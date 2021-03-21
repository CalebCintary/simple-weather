//
// Created by lavr4 on 3/14/2021.
//

#include "signals_handlers.h"

void sig_handler(int signum) {

}

void install_signal_handlers() {
    //signal(SIGKILL, sig_handler);
    signal(SIGTERM, sig_handler);
    signal(SIGINT, sig_handler);
}