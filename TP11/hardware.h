
//////////////////////////////////// HARDWARE - HEADER ////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                           //
// Incluye funciones que serán usadas por distintos archivos del programa.                   //
//                                                                                           //
///////////////////////////////////////////////////////////////////////////////////////////////

#ifndef HARDWARE_H
#define HARDWARE_H

#define CANT_LEDS 7 

typedef struct                  
{
    char led_name [10];
    char pin [4];
    char direction [5];
    char value;
    char value_copy;
}pinsT;

void inicio_estado_pines (pinsT leds[]);
void pin_out_or_in (int, pinsT leds[]);
void set_pin_zero_or_one (int, pinsT leds[]);
void export_all_pins(pinsT leds[]);
void unexport_all_pins(pinsT leds[]);

#endif /* HARDWARE_H */

