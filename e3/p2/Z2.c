#include <avr/io.h>
#include <avr/interrupt.h>

int main(void) {
	cli(); // wylaczamy przerwania

	DDRD |= (1<<PD5); // ustawiamy OC1A na wyjscie
	
	//timer zlicza do wartosci w ICR1 - konfigurucja aby uzyskac okres przebiegu na OC1A
	TCCR1A |= (1<<WGM11) | (1<<COM1A1); //zerowanie OC1A przy porownaniu
	TCCR1B |= (1<<WGM12) | (1<<WGM13); //tryb fast pwm
	TCCR1B |= (1<<CS11) | (1<<CS10); // prescaler 64  wystartowanie timera
	ICR1 = 8906; // ICR1 = ilosc cykli - 1 //35625
	OCR1A = 2968; //czas trwania jedynki na OC1A
	
	sei(); //  globalne zezwolenie na przerwania
	
	while (1){
		// main loop
	}
}
