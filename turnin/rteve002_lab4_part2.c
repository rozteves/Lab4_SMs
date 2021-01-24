/*	Author: lab
 *  Partner(s) Name: Roz Teves
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States{Start, check, inc, incPress, dec, decPress} state;

void Tick(){
	//Transitions
	switch(state){
		case Start:
			state = check;
			PORTC = 0x07;
			break;
		case check:
			if((PINA & 0x01) == 0x01){
				state = inc;
			}
			else if ((PINA & 0x02) == 0x02){
				state = dec;
			}
			break;
		case inc:
			state = incPress;
			break;
		case dec:
			state = decPress;
			break;
		case incPress:
			if((PINA & 0x01) == 0x01){
				state = incPress;
			}
			else
				state = check;
			break;
		case decPress:
			if((PINA & 0x02) == 0x02){
				state = decPress;
			}
			else
				state = check;
			break;
		default:
			state = Start;
			break;
	}
	//Actions
	switch(state){
		case Start:
			break;
		case check: 
			if((PINA & 0x03) == 0x03){
				PORTC = 0x00;
			}
			break;
		case inc:
			if(PORTC < 0x09){
				PORTC = PORTC + 1;
			}
			break;
		case incPress:
			if((PINA & 0x03) == 0x03){
				PORTC = 0x00;
			}
			break;
		case dec:
			if(PORTC > 0x00){
				PORTC = PORTC - 1;
			}
			break;
		case decPress:
			if((PINA & 0x03) == 0x03){
				PORTC = 0x00;
			}
			break;
		default:
			break;
	}
}

int main(void) {
    /* Insert DDR and PORT initializations */
    state = Start;
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;
    /* Insert your solution below */
    while (1) {
	Tick();
    }
    return 1;
}
