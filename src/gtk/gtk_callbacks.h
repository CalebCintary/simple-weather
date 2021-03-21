//
// Created by calebcintary on 3/17/21.
//

#ifndef CLAB1_GTK_CALLBACKS_H
#define CLAB1_GTK_CALLBACKS_H

#include <gtk/gtk.h>
#include "../requests/owm.h"

GtkBuilder *builder;

GObject *mwc_settings_window;
GObject *openweathermap_settings_window;

void mainwindow_searchbar_activate(GtkEntry *entry, gpointer userdata);

void settings_invoke_button_clicked(GtkButton *button, gpointer userdata);
void settings_exit_button_clicked(GtkButton *button, gpointer userdata);

void openweathermap_settings_button_invoke_clicked(GtkButton *button, gpointer userdata);
void openweathermap_settings_button_cancel_clicked(GtkButton *button, gpointer userdata);
void openweathermap_settings_button_apply_clicked(GtkButton *button, gpointer userdata);
void openweathermap_settings_checkbox_toggled(GtkToggleButton *button, gpointer userdata);


#endif //CLAB1_GTK_CALLBACKS_H
