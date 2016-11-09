

/////////////////////////////////////////////// INPUT CONTROL /////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                   //
//  Impresion en pantalla de aquello necesario por el programa.                                      //
//                                                                                                   //
///////////////////////////////////////////////////////////////////////////////////////////////////////

#include "input_control.h"





MY_REG validacion (char c, pinsT leds[], MY_REG port_a) //Recibo el valor de la tecla ingresada y el arreglo donde está la info de los pines.
{
    int n;
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
            
        case 'b': //Los leds prendidos parpadean (se apagan y se vuelven a prender)
        {
            if(port_a.by.hi) //Si el puerto esta todo apagado no entro en blink
            {
               port_a = blink(leds, port_a); 
            }
            
            impresion(port_a);
            
        }
        break;
            
        case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7':
    
        {
            n = (c - 48);
            if(leds[n].value == '1')
            {
                leds[n].value = '0';
                set_pin_zero_or_one (n,leds);
                port_a = case_number_off (n,port_a);
            }
            else if (leds[n].value == '0')
            {
                leds[n].value = '1';
                set_pin_zero_or_one (n,leds);
                port_a = case_number_on (n,port_a);
            }
            
            
        }
        break;
        case ' ':   //Se prende un led y luego se apaga. Despues hace los mismo con el resto de los leds
        {
            port_a = cool (leds, port_a);
        }
        break;
    }
    return port_a;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                  BLINK
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

MY_REG blink (pinsT leds[], MY_REG port_a) //Funcion de Blink
{
    int k = 0, n;
    char c;
    for (n=0; n <= CANT_LEDS; n++)    //Se hace una copia del estado de los pines en el momento
    {
        leds[n].value_copy = leds[n].value;
    }

    while (c != 'b')
    {
        k = kbhit();
        if (k!=0)           //si se apreto un tecla la guardo
        {
            c = (fgetc(stdin));
        }
        else
        {
            for (n=0; n <= CANT_LEDS; n++)   //Apago todos los LEDs
                {
                    if (leds[n].value_copy == '1')
                    {
                        leds[n].value = '0';
                    }
                    set_pin_zero_or_one (n,leds);
                }
            port_a = case_blink (port_a);
            usleep(BLINK_SPEED);
            system("clear");

            for (n=0; n <= CANT_LEDS; n++)   //Vuelvo a prender los LEDs
            {
                if (leds[n].value_copy == '1')
                {
                    leds[n].value = '1';
                }
                set_pin_zero_or_one (n,leds);
            }
            impresion(port_a);
            usleep(BLINK_SPEED);
            system("clear");
        }

    }

    for (n=0; n <= CANT_LEDS; n++)   //Se guardan en value los estados de los pines antes del parpadeo.
    {
        leds[n].value = leds[n].value_copy;

    }
    return port_a;
    
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                          COOL
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

MY_REG cool (pinsT leds[], MY_REG port_a)
{
    MY_REG port_cool;
    int k=0, n;
    char c;
    
    for (n=0; n <= CANT_LEDS; n++)    //Se hace una copia del estado de los pines en el momento
    {
        leds[n].value_copy = leds[n].value;
    }
   
  //================================================================================================================================
    for (n=0; n <= CANT_LEDS; n++)   //Apago todos los LEDs
        {
            if (leds[n].value_copy == '1')
            {
                leds[n].value = '0';
            }
            set_pin_zero_or_one (n,leds);
        }
    
    port_cool.by.hi = 0x00;
    
    while(c != ' ')     //Hasta apretar SPACE nuevamente
    {
        for (n=0; (n <= CANT_LEDS) && (c != ' '); n++)
        {
            k = kbhit();
            if (k!=0)           //si se apreto un tecla la guardo
            {
                c = (fgetc(stdin));
            }
            //Prendo el LED n,
            leds[n].value = '1';
            set_pin_zero_or_one (n,leds);
            port_cool = case_number_on(n,port_cool);
            system("clear");
            impresion(port_cool);
            //Apago el LED n,
            usleep(COOL_SPEED);
            leds[n].value = '0';
            set_pin_zero_or_one (n,leds);
            port_cool = case_number_off(n,port_cool);
            system("clear");
            impresion(port_cool);

        }
    }
    
    
  //================================================================================================================================
  
    for (n=0; n <= CANT_LEDS; n++)   //Se guardan en value los estados de los pines antes del parpadeo.
    {
        leds[n].value = leds[n].value_copy;

    }
    for (n=0; n <= CANT_LEDS; n++)   //Vuelvo a prender los LEDs
            {
                set_pin_zero_or_one (n,leds);
            }
    impresion(port_a);
    return port_a;
}

