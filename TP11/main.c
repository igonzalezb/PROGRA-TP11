
///////////////////////////////////////////////////////////////////////////////////////////////////////
//  Trabajo Práctico 11                                                                              //
//                                                                                                   //
//  Entrega: 7 de Noviembre de 2016            ///////////////////////////////////////////////////   //
//                                            //Manejo de LEDS en la Raspberry Pi y en consola //    //
//  Grupo 6: González Bigliardi, Iñaki       ///////////////////////////////////////////////////     //
//           Lago, Valentina                                                                         //
//           Müller, Malena                                                                          //
//                                                                                                   //
//  Se emulan los puertos A, B y D. A y B son dos puertos de 8 bits, configurables tanto para entrada//
//  como para salida. D tiene 16 y es simplemente un alias para los puertos A y B juntos, siendo el B//
//  el menos significativo.                                                                          //
//                                                                                                   //
///////////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

#include "main.h"
#include "nonblock.h"
#include "emu_ports.h"
#include "input_control.h"
#include "hardware.h"
#include "consola.h"

int main(void) 
{
    char c;
    int i=0;
    MY_REG port_a;

    if((ALLEGRO))
    {
        //allegro(port_a);
        return (0);
    }
    else    //Terminal y Hardware
    {
            //=======================================================================================================================================================================================================================================================================
        pinsT leds[] = {{"LED_0","4","out",'0','0'},
                            {"LED_1","17","out",'0','0'},
                                {"LED_2","18","out",'0','0'},
                                    {"LED_3","27","out",'0','0'},
                                        {"LED_4","22","out",'0','0'},
                                            {"LED_5","23","out",'0','0'},
                                                {"LED_6","24","out",'0','0'},
                                                    {"LED_7","25","out",'0','0'}};
        
        inicio_estado_pines (leds);
        system("clear");
        
        printf("Bienvenido!\n");
        printf("INSTRUCCIONES:\n Si presiona un numero del '0' al '7' se enciende o apaga el LED de esa posicion\n Si presiona 'b' parpadean los LED encendidos hasta que se aprete 'b' de nuevo\n Si presiona 's' se encienden todos\n Si presiona 'c' se apagan todos\n Si presiona 'ESC' sale del programa\n ");
        printf("\n\n Por favor, presione ENTER para comenzar");
        while ((c = getchar()) != '\n')
            {
               continue; 
            }
        system("clear");
        //==========================================================================================================================================================================================================================================================================

            port_a.w.word = 0x0000; //Asi empiezan todos los leds apagados
            impresion(port_a);  //Imprimo el puerto a
            nonblock(NB_ENABLE);
        
            while (c != '\e') //Funciona hasta que se apreta la tecla ESC
            {
                i=kbhit();
                if (i!=0)
                {
                    c = (fgetc(stdin)); //Obtengo lo ingresado por el teclado
                   
                    if (VALIDO) //Si la tecla ingresada es valida continuo
                    {
                        system("clear"); //Limpio pantalla
                        port_a = validacion(c, leds, port_a); //Ejecuto la operacion ingresada por el teclado
                        
                    }
                }
            }
            nonblock(NB_DISABLE);
        
            unexport_all_pins(leds);
            system("clear"); //Limpio la pantalla
            return (0);
    }
}
