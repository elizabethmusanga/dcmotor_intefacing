/*
 * DC_Motor.c
 *
 * Created: 11/9/2021 2:55:22 PM
 * Author : eliza
 */ 

#define F_CPU 8000000UL			/* Define CPU Frequency 8MHz */ 
#include <avr/io.h> 
#include <avr/interrupt.h> 
#include <stdio.h> 
#include <util/delay.h> 
#include "DC_Motor.h" 
volatile uint8_t Direction = 0;

/* Function that does the pin definitions and setup for GPI0, interrupt and PWM */ 
void setup(){ 
	DDRB = 0xFF;		/* Make PORTB as output Port */ 
	DDRB &= ~(1<<PB2); /* Make INT2 pin as Input */ 
	DDRB |= (1<<PB3); /* Make OC0 pin as Output */ 
	GICR = (1<<INT2); /* Enable INT2*/ 
	MCUCSR = (1<<ISC2); /* Trigger INT2 on Rising Edge triggered */ 
	sei(); /* Enable Global Interrupt */ 
	ADC_Init(); /* Initialize ADC */ 
	TCNT0 = 0; /* Set timer0 count zero */ 
	TCCR0 = (1<<WGM00)|(1<<WGM01)|(1<<COM01)|(1<<CS00)|(1<<CS01);/* Set Fast PWM with Fosc/64 Timer0 clock */ 
	}
	
/* Interrupt ISR function */ 
ISR(INT2_vect){ 
	Direction = ~Direction; /* Toggle Direction */
	_delay_ms(50); /* Software de-bouncing control delay */ 
	} 
	
	
	

	
int main(void)
{
    setup(); 
	while(1) 
	{
		 if (Direction !=0) /* Rotate DC motor Clockwise */ 
		 PORTB = 0x01; else /* Else rotate DC motor Anticlockwise */ 
		 PORTB = 0x02; 
		 OCR0 = (ADC_Read(0)/4); /* Read ADC and map it into 0-255 to write in OCR0 register*/
	}
}

