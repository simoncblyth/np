/**
NSQLite_test.cc
=================

~/np/tests/NSQLite_test.sh

**/

#include "NSQLite.h"
#include "NP.hh"

struct NSQLite_test
{
    static int createTable(NSQLite* db);
    static int insertData(NSQLite* db);
    static int OLD_addStudent(NSQLite* db, int id, const char* first_name, const char* last_name, const char* email);
    static int     addStudent(NSQLite* db, int id, const char* first_name, const char* last_name, const char* email);
    static int readData(NSQLite* db);

    static int loadSchema(NSQLite* db, const char* _schema);
    static int loadEvent( NSQLite* db, const char* _evsmry);

    static int main(const char* _db, const char* _schema, const char* _evsmry);
};

int NSQLite_test::createTable(NSQLite* db){
    const char* sql = "CREATE TABLE STUDENT("
                "ID INT PRIMARY KEY NOT NULL,"
                "FIRST_NAME TEXT NOT NULL,"
                "LAST_NAME TEXT NOT NULL,"
                "EMAIL TEXT NOT NULL)";

    db->exec(sql);
    return 0;
}

int NSQLite_test::insertData(NSQLite* db){
    const char* sql = "INSERT INTO STUDENT (ID, FIRST_NAME, LAST_NAME, EMAIL) "
                "VALUES(1, 'John', 'Doe', 'john@doe.com'),"
                "(2, 'Peter', 'Griffin', 'peter@griffin.com'),"
                "(3, 'Homer', 'Simpson', 'homer@simpson.com')";

    db->exec(sql);
    return 0;
}

int NSQLite_test::OLD_addStudent(NSQLite* db, int id, const char* first_name, const char* last_name, const char* email )
{
    const char* sql = "INSERT OR REPLACE INTO STUDENT (ID, FIRST_NAME, LAST_NAME, EMAIL) VALUES (?, ?, ?, ?);";
    OLD_NSQLiteStmt inserter(db->db, sql);

    sqlite3_bind_int64(inserter.stmt, 1, id);
    sqlite3_bind_text(inserter.stmt, 2, first_name, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(inserter.stmt, 3, last_name,  -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(inserter.stmt, 4, email,      -1, SQLITE_TRANSIENT);

    if (sqlite3_step(inserter.stmt) != SQLITE_DONE) {
        std::cerr << "Failed to ingest student: " << sqlite3_errmsg(db->db) << std::endl;
    }
    return 0;
}


int NSQLite_test::addStudent(NSQLite* db, int id, const char* first_name, const char* last_name, const char* email)
{
    const char* sql = "INSERT OR REPLACE INTO STUDENT (ID, FIRST_NAME, LAST_NAME, EMAIL) VALUES (?, ?, ?, ?);";
    NSQLiteStmt inserter(db->db, sql);
    inserter.execute(id, first_name, last_name, email); // Fully generalized execution and binding in one line!
    return 0;
}


int NSQLite_test::readData(NSQLite* db)
{
    const char* sql = "SELECT * FROM 'STUDENT'";
    db->exec_cb(sql);
    db->queryColumns(sql);
    return 0;
}

int NSQLite_test::loadSchema(NSQLite* db, const char* _schema)
{
    std::string sql = U::ReadStringDirect(_schema);

    std::cout << "[NSQLite_test::loadSchema\n" ;
    std::cout << sql << "\n" ;
    std::cout << "]NSQLite_test::loadSchema\n" ;

    db->exec(sql.c_str());
    return 0;
}


/**
NSQLite_test::loadEvent
-----------------------

THIS HAS BEEN RELOCATED TO sysrap/sreportdb.h

TODO: once established over in sysrap - remove this


**/


int NSQLite_test::loadEvent(NSQLite* db, const char* _evsmry)
{
    NP* evsmry = NP::Load(_evsmry);
    if (!evsmry) {
        std::cerr << "Error: Failed to load NP array from " << _evsmry << "\n";
        return -1;
    }
    std::cout << "[NSQLite_test::loadEvent " << evsmry->sstr() << "\n";
    assert(evsmry->num_dim() == 2);

    const std::vector<std::string>& labels = *(evsmry->labels);
    size_t num_labels = labels.size();

    // 1. Safe Label Extraction Helper
    auto get_label_idx = [&labels, num_labels](const std::string& key) -> size_t {
        size_t idx = std::find(labels.begin(), labels.end(), key) - labels.begin();
        if (idx >= num_labels) {
            throw std::runtime_error("Required column label missing from NP array: " + key);
        }
        return idx;
    };

    size_t index_idx, timestamp_idx, genstep_idx, photon_idx, hit_idx;
    size_t launch_idx, upload_idx, simulate_idx, download_idx;

    try {
        index_idx     = get_label_idx("index");
        timestamp_idx = get_label_idx("timestamp");
        genstep_idx   = get_label_idx("genstep");
        photon_idx    = get_label_idx("photon");
        hit_idx       = get_label_idx("hit");
        launch_idx    = get_label_idx("launch");
        upload_idx    = get_label_idx("dt_upload");
        simulate_idx  = get_label_idx("dt_simulate");
        download_idx  = get_label_idx("dt_download");
    } catch (const std::exception& e) {
        std::cerr << "Schema error: " << e.what() << "\n";
        delete evsmry;
        return -2;
    }

    const char* sql = "INSERT OR REPLACE INTO opticks_events (run_id, event_index, event_timestamp, "
                      "genstep_count, photon_count, hit_count, launch_count, dt_upload, dt_simulate, dt_download) "
                      "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?);";

    NSQLiteStmt inserter(db->db, sql);
    // TODO: Determine how you pull your true parent run_id (e.g., passed as an argument)
    int64_t run_id = 0;

    size_t ni = evsmry->shape[0];
    size_t nj = evsmry->shape[1];
    const int64_t* ee = evsmry->cvalues<int64_t>();

    // 2. BEGIN THE TRANSACTION (Massive speedups)
    sqlite3_exec(db->db, "BEGIN TRANSACTION;", nullptr, nullptr, nullptr);

    for (size_t i = 0; i < ni; i++)
    {
        const int64_t* row = ee + (i * nj);

        int64_t event_index     = row[index_idx];
        int64_t event_timestamp = row[timestamp_idx];
        int64_t genstep_count   = row[genstep_idx];
        int64_t photon_count    = row[photon_idx];
        int64_t hit_count       = row[hit_idx];
        int64_t launch_count    = row[launch_idx];
        int64_t dt_upload       = row[upload_idx];
        int64_t dt_simulate     = row[simulate_idx];
        int64_t dt_download     = row[download_idx];

        inserter.execute(run_id, event_index, event_timestamp, genstep_count,
                         photon_count, hit_count, launch_count, dt_upload,
                         dt_simulate, dt_download);
    }

    // 3. COMMIT THE TRANSACTION
    sqlite3_exec(db->db, "COMMIT;", nullptr, nullptr, nullptr);

    std::cout << "]NSQLite_test::loadEvent\n";
    delete evsmry;
    return 0;
}


int NSQLite_test::main(const char* _db, const char* _schema, const char* _evsmry)
{
    NSQLite db(_db);

    int rc = 0 ;

    if(_schema == nullptr)
    {
        rc += createTable(&db);
        rc += insertData(&db);
        rc += addStudent(&db, 4, "Peter", "Parker", "peter@batcave.com" );
        rc += readData(&db);
    }
    else
    {
        rc += loadSchema(&db, _schema);
        rc += loadEvent( &db, _evsmry);
    }

    return rc ;
}

int main(int argc, char** argv)
{
    const char* _db     = argc > 1 ? argv[1] : "/tmp/NSLite_test.db" ;
    const char* _schema = argc > 2 ? argv[2] : nullptr ;
    const char* _evsmry  = argc > 3 ? argv[3] : nullptr ;

    return NSQLite_test::main(_db, _schema, _evsmry );
}

