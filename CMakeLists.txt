cmake_minimum_required(VERSION 3.10)
project(simple-weather LANGUAGES C)

set(CMAKE_C_STANDARD 11)

set(CLABSOURCE src/main.c
        src/signals/signals_handlers.c
        src/signals/signals_handlers.h
        src/requests/curl.h src/requests/curl_base.c
        src/requests/owm.c src/requests/owm.h
        src/properties.h
        src/gtk/gtk_callbacks.h
        src/gtk/mainwindow_callbacks.c src/gtk/settings_callback.c)

add_executable(simple-weather ${CLABSOURCE})

configure_file(builder.ui builder.ui COPYONLY)
configure_file(data_OpenWeather.png data_OpenWeather.png COPYONLY)

include(FindPkgConfig)

# Including curl
pkg_search_module(CURL libcurl REQUIRED)
include_directories(SYSTEM ${CURL_INCLUDE_DIRS})
target_link_libraries(simple-weather ${CURL_LIBRARIES})

PKG_CHECK_MODULES(GTK3 REQUIRED gtk+-3.0)
INCLUDE_DIRECTORIES(${GTK3_INCLUDE_DIRS})
LINK_DIRECTORIES(${GTK3_LIBRARY_DIRS})
TARGET_LINK_LIBRARIES(simple-weather ${GTK3_LIBRARIES})

find_package(Threads)
target_link_libraries(simple-weather ${CMAKE_THREAD_LIBS_INIT})

pkg_search_module(JSON json-c)
include_directories(SYSTEM ${JSON_INCLUDE_DIRS})
find_library(JSON_LIBRARY json-c REQUIRED)
message(${JSON_LIBRARY})
target_link_libraries(simple-weather ${JSON_LIBRARY})

