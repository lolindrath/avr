#include <avr/io.h>
#include <util/delay.h>

#include "atmega328p.h"


int main (void)
{
	data_direction(&DDRC, PIN0, OUTPUT);
	data_direction(&DDRC, PIN1, OUTPUT);
	

    while(1)
    {
		digital_write(&PORTC, PIN0, LOW);
		digital_write(&PORTC, PIN1, HIGH);
		delay_ms(50);

		digital_write(&PORTC, PIN0, HIGH);
		digital_write(&PORTC, PIN1, LOW);
		delay_ms(50);
    }
   
    return(0);
}

