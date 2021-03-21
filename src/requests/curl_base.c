//
// Created by lavr4 on 3/14/2021.
//

#include "curl.h"

CURL* curl = NULL;
int is_in_work = 0;

void curl_setup() {
    curl = curl_easy_init();
}

CURL* get_curl_session() {
    if (curl == NULL) {
        curl_setup();
    }

    while (is_in_work);

    is_in_work = 1;
    return curl;
}


size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata) {
    char* response = (char*) userdata;
    size_t realsize = size * nmemb;
    size_t previous_size = strlen(response);

    char *_ptr = realloc(response, previous_size + realsize + 1);

    memcpy(_ptr, ptr, strlen(ptr) + 1);

    return realsize;
}

char *curl_setup_baseget_response() {
    char *buffer = malloc(1000);

    curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, buffer);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

    return buffer;
}





void remove_session() {
    //curl_global_cleanup();
    is_in_work = 0;
}