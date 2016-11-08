

/////////////////////////////////////////////// INPUT CONTROL /////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                   //
//  Impresion en pantalla de aquello necesario por el programa.                                      //
//                                                                                                   //
///////////////////////////////////////////////////////////////////////////////////////////////////////

#include "input_control.h"


int n;


MY_REG validacion (char c, pinsT leds[], MY_REG port_a) //Recibo el valor de la tecla ingresada y el arreglo donde está la info de los pines.
{
    switch (c)
    {
        case 's': //Se prenden todos los leds
        {
            for (n=0; n <= CANT_LEDS; n++)   //LEDS
            {
                leds[n].value = '1';
                set_pin_zero_or_one (n,leds);
            }
            port_a = case_set (port_a);
        }
        break;
            
        case 'c': //Se apagan todos los leds
        {
            for (n=0; n <= CANT_LEDS; n++)   //LEDS
            {
                leds[n].value = '0';
                set_pin_zero_or_one (n,leds);
            }
            port_a = case_clear (port_a);
        }
        break;
            
        case 'b': //Los leds prendidos parpadean (se apagan y se vuelven a prender) VER PARPADEOOOOO
        {
            for (n=0; n <= CANT_LEDS; n++)    //Se hace una copia del estado de los pines en el momento
            {
                leds[n].value_copy = leds[n].value;
                printf("value: %c\n", leds[n].value);
                printf("value_copy: %c\n", leds[n].value_copy);
            }
            int k = 0;
            
            while ((k == 0)) //ver
            {
                k = kbhit();
                for (n=0; n <= CANT_LEDS; n++)   //LEDS
                {
                    if (leds[n].value_copy == '1')
                    {
                        leds[n].value = ((leds[n].value_copy) - '1');
                        
                    }
                    set_pin_zero_or_one (n,leds);
                }
                //port_a = case_blink (port_a);
                sleep(1); //VER DE PONER OTRO TIMER
                //system("clear"); //esta bien dejar esto?
                //--k;
               
            
            
            
            }
            for (n=0; n <= CANT_LEDS; n++)   //Se guardan en value los estados de los pines antes del parpadeo.
            {
                leds[n].value = leds[n].value_copy;
                printf("value: %c\n", leds[n].value);
                printf("value_copy: %c\n", leds[n].value_copy);
            }
           // case_blink (port_a);
        }
        break;
            
        case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7':
    
        {
            n = (c - 48);
            //leds[n].value = (!(leds[n].value));
            leds[n].value = '1';
            set_pin_zero_or_one (n,leds);
            port_a = case_number (n,port_a);
        }
        break;
    }
    return port_a;
}


