// ./create_db.sh

/**
NSQLite_test.cc
=================

**/

#include "NSQLite.h"

struct NSQLite_test
{
    static int createTable(NSQLite* db);
    static int insertData(NSQLite* db);
    static int OLD_addStudent(NSQLite* db, int id, const char* first_name, const char* last_name, const char* email);
    static int     addStudent(NSQLite* db, int id, const char* first_name, const char* last_name, const char* email);
    static int readData(NSQLite* db);
    static int main(const char* path);
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

int NSQLite_test::main(const char* path)
{
    NSQLite db(path);

    int rc = 0 ; 
    rc += createTable(&db);
    rc += insertData(&db);
    rc += addStudent(&db, 4, "Peter", "Parker", "peter@batcave.com" );
    rc += readData(&db);

    return rc ;
}

int main(int argc, char** argv)
{
    return NSQLite_test::main(argv[1]);
}

