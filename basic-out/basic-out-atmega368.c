/*
    5-10-07
    Copyright Spark Fun Electronics� 2007
    Nathan Seidle
    nathan at sparkfun.com
    
    Example basic printf input/output
*/

#include <stdio.h>
#include <avr/io.h>

#define FOSC 16000000
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

#define sbi(var, mask)   ((var) |= (uint8_t)(1 << mask))
#define cbi(var, mask)   ((var) &= (uint8_t)~(1 << mask))

#define STATUS_LED 0

//Define functions
//======================
void ioinit(void);      // initializes IO
static int uart_putchar(char c, FILE *stream);
uint8_t uart_getchar(void);

static FILE mystdout = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);

void delay_ms(uint16_t x); // general purpose delay
//======================

int main (void)
{
	uint8_t x = 0;
	
    ioinit(); //Setup IO pins and defaults

    while(1)
    {
		x++;
	
		printf("Test it! x = %d", x);
		
		sbi(PORTC, STATUS_LED);
		delay_ms(500);

		cbi(PORTC, STATUS_LED);
		delay_ms(500);
    }
   
    return(0);
}

void ioinit (void)
{
    //1 = output, 0 = input
    DDRB = 0b11101111; //PB4 = MISO 
    DDRC = 0b11111111; //
    DDRD = 0b11111110; //PORTD (RX on PD0)

    //USART Baud rate: 9600
    UBRR0H = MYUBRR >> 8;
    UBRR0L = MYUBRR;
    UCSR0B = (1<<RXEN0)|(1<<TXEN0);
    
    stdout = &mystdout; //Required for printf init
}

static int uart_putchar(char c, FILE *stream)
{
    if (c == '\n') uart_putchar('\r', stream);
  
    loop_until_bit_is_set(UCSR0A, UDRE0);
    UDR0 = c;
    
    return 0;
}

uint8_t uart_getchar(void)
{
    while( !(UCSR0A & (1<<RXC0)) );
    return(UDR0);
}

//General short delays
void delay_ms(uint16_t x)
{
  uint8_t y, z;
  for ( ; x > 0 ; x--){
    for ( y = 0 ; y < 80 ; y++){
      for ( z = 0 ; z < 40 ; z++){
        asm volatile ("nop");
      }
    }
  }
}