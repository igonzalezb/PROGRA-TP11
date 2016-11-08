

/////////////////////////////////////////////// CONSOLA /////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                   //
//  Impresion en pantalla de aquello necesario por el programa.                                      //
//                                                                                                   //
///////////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <unistd.h>
#include "main.h"
#include "hardware.h"
#include "emu_ports.h"
#include "consola.h"



MY_REG case_set (MY_REG port_a)
{
    uint mask = 0xFFFF;             //IMPRESION
    port_a = maskOn (port_a, mask, PORTA); //Prendo los leds que dice la mascara (todos)
    impresion (port_a);
    return port_a;
}

MY_REG case_clear (MY_REG port_a)
{
    uint mask = 0x0000;
    port_a = maskOff (port_a, mask, PORTA);
    impresion (port_a);
    return port_a;
}

MY_REG case_blink (MY_REG port_a)
{
    MY_REG blink;
    blink.w.word = 0x0000;
    impresion (blink);
    usleep(300000);
    //system("clear");
    impresion (port_a);
    return port_a;
}

MY_REG case_number (int n, MY_REG port_a)
{
    //n = (c - 48);
    port_a = bitSet(port_a, n, PORTA);
    impresion (port_a);
    return port_a;
}





void impresion (MY_REG port_a)
{
    //=================TERMINAL==============================================================
    long binary;
    binary = decimalToBinary(port_a); //Convierto numero a un int "binario"
    //system("clear");
    printf("LEDs in PORTA: %08ld\n", binary); //Lo imprimo en pantalla
}

long decimalToBinary(MY_REG port_a) //Convierte numeros a binarios
    {
        int remainder;
        long binary = 0, i = 1;
        while((port_a.by.hi) != 0)
        {
            remainder = (port_a.by.hi)%2;
            (port_a.by.hi) = (port_a.by.hi)/2;
            binary= binary + (remainder*i);
            i = i*10;
        }
        return binary;
    }



