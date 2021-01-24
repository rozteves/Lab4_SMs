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

enum States{Start, button, check, press, release} state;

void Tick(){
	//Transitions
	switch(state){
		case Start:
			state = button;
			break;
		case button:
			if(PINA == 0x04){
				state = check;
			}
			else
				state = button;
			break;
		case check:
			if(PINA == 0x04){
				state = check;
			}
			else if(PINA == 0x00){
				state = release;
			}
			else
				state = button;
			break;
		case release:
			if(PINA == 0x00){
				state = release;
			}
			else if(PINA == 0x02){
				state = press;
			}
			else
				state = button;
			break;
		case press:
			state = button;
			break;
		default:
			state = Start;
			break;
	}
	//Actions
	switch(state){
		case Start:
			break;
		case button:
		case check:
		case release:
			if(PINA == 0x80){
				PORTB = 0x00;
			}
			break;
		case press:
			if(PINA == 0x80){
				PORTB = 0x00;
			}
			else if(PORTB == 0x00){//change lock
				PORTB = 0x01;
			}
			else if(PORTB == 0x01){//change lock
				PORTB = 0x00;
			}
			else
				PORTB = 0x00;
			break;	
		default:
			PORTB = 0x00;
			break;
	}
}

int main(void) {
    /* Insert DDR and PORT initializations */
    state = Start;
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    /* Insert your solution below */
    while (1) {
	Tick();
    }
    return 1;
}
