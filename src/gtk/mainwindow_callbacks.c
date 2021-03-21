//
// Created by calebcintary on 3/17/21.
//

#include "gtk_callbacks.h"
#include "pthread.h"
#include "string.h"
#include <json-c/json.h>
#include <json-c/json_util.h>

void * weathericonload_start (void *pointer) {
    get_weather_icon((char*) pointer);
    GtkImage *weather_icon = GTK_IMAGE(gtk_builder_get_object(builder, "weather_icon"));
    gtk_image_set_from_file(weather_icon, "icon.png");
}




void * loadthread_start(void *pointer) {
    char* city = pointer;

    char *json = get_weather(city);




    puts(json);
    FILE *file = fopen("file.json", "w");
    if (!file) {
        puts("CRITICAL - Cannot create buffer for json object");
        exit(-1);
    }
    fputs(json, file);
    fclose(file);


    json_object *root = json_object_from_file("file.json");

    //ERRORS
    {
        if (!root) {
            GtkLabel *mainwindow_error_label = GTK_LABEL(gtk_builder_get_object(builder, "mainwindow_error_label"));
            gtk_label_set_text(mainwindow_error_label, "Sorry, but there is no internet connection");
            GtkStack *stack = GTK_STACK(gtk_builder_get_object(builder, "mainwindow_stack"));
            gtk_stack_set_visible_child_name(stack, "page3");
            return NULL;
        }

        int32_t cod = json_object_get_int(json_object_object_get(root, "cod"));
        if (cod == 404) {
            GtkStack *stack = GTK_STACK(gtk_builder_get_object(builder, "mainwindow_stack"));
            gtk_stack_set_visible_child_name(stack, "page3");
            return NULL;
        }
        if (cod == 400) {
            GtkLabel *mainwindow_error_label = GTK_LABEL(gtk_builder_get_object(builder, "mainwindow_error_label"));
            gtk_label_set_text(mainwindow_error_label, "Sorry, but there is an empty request");
            GtkStack *stack = GTK_STACK(gtk_builder_get_object(builder, "mainwindow_stack"));
            gtk_stack_set_visible_child_name(stack, "page3");
            return NULL;
        }
    }

    //ICON SETUP
    json_object *weather = json_object_array_get_idx(json_object_object_get(root, "weather"), 0);
    const char *icon_name = json_object_get_string(json_object_object_get(weather, "icon"));

    pthread_t pthread_id;
    pthread_attr_t pthread_attr;

    pthread_attr_init(&pthread_attr);

    pthread_create(&pthread_id, &pthread_attr, weathericonload_start, icon_name);

    {
        GtkLabel *name = GTK_LABEL(gtk_builder_get_object(builder, "city_name"));
        gtk_label_set_text(name, json_object_get_string(json_object_object_get(root, "name")));

        GtkLabel *country = GTK_LABEL(gtk_builder_get_object(builder, "country_code"));
        gtk_label_set_text(country, json_object_get_string(json_object_object_get(json_object_object_get(root, "sys"), "country")));

        GtkLabel *weather_description = GTK_LABEL(gtk_builder_get_object(builder, "weather_description"));
        gtk_label_set_text(weather_description, json_object_get_string(json_object_object_get(weather, "description")));
    }

    {
        json_object *main = json_object_object_get(root, "main");

        GtkLabel *temperature_label = GTK_LABEL(gtk_builder_get_object(builder, "temperature_label"));
        gtk_label_set_text(temperature_label, json_object_get_string(json_object_object_get(main, "temp")));

        GtkLabel *feels_like = GTK_LABEL(gtk_builder_get_object(builder, "feels_like"));
        gtk_label_set_text(feels_like, json_object_get_string(json_object_object_get(main, "feels_like")));

        GtkLabel *temp_min = GTK_LABEL(gtk_builder_get_object(builder, "temp_min"));
        gtk_label_set_text(temp_min, json_object_get_string(json_object_object_get(main, "temp_min")));

        GtkLabel *temp_max = GTK_LABEL(gtk_builder_get_object(builder, "temp_max"));
        gtk_label_set_text(temp_max, json_object_get_string(json_object_object_get(main, "temp_max")));

        GtkLabel *pressure = GTK_LABEL(gtk_builder_get_object(builder, "pressure"));
        gtk_label_set_text(pressure, json_object_get_string(json_object_object_get(main, "pressure")));

        GtkLabel *humidity = GTK_LABEL(gtk_builder_get_object(builder, "humidity"));
        gtk_label_set_text(humidity, json_object_get_string(json_object_object_get(main, "humidity")));
    }

    GtkStack *stack = GTK_STACK(gtk_builder_get_object(builder, "mainwindow_stack"));
    gtk_stack_set_visible_child_name(stack, "page2");
    
    
    

    return 0;
}

void settings_invoke_button_clicked(GtkButton *button, gpointer userdata) {
    gtk_widget_show(GTK_WIDGET(mwc_settings_window));
}

void settings_exit_button_clicked(GtkButton *button, gpointer userdata) {
    gtk_widget_hide(GTK_WIDGET(mwc_settings_window));
}

void mainwindow_searchbar_activate(GtkEntry *entry, gpointer userdata) {
    const gchar* string = gtk_entry_get_text(entry);
    puts("Searching for: ");
    puts(string);

    GtkStack *stack = GTK_STACK(gtk_builder_get_object(builder, "mainwindow_stack"));
    gtk_stack_set_visible_child_name(stack, "page1");


    pthread_t pthread_id;
    pthread_attr_t pthread_attr;

    pthread_attr_init(&pthread_attr);

    pthread_create(&pthread_id, &pthread_attr, loadthread_start, string);



}
