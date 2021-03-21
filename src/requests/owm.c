//
// Created by lavr4 on 3/14/2021.
//

#include "owm.h"
#include "curl.h"



char* get_weather(char* city) {
    CURL* curl = get_curl_session();

    char* url = "api.openweathermap.org/data/2.5/weather?q=";
    char* urlParams = "&mode=json&appid=f262fce100326b8948aaa3ce1b3d308c&units=metric";
    char* fullurl = calloc(strlen(url) + strlen(urlParams) + strlen(city) + 1, sizeof(char));
    fullurl = strcat(fullurl, url);
    fullurl = strcat(fullurl, city);
    fullurl = strcat(fullurl, urlParams);

    curl_easy_setopt(curl, CURLOPT_URL, fullurl);
    char * response = curl_setup_baseget_response();
    curl_easy_perform(curl);
    remove_session();

    return response;
}


size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

void* get_weather_icon(char *name) {
    CURL* curl = get_curl_session();


    char* url = "http://openweathermap.org/img/wn/";
    char* urlParams = "@2x.png";
    char* fullurl = calloc(strlen(url) + strlen(urlParams) + strlen(name) + 1, sizeof(char));
    fullurl = strcat(fullurl, url);
    fullurl = strcat(fullurl, name);
    fullurl = strcat(fullurl, urlParams);

    FILE *fp;
    fp = fopen("icon.png","wb");

    curl_easy_setopt(curl, CURLOPT_URL, fullurl);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);


    curl_easy_perform(curl);
    fclose(fp);
    remove_session();
}

char* get_detailed_weather(char *city) {
    CURL* curl = get_curl_session();

    char* url = "pro.openweathermap.org/data/2.5/forecast/hourly?q=";
    char* urlParams = "&mode=json&appid=f262fce100326b8948aaa3ce1b3d308c&units=metric";
    char* fullurl = calloc(strlen(url) + strlen(urlParams) + strlen(city) + 1, sizeof(char));
    fullurl = strcat(fullurl, url);
    fullurl = strcat(fullurl, city);
    fullurl = strcat(fullurl, urlParams);

    curl_easy_setopt(curl, CURLOPT_URL, fullurl);
    char * response = curl_setup_baseget_response();
    curl_easy_perform(curl);
    remove_session();

    return response;
}

