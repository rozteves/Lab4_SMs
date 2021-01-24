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

//initial start, waitA0, pressA0, waitA1, pressA1
enum States{Start, offRelease, onPress, onRelease, offPress} state;

void Tick(){
	switch(state){
		case Start:
			state = offRelease;
			break;
		case offRelease:
			if((PINA & 0x01) == 0x01){
				state = onPress;
			}
			break;
		case onPress:
			if((PINA & 0x01) != 0x01){
				state = onRelease;
			}
			break;
		case onRelease:
			if((PINA & 0x01) == 0x01){
				state = offPress;
			}
			break;
		case offPress:
			if((PINA & 0x01) != 0x01){
				state = offRelease;
			}
			break;
		default:
			state = Start;
			break;
	}
	switch(state){//state actions
		case Start:
			break;
		case offRelease:
			PORTB = 0x01;
			break;
		case onPress:
			PORTB = 0x02;
			break;
		case onRelease:
			break;
		case offPress:
			PORTB = 0x01;
		default:
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
