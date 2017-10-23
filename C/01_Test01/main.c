/*
 * main.c
 *
 *  Created on: 22.12.2016
 *      Author: sysoper
 */
#include <avr/io.h>
#include <util/delay.h>

int main(void){

	DDRD |= (1<<PD1);


	PORTD |= (1<<PD1);

}
