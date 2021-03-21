//
// Created by lavr4 on 3/14/2021.
//

#ifndef CLAB1_CURL_H
#define CLAB1_CURL_H

#include <stdlib.h>
#include <curl/curl.h>

#include <string.h>




void curl_setup();

CURL* get_curl_session();

char *curl_setup_baseget_response();

void *curl_getfile(char *name);

void remove_session();

#endif //CLAB1_CURL_H
