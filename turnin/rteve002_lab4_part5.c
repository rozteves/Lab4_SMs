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

enum States{Start, loop, changeLock} state;

//global variables
unsigned char cnt = 0;
unsigned char prev = 0;
// #-X-Y-Z
unsigned char arr[8] = {0x04, 0x00, 0x01, 0x00, 0x02, 0x00, 0x01, 0x00};

void Tick(){
	//Transitions
	switch(state){
		case Start:
			state = loop;
			break;
		case loop:
			if(cnt == 7){
				state = changeLock;
			}
			else
				state = loop;
			break;
		case changeLock:
			state = Start;
			break;
		default:
			state = Start;
			break;
	}
	//Actions
	switch(state){
		case Start:
			break;
		case loop:
			if(PINA == 0x80){
				PORTB = 0x00;
				cnt = 0;
			}
			if(cnt < 8 && PINA == arr[cnt]){
				if(PINA == prev){
					cnt = cnt;
				}
				else
					cnt++;
				prev = PINA;
			}
			break;
		case changeLock: 
			if(PORTB == 0x00){
				PORTB = 0x01;
				cnt = 0;
			}
			else{
				PORTB = 0x00;
				cnt = 0;
			}
			prev = PINA;
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
