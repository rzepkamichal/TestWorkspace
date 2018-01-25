#include <avr/io.h>
#include <util/delay.h>

int main(void){

	DDRA |= 0xFF;
	DDRC |=0xFF;
	DDRD |=0xFF;

	PORTA |= 0xFF;
	PORTD |= 0xFF;
	PORTC |= 0xFF;

	_delay_ms(10000);

	PORTA = 0x00;
	PORTD = 0x00;
	PORTC = 0x00;

	PORTA |=(1<<0);
	_delay_ms(1000);
	PORTA |=(1<<1);
	_delay_ms(1000);
	   PORTA |=(1<<2);
	_delay_ms(1000);
	PORTA |=(1<<3);
	_delay_ms(1000);
	PORTA |=(1<<4);
	_delay_ms(1000);
	PORTA |=(1<<5);
	_delay_ms(1000);
	PORTA |=(1<<6);
	_delay_ms(1000);
	PORTA |=(1<<0);


	PORTA &=~(1<<6);
	_delay_ms(1000);
	PORTA &=~(1<<5);
	_delay_ms(1000);
	PORTA &=~(1<<4);
	_delay_ms(1000);
	PORTA &=~(1<<3);
	_delay_ms(1000);
	PORTA &=~(1<<2);
	_delay_ms(1000);
	PORTA &=~(1<<1);
	_delay_ms(1000);
	PORTA &=~(1<<0);

	PORTC |=(1<<0);
	_delay_ms(1000);
	PORTC |=(1<<1);
	_delay_ms(1000);
    PORTC |=(1<<2);
	_delay_ms(1000);
	PORTC |=(1<<3);
	_delay_ms(1000);
	PORTC |=(1<<4);
	_delay_ms(1000);
	PORTC |=(1<<5);
	_delay_ms(1000);
	PORTC |=(1<<6);
	_delay_ms(1000);
	PORTC |=(1<<0);

	PORTC &=~(1<<6);
	_delay_ms(1000);
	PORTC &=~(1<<5);
	_delay_ms(1000);
	PORTC &=~(1<<4);
	_delay_ms(1000);
	PORTC &=~(1<<3);
	_delay_ms(1000);
	PORTC &=~(1<<2);
	_delay_ms(1000);
	PORTC &=~(1<<1);
	_delay_ms(1000);
	PORTC &=~(1<<0);

	PORTD |=(1<<2);
	_delay_ms(1000);
	PORTD |=(1<<3);
	_delay_ms(1000);
    PORTD |=(1<<5);
	_delay_ms(1000);
	PORTD |=(1<<6);

	PORTD &=~(1<<6);
	_delay_ms(1000);
	PORTD &=~(1<<5);
	_delay_ms(1000);
	PORTD &=~(1<<3);
	_delay_ms(1000);
	PORTD &=~(1<<3);
	_delay_ms(1000);
	PORTD &=~(1<<2);

	PORTA |=(1<<0);
	_delay_ms(1000);
	PORTA |=(1<<1);
	_delay_ms(1000);
	PORTA |=(1<<2);
	_delay_ms(1000);
	PORTA |=(1<<3);
	_delay_ms(1000);
	PORTA |=(1<<4);
	_delay_ms(1000);
	PORTA |=(1<<5);
	_delay_ms(1000);
	PORTA |=(1<<6);
	_delay_ms(1000);
	PORTA |=(1<<0);
	_delay_ms(1000);
	PORTC |=(1<<0);
	_delay_ms(1000);
	PORTC |=(1<<1);
	_delay_ms(1000);
	PORTC |=(1<<2);
	_delay_ms(1000);
	PORTC |=(1<<3);
	_delay_ms(1000);
	PORTC |=(1<<4);
	_delay_ms(1000);
	PORTC |=(1<<5);
	_delay_ms(1000);
	PORTC |=(1<<6);
	_delay_ms(1000);
	PORTC |=(1<<0);
	_delay_ms(1000);
	PORTD |=(1<<2);
	_delay_ms(1000);
	PORTD |=(1<<3);
	_delay_ms(1000);
	PORTD |=(1<<5);
	_delay_ms(1000);
	PORTD |=(1<<6);
	_delay_ms(10000);

	PORTA =0x00;
	PORTB =0x00;
	PORTC=0x00;

	for (int i=0;i<20;i++){
		PORTA|=0xFF;
		_delay_ms(500);
		PORTA=0x00;
		PORTC|=0xFF;
		_delay_ms(500);
		PORTC=0x00;
		PORTD|=0xFF;
		_delay_ms(500);
		PORTD=0x00;
	}

	for (int i=0;i<20;i++){
			PORTA|=0xFF;
			_delay_ms(300);
			PORTA=0x00;
			PORTD|=0xFF;
			_delay_ms(300);
			PORTD=0x00;
			PORTC|=0xFF;
			_delay_ms(300);
			PORTC=0x00;
		}

	for (int i=0;i<30;i++){
			PORTA|=0xFF;
			_delay_ms(100);
			PORTA=0x00;
			PORTC|=0xFF;
			_delay_ms(100);
			PORTC=0x00;
			PORTD|=0xFF;
			_delay_ms(100);
			PORTD=0x00;
		}

	_delay_ms(3000);

	for(int i=0;i<3;i++){
	for(int i=0;i<8;i++){
		PORTA |= (1<<i);
		_delay_ms(400);
		PORTA &=~(1<<i);
	}

	for(int i=0;i<8;i++){
			PORTC |= (1<<i);
			_delay_ms(400);
			PORTC &=~(1<<i);
		}

	PORTD|=(1<<2);
	_delay_ms(400);
	PORTD&=~(1<<2);
	PORTD|=(1<<3);
	_delay_ms(400);
	PORTD&=~(1<<3);
	PORTD|=(1<<5);
	_delay_ms(400);
	PORTD&=~(1<<5);
	PORTD|=(1<<6);
	_delay_ms(400);
	PORTD&=~(1<<6);
	}
	PORTA |=(1<<0);
		_delay_ms(1000);
		PORTA |=(1<<1);
		_delay_ms(1000);
		PORTA |=(1<<2);
		_delay_ms(1000);
		PORTA |=(1<<3);
		_delay_ms(1000);
		PORTA |=(1<<4);
		_delay_ms(1000);
		PORTA |=(1<<5);
		_delay_ms(1000);
		PORTA |=(1<<6);
		_delay_ms(1000);
		PORTA |=(1<<0);
		_delay_ms(1000);
		PORTC |=(1<<0);
		_delay_ms(1000);
		PORTC |=(1<<1);
		_delay_ms(1000);
		PORTC |=(1<<2);
		_delay_ms(1000);
		PORTC |=(1<<3);
		_delay_ms(1000);
		PORTC |=(1<<4);
		_delay_ms(1000);
		PORTC |=(1<<5);
		_delay_ms(1000);
		PORTC |=(1<<6);
		_delay_ms(1000);
		PORTC |=(1<<0);
		_delay_ms(1000);
		PORTD |=(1<<2);
		_delay_ms(1000);
		PORTD |=(1<<3);
		_delay_ms(1000);
		PORTD |=(1<<5);
		_delay_ms(1000);
		PORTD |=(1<<6);

		PORTA=0x00;
		PORTC=0x00;
		PORTD=0x00;

		_delay_ms(800);
		PORTA|=0xFF;
		PORTC|=0xFF;
		PORTD|=0xFF;

		_delay_ms(800);
		PORTA=0x00;
				PORTC=0x00;
				PORTD=0x00;

				_delay_ms(800);
						PORTA|=0xFF;
						PORTC|=0xFF;
						PORTD|=0xFF;

						_delay_ms(800);
							PORTA=0x00;
									PORTC=0x00;
									PORTD=0x00;

									_delay_ms(800);
															PORTA|=0xFF;
															PORTC|=0xFF;
															PORTD|=0xFF;



}
