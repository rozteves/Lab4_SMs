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

enum States{Start, button, lock, unlock, hash} state;

void Tick(){
	//Transitions
	switch(state){
		case Start:
			state = button;
			break;
		case button:
			if((PINA & 0x07) == 0x04){
				state = hash;
			}
			else
				state = button;
			break;
		case hash:
			if((PINA & 0x07) == 0x04){
				state = hash;
			}
			else if((PINA & 0x07) == 0x00){
				state = unlock;
			}
			else 
				state = button;
			break;
		case unlock:
			if((PINA & 0x07) == 0x00){
				state = unlock;
			}
			else if((PINA & 0x07) == 0x02){
				state = lock;
			}
			else
				state = button;
			break;
		case lock:
			if((PINA & 0x80) == 0x80){
				state = button;
			}
			else
				state = lock;
			break;
		default:
			state = button;
			break;
	}
	//Actions
	switch(state){
		case Start:
			break;
		case button:
		case hash:
		case unlock:
			PORTB = 0x00;
			break;
		case lock:
			PORTB = 0x01;
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
