

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
    uint mask = 0xFFFF;             
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
    return port_a;
}

MY_REG case_number_on (int n, MY_REG port_a)
{
    //n = (c - 48);
    port_a = bitSet(port_a, n, PORTA);
    impresion (port_a);
    return port_a;
}

MY_REG case_number_off (int n, MY_REG port_a)
{
    //n = (c - 48);
    port_a = bitClr(port_a, n, PORTA);
    impresion (port_a);
    return port_a;
}

void welcome (void)
{
        system("clear");
        
        char c;
        printf(BLUE_TEXT "\t\t\tBienvenido\n");
        printf(MAGENTA_TEXT "INSTRUCCIONES:\n");
        printf(WHITE_TEXT " Si presiona un numero del" GREEN_TEXT " '0' " WHITE_TEXT "al" GREEN_TEXT " '7' " WHITE_TEXT "se enciende o apaga el LED de esa posicion\n");
        printf(WHITE_TEXT " Si presiona" GREEN_TEXT " 'b' " WHITE_TEXT "parpadean los LEDs encendidos hasta que se aprete" GREEN_TEXT " 'b' " WHITE_TEXT "nuevamente\n");
        printf(WHITE_TEXT " Si presiona" GREEN_TEXT " 's' " WHITE_TEXT "se encienden todos los LEDs\n");
        printf(WHITE_TEXT " Si presiona" GREEN_TEXT " 'c' " WHITE_TEXT "se apagan todos los LEDs\n");
        printf(WHITE_TEXT " Si presiona" GREEN_TEXT " 'ESPACIO' " WHITE_TEXT "se van prendendo y apagando los LEDs (uno por uno), hasta que se aprete" GREEN_TEXT " 'ESPACIO' " WHITE_TEXT "nuevamente\n");
        printf(WHITE_TEXT " Si presiona" GREEN_TEXT " 'ESC' " WHITE_TEXT "finaliza el programa\n");
               
        
        printf(WHITE_TEXT"\n\n Por favor, presione" RED_TEXT " ENTER " WHITE_TEXT"para comenzar");
        while ((c = getchar()) != '\n')
            {
               continue; 
            }
        system("clear");
}




void impresion (MY_REG port_a)
{
    //=================TERMINAL==============================================================
    long binary;
    binary = decimalToBinary(port_a); //Convierto numero a un int "binario"
    system("clear");
    printf( WHITE_TEXT "LEDs in" CYAN_TEXT " PORTA" WHITE_TEXT ": " RED_TEXT"%08ld\n" WHITE_TEXT, binary); //Lo imprimo en pantalla
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



