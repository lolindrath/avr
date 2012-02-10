
#ifndef _ATMEGA328_ANDY_
#define _ATMEGA328_ANDY_

//#define F_CPU 8000000UL

#define PORT_B 1
#define PORT_C 2
#define PORT_D 3

#define PIN0 0
#define PIN1 1
#define PIN2 2
#define PIN3 3
#define PIN4 4
#define PIN5 5
#define PIN6 6
#define PIN7 7

#define OUTPUT 1
#define INPUT 0

#define HIGH 1
#define LOW 0


void delay_ms(uint16_t x);

void data_direction(volatile uint8_t *port, uint8_t pin, uint8_t mode);

void digital_write(volatile uint8_t *port, uint8_t pin, uint8_t value);

#endif


