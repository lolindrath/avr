#include <inttypes.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

#include "atmega328p.h"

#define TIMER1_PWM_INIT _BV(WGM10) | _BV(WGM11) | _BV(COM1A1)
#define TIMER1_CLOCKSOURCE _BV(CS12)
#define TIMER1_TOP 255
#define PWM_INCR 16

enum { UP, DOWN };

ISR (TIMER1_OVF_vect)
{
	/*
	static uint16_t pwm;
	static uint8_t direction;

	switch(direction)
	{
		case UP:
			pwm += PWM_INCR;
			if(pwm == TIMER1_TOP)
				direction = DOWN;
			break;
		case DOWN:
			pwm -= PWM_INCR;
			if(pwm == 0)
				direction = UP;
			break;
	}
	*/

	OCR1A = 16;
}

int main (void)
{
	TCCR1A = TIMER1_PWM_INIT;

	TCCR1B |= TIMER1_CLOCKSOURCE;

	OCR1A = 0;
	DDRB = _BV(PB1);
	TIMSK1 = _BV(TOIE1);
	sei();
	
    while(1)
    {
		sleep_mode();
    }
   
    return(0);
}

