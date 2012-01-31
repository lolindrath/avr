#include <inttypes.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

#include "atmega328p.h"

void led(int num)
{
	switch(num)
	{
		case 1:
			data_direction(&DDRC, PIN0, OUTPUT);
			data_direction(&DDRC, PIN1, OUTPUT);
			data_direction(&DDRC, PIN2, INPUT);
			digital_write(&PORTC, PIN0, HIGH);
			digital_write(&PORTC, PIN1, LOW);
			break;
		case 2:
			data_direction(&DDRC, PIN0, OUTPUT);
			data_direction(&DDRC, PIN1, OUTPUT);
			data_direction(&DDRC, PIN2, INPUT);
			digital_write(&PORTC, PIN0, LOW);
			digital_write(&PORTC, PIN1, HIGH);
			break;
		case 3:
			data_direction(&DDRC, PIN0, INPUT);
			data_direction(&DDRC, PIN1, OUTPUT);
			data_direction(&DDRC, PIN2, OUTPUT);
			digital_write(&PORTC, PIN1, HIGH);
			digital_write(&PORTC, PIN2, LOW);
			break;
		case 4:
			data_direction(&DDRC, PIN0, INPUT);
			data_direction(&DDRC, PIN1, OUTPUT);
			data_direction(&DDRC, PIN2, OUTPUT);
			digital_write(&PORTC, PIN1, LOW);
			digital_write(&PORTC, PIN2, HIGH);
			break;
		case 5:
			data_direction(&DDRC, PIN0, OUTPUT);
			data_direction(&DDRC, PIN1, INPUT);
			data_direction(&DDRC, PIN2, OUTPUT);
			digital_write(&PORTC, PIN0, HIGH);
			digital_write(&PORTC, PIN2, LOW);
			break;
		case 6:
			data_direction(&DDRC, PIN0, OUTPUT);
			data_direction(&DDRC, PIN1, INPUT);
			data_direction(&DDRC, PIN2, OUTPUT);
			digital_write(&PORTC, PIN0, LOW);
			digital_write(&PORTC, PIN2, HIGH);
			break;
	}
}

//int leds[7] = {0, 1, 0, 1, 0, 1, 0};
int *leds = 0;
int leds1[7] = {0, 1, 0, 1, 0, 1, 0};
int leds2[7] = {0, 0, 1, 0, 1, 0, 1};
int currentLed = 1;
int set = 1;
ISR(TIMER0_COMPB_vect)
{
	if(leds[currentLed] == 1)
	{
		led(currentLed);
		currentLed++;
	}
	else
	{
		currentLed++;
	}

	if(currentLed > 6)
	{
		currentLed = 1;
	}
}

int main (void)
{
	leds = leds1;
	TCCR0B |= ((1 << CS00) | (1 << CS01));
	TCCR0A |= (1 << WGM01);
	TIMSK0 |= (1 << OCIE0B);
	sei();
	OCR0A = 256;

    while(1)
    {
		/*
		for(int i = 1; i <= 6; i++)
		{
			led(i);
			delay_ms(50);
		}
		*/

		delay_ms(1);
		cli();

		if(set == 1)
		{
			set = 2;
			leds = leds1;
		}
		else
		{
			set = 1;
			leds = leds2;
		}
		sei();

    }
   
    return(0);
}

