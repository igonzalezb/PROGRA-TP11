
//////////////////////////////////// CONSOLA - HEADER ////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                           //
// Incluye funciones que serán usadas por distintos archivos del programa.                   //
//                                                                                           //
///////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CONSOLA_H
#define CONSOLA_H

#include "emu_ports.h"

MY_REG case_set (MY_REG);
MY_REG case_clear (MY_REG);
MY_REG case_blink (MY_REG);
MY_REG case_number (int,MY_REG);

void impresion (MY_REG);

long decimalToBinary(MY_REG);

#endif /* CONSOLA_H */
