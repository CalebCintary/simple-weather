//
// Created by calebcintary on 3/18/21.
//

#include "gtk_callbacks.h"


void openweathermap_settings_button_invoke_clicked(GtkButton *button, gpointer userdata) {
    gtk_widget_show(GTK_WIDGET(openweathermap_settings_window));
}

void openweathermap_settings_button_cancel_clicked(GtkButton *button, gpointer userdata) {
    gtk_widget_hide(GTK_WIDGET(openweathermap_settings_window));
}

void openweathermap_settings_button_apply_clicked(GtkButton *button, gpointer userdata) {
    gtk_widget_hide(GTK_WIDGET(openweathermap_settings_window));
}

void openweathermap_settings_checkbox_toggled(GtkToggleButton *button, gpointer userdata) {

}

