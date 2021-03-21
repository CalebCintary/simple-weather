#include "signals/signals_handlers.h"
#include "curl/curl.h"
#include "requests/owm.h"
#include <gtk/gtk.h>
#include "gtk/gtk_callbacks.h"
#include <time.h>

GObject *window;
GObject *settings_window;


int main(int argc, char* argv[]) {

    clock_t tStart = clock();

    GObject *button;
    GError *error = NULL;

    gtk_init(&argc, &argv);

    printf("%Lf", (long double)(((long double)(clock() - tStart)) / (long double)CLOCKS_PER_SEC));

    builder = gtk_builder_new();

    if (gtk_builder_add_from_file(builder, "../builder.ui", &error) == 0) {
        g_printerr ("Error loading file: %s\n", error->message);
        g_clear_error (&error);
        return 1;
    }

    window = gtk_builder_get_object (builder, "main_window");
    mwc_settings_window = gtk_builder_get_object(builder, "settings_window");
    openweathermap_settings_window = gtk_builder_get_object(builder, "openweathermap_settings_window");

    g_signal_connect(window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

    /* Connecting settings window to settings invoke button */
    GObject *settings_invoke_button = gtk_builder_get_object(builder, "settings_invoke_button");
    g_signal_connect(settings_invoke_button,
                     "clicked",
                     G_CALLBACK(settings_invoke_button_clicked),
                     NULL);

    /* Connecting settings exit button */
    GObject *settings_exit_button = gtk_builder_get_object(builder, "settings_exit_button");
    g_signal_connect(settings_exit_button,
                     "clicked",
                     G_CALLBACK(settings_exit_button_clicked),
                     NULL);

    GObject *openweathermap_settings_button_invoke = gtk_builder_get_object(builder, "openweathermap_settings_button_invoke");
    g_signal_connect(openweathermap_settings_button_invoke,
                     "clicked",
                     G_CALLBACK(openweathermap_settings_button_invoke_clicked),
                     NULL);

    GObject *openweathermap_settings_button_cancel = gtk_builder_get_object(builder, "openweathermap_settings_button_cancel");
    g_signal_connect(openweathermap_settings_button_cancel,
                     "clicked",
                     G_CALLBACK(openweathermap_settings_button_cancel_clicked),
                     NULL);

    GObject *openweathermap_settings_button_apply = gtk_builder_get_object(builder, "openweathermap_settings_button_apply");
    g_signal_connect(openweathermap_settings_button_apply,
                     "clicked",
                     G_CALLBACK(openweathermap_settings_button_apply_clicked),
                     NULL);

    GObject *openweathermap_settings_checkbox = gtk_builder_get_object(builder, "openweathermap_settings_checkbox");




    GObject *search_bar = gtk_builder_get_object(builder, "search_bar");
    g_signal_connect(search_bar,
                     "activate",
                     G_CALLBACK(mainwindow_searchbar_activate),
                     NULL);


    
    puts("All is initialized!\n");

    gtk_main ();

    return 0;
}