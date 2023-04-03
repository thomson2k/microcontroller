// PA.0 -> D0 , GND -> K1 , PD2 -> W1
#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 1000000UL
#include <util/delay.h>

//obsluga przerwania INT0
ISR(INT0_vect) {
	_delay_ms(10);
	// jezeli po czasie 10ms przycisk jest niewcisniety przechodzimy do instrukcji
	if(PIND & (1<<PD2)) {
		return;
	}
	TCNT1 = 58250; //poczatkowa wartosc timera
	TCCR1B |= (1<<CS11) | (1<<CS10); //ustawienie prescalera czyli start timera
	PORTA |= (1<<PA0); // w��czenie diody LED
}

//obsluga przerwania TIMER1
ISR(TIMER1_OVF_vect) {
	TCCR1B &= ~((1<<CS11) | (1<<CS10)); //wyzerowanie prescalera czyli stop timer
	PORTA &= ~(1<<PA0); // wylaczenie diody led
}


int main(void) {
	cli(); // wlazcneie przerwan
	
	DDRA |= (1<<PA0); // ustawienie portu PA.0 na wyjscie
	DDRD &= ~(1<<PD2); // ustawienie portu PD.2 na wejscie
	PORTD |= (1<<PD2);
	DDRC = 0xFF; // ustawienie PORTC na wyjscie
	
	MCUCR |= (1<<ISC01); //INT 0 zbocze spadajace
	GICR |= (1<<INT0);	// 
	
	TIMSK |= (1<<TOIE1); //TIMER1 - zezwolenie na przerwanie przy przepelnieniu
	
	sei(); // globalne zezwolenie na przerwania
	
	while (1)
	{
		PORTC = 0xFF; //wszystkie diody zapalone
		_delay_ms(500);
		PORTC = 0x00; //wszystkie diody zgaszone
		_delay_ms(500);
	}
}