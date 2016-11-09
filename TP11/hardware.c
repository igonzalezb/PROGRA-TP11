
/////////////////////////////////////////////// HARDWARE //////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                   //
//  Control de pines de la Raspberry Pi con dirección de salida.                                     //
//                                                                                                   //
///////////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include "hardware.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////

void inicio_estado_pines (pinsT leds[])
{
    export_all_pins(leds);
    int n;
    for (n=0; n <= CANT_LEDS; n++)
    {
        pin_out_or_in (n,leds);
        set_pin_zero_or_one (n,leds);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////// FUNCIONES UTILES ///////////////////////////////////////////
   
///////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////export_all_pins/////////////////////////////////////////////
//                                                                                                   //
// Exporta los pines que se vayan a usar.                                                            //
// Recibe: arreglo de estructuras de leds                                                            //
// Devuelve: Nada.                                                                                   //
//                                                                                                   //
///////////////////////////////////////////////////////////////////////////////////////////////////////
    
    
    void export_all_pins(pinsT leds[])
    {
        FILE *handle_export;
        
        int nWritten, i;
        
        for (i=0; i<=CANT_LEDS; i++) //ver como recorrer todo el arreglo de estructuras
        {
            if ((handle_export = fopen ("/sys/class/gpio/export","w"))==NULL)
            {
                printf("Cannot open EXPORT File. Try again later.\n");
                exit(1);
            }
         
            nWritten = fputs(leds[i].pin, handle_export);
         
            if (nWritten==-1)
            {
                printf("Cannot EXPORT PIN. Try again later.\n");
                exit(1);
            }
//            else
//            {
//                printf("EXPORT File opened succesfully \n");
//            }
            
            fclose(handle_export);
        }
    }

/////////////////////////////////////////// pin_out_or_in /////////////////////////////////////////////
//                                                                                                   //
// Setea el pin en in o out de acuerdo a como este definido en la estructura.                        //
// Recibe: el numero de pin (No el numero que figura en la Raspberry Pi, sino que el numero de bit). //
// y el arreglo de estructuras de leds                                                               //
// Devuelve: Nada.                                                                                   //
//                                                                                                   //
///////////////////////////////////////////////////////////////////////////////////////////////////////
    
     
    void pin_out_or_in (int i,pinsT leds[])
    {
        FILE * handle_direction = NULL;
        int nWritten;
        char destino[50];
        //sprintf (stdout,"/sys/class/gpio/gpio%s/direction", leds[i].pin);
        sprintf (destino,"/sys/class/gpio/gpio%s/direction", leds[i].pin);
    ///////////////////////////////////////////////////////////////////////////////////
        //PARA PROBAR
        //sprintf (stdout,"/sys/class/gpio/gpio%s/direction", leds[i].pin);
//        printf("destino: %s\n", destino);
//
//        printf("CHECK POINT: %s\n", leds[i].pin);
    //////////////////////////////////////////////////////////////////////////////////////    
        if ((handle_direction = fopen (destino,"w"))==NULL)
        {
            printf("Cannot open DIRECTION File\n");
            exit(1); 
        }
        if((nWritten = fputs(leds[i].direction,handle_direction)) == -1)
        {
            printf("Cannot open DIRECTION pin. Try again later.\n");
            exit(1);
        }
//        else
//        {
//            printf("DIRECTION File for PIN opened succesfully\n");
//        }
        fclose(handle_direction);
    }

/////////////////////////////////////////// set_pin_zero_or_one ///////////////////////////////////////
//                                                                                                   //
// Pone el pin en 0 o 1 de acuerdo a lo que la estructura  indique.                                  //
// Recibe: el numero de pin (No el numero que figura en la Raspberry Pi, sino que el numero de bit.  //
// y el arreglo de estructuras de leds                                                               //
// Devuelve: Nada.                                                                                   //
//                                                                                                   //
///////////////////////////////////////////////////////////////////////////////////////////////////////

    void set_pin_zero_or_one (int i,pinsT leds[])
    {
        FILE * handle;
        char destino[50];
        sprintf (destino,"/sys/class/gpio/gpio%s/value", leds[i].pin);
            
        if ((handle = fopen (destino,"w"))==NULL)
        {
            printf("Cannot open device. Try again later. \n");
            exit(1); 
        }
//        else
//        {
//            printf("Device successfully opened\n");
//        }
        
        if(fputc(leds[i].value,handle) == -1)
        {
            printf(" Clr_Pin: Cannot write to file. Try again later.\n");
            exit(1);
        }
        //else
        //{
        //    printf("Clr_Pin write to file %s (handle=%X) successfully done\n", * handle);
        //}
        fclose(handle);
    }
     
///////////////////////////////////////////unexport_all_pins///////////////////////////////////////////
//                                                                                                   //
// Hace un unexport de los pines que se usaron.                                                      //
// Recibe: arreglo de estructuras de leds                                                            //
// Devuelve: Nada.                                                                                   //
//                                                                                                   //
///////////////////////////////////////////////////////////////////////////////////////////////////////
    
    void unexport_all_pins(pinsT leds[])
    {
        FILE *handle_unexport;
        int nWritten, i;

        for (i=0; i<=CANT_LEDS; i++)
        {
            if ((handle_unexport = fopen ("/sys/class/gpio/unexport","w"))==NULL)
            {
                printf("Cannot open UNEXPORT File. Try again later.\n");
                exit(1);
            }
         
            nWritten=fputs(leds[i].pin , handle_unexport);
         
            if (nWritten==-1)
            {
                printf("Cannot open UNEXPORT PIN. Try again later.\n");
                exit(1); 
            }
//            else
//                printf("UNEXPORT File opened succesfully \n");
            fclose(handle_unexport);
        }
    }
     
     
