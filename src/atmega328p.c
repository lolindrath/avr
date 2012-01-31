#include <avr/io.h>
#include <util/delay.h>
#include "atmega328p.h"

void delay_ms(uint16_t x)
{
	while(x)
	{
		_delay_ms(1);
		x--;
	}
}

void data_direction(volatile uint8_t *data_reg, uint8_t pin, uint8_t mode)
{
	if(mode == INPUT)
	{
		*data_reg &= ~_BV(pin);
	}
	else if(mode == OUTPUT)
	{
		*data_reg |= _BV(pin);
	}
}

void digital_write(volatile uint8_t *port, uint8_t pin, uint8_t value)
{
	if(value == HIGH)
	{
		*port |= _BV(pin);
	}
	else if(value == LOW)
	{
		*port &= ~_BV(pin);
	}
}





