/*
 * Lab Section: 21
 * Assignment: Lab #4 Exercise #1
 * I acknowledge all content contained herein, excluding template
	or example code, is my own original work.
 */ 

#include <avr/io.h>

enum States{start, wait, pressed, stay} state;
unsigned char tmpB = 0x00;
unsigned char A = 0x00;
// Bit-access function

unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b)
{
	return (b ? (x | (0x01 << k)) : (x & ~(0x01 << k)));
}

unsigned char GetBit(unsigned char x, unsigned char k)
{
	return ((x & (0x01 << k)) != 0);
}


void B_SM_Tick()
{
	switch (state)
	{
		case start:
			tmpB = SetBit(tmpB, 0, 1);
			state = wait;
			break;
			
		case wait:
			if(GetBit(A, 0))
				state = pressed;
			else
				state = wait;
			break;
		
		case pressed:
			state = stay;
			break;
		
		case stay:
			if(!GetBit(A, 0))
				state = wait;
			else
				state = stay;
			break;
		
		default:
		break;
	}
	switch (state)
	{ //State Actions
		case start:
		break;
		
		case wait:
		break;
		
		case pressed:
		if(GetBit(tmpB, 0) == 1)
		{
			tmpB = SetBit(tmpB, 1, 1);
			tmpB = SetBit(tmpB, 0, 0);
		}
		else
		{
			tmpB = SetBit(tmpB, 1, 0);
			tmpB = SetBit(tmpB, 0, 1);
		}
		break;
		
		case stay:
		break;
		
		default:
		break;
	}
}

int main()
{
	DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as input
	DDRB = 0xFF; PORTB = 0x00; // Configure port B's 8 pins as outputs
	state = start;

	while(1)
	{	A = PINA & 0x01;
		B_SM_Tick();
		// 3) write results to port
		PORTB = tmpB;
	}
	return 0;
}

