
//////////////////////////////////// INPUT_CONTROL - HEADER ////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                           //
// Incluye funciones que serán usadas por distintos archivos del programa.                   //
//                                                                                           //
///////////////////////////////////////////////////////////////////////////////////////////////

#ifndef INPUT_CONTROL_H
#define INPUT_CONTROL_H

#include <stdio.h>
#include <unistd.h>
#include "main.h"
#include "hardware.h"
#include "nonblock.h"
#include "consola.h"

//MY_REG validacion (char, pinsT, MY_REG);

MY_REG validacion (char c, pinsT leds[], MY_REG port_a);

#endif /* INPUT_CONTROL_H */
