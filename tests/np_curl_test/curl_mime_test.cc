/**
curl_mime_test.cc
===================

This succeeded to read bare array data manually from file and upload
to FastAPI endpoint after adapting the handler, ~/env/tools/fastapi_check/main.py
to branch on content-type::

     86     content_type = request.headers.get('content-type')
     87     if content_type.startswith("multipart/form-data"):
     88         form = await request.form()
     89         filename = form["upload"].filename
     90         print("filename:%s" % filename )
     91         contents = await form["upload"].read()
     92         a = np.frombuffer(contents, dtype=dtype ).reshape(*shape)
     93     else:
     94         data: bytes = await request.body()
     95         a = np.frombuffer(data, dtype=dtype ).reshape(*shape)
     96     pass
     97



**/



#include <stdio.h>
#include <curl/curl.h>

// Define your callback functions
size_t file_read_callback(char *buffer, size_t size, size_t nitems, void *arg) {
    FILE *file = (FILE *)arg;
    return fread(buffer, size, nitems, file); // Read data from the file
}

int file_seek_callback(void *arg, curl_off_t offset, int origin) {
    FILE *file = (FILE *)arg;
    if (fseek(file, offset, origin) == 0) {
        return CURL_SEEKFUNC_OK; // Seek was successful
    } else {
        return CURL_SEEKFUNC_FAIL; // Seek failed
    }
}

void file_free_callback(void *arg) {
    // Close the file if necessary when the MIME part is freed
    if (arg) {
        fclose((FILE *)arg);
    }
}

int main(int argc, char** argv)
{
    const char* path = "/Users/blyth/Downloads/arr" ;

    CURL *curl = curl_easy_init();
    if (!curl) return 1;


    curl_mime *mime;
    curl_mimepart *part;
    FILE *file = fopen(path, "rb"); // Open file for binary read

    if (!file) {
        fprintf(stderr, "Could not open file.\n");
        curl_easy_cleanup(curl);
        return 1;
    }

    // Get the file size for datasize
    fseek(file, 0, SEEK_END);
    curl_off_t file_size = ftell(file);
    fseek(file, 0, SEEK_SET); // Rewind to the beginning

    // Create a MIME handle and add a part
    mime = curl_mime_init(curl);
    part = curl_mime_addpart(mime);

    // Set the data source using the callback function
    curl_mime_data_cb(part, file_size, file_read_callback, file_seek_callback, file_free_callback, file);

    // Set the field name and filename for the part
    curl_mime_name(part, "upload");
    curl_mime_filename(part, "binary_data");

    // Set up the rest of your libcurl options (URL, POST method, etc.)
    curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.1:8000/array_transform");
    curl_easy_setopt(curl, CURLOPT_MIMEPOST, mime);


    struct curl_slist* headerlist = nullptr ;
    headerlist = curl_slist_append(headerlist, "x-opticks-token:secret" );
    headerlist = curl_slist_append(headerlist, "x-opticks-dtype:uint8" );
    headerlist = curl_slist_append(headerlist, "x-opticks-shape:(512,512,3)" );
    headerlist = curl_slist_append(headerlist, "x-opticks-level:1" );
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerlist);


    // Perform the request
    CURLcode res = curl_easy_perform(curl);

    // Check for errors
    if (res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    }

    // Cleanup
    curl_mime_free(mime); // This will call file_free_callback for 'file'
    curl_easy_cleanup(curl);

    return 0;
}

