//
// Created by calebcintary on 3/17/21.
//

#ifndef CLAB1_PROPERTIES_H
#define CLAB1_PROPERTIES_H

typedef enum {
    PA,
    KPA,
    BAR
} PressureUnits;

typedef enum {
    CELSIUM,
    FARENGEIT,
    KELVIN
} TemperatureUnits;

typedef enum {
    MPS,
    KPH,
    MPH
} WindSpeedUnits;

typedef struct {
    char*            owm_apikey;
    WindSpeedUnits   wsu;
    TemperatureUnits tu;
    PressureUnits    pu;
} Properties;



#endif //CLAB1_PROPERTIES_H
