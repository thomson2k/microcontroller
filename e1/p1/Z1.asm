//  PA1=w1 k4=gnd PA0=d2
.include "m32def.inc"
	
	.org 0x00
	jmp main

	.org 0x100
main: 			; program g��wny

	sbi DDRA, 0 ; wejscie bitu diody 
	cbi DDRA, 1 ; wyjscie bitu przycisku
	sbi PORTA, 1 ; przerzucenie do bitu PORTA

loop:			; pocz�tek p�tli g��wnej
	sbic PINA, 1 ; pominiecie instrukcji przy nacisnieciu przycisku
	sbi PORTA, 0 ; ustawienie bitu czyli za��czenie diody
	sbis pina, 1 ; pominiecie instrukcji przy nie naci�nietym przycisku
	cbi porta, 0 ; czyszczenie bitu czyli zgaszenie diody

		
	rjmp loop 	; wr�� na pocz�tek p�tli g��wnej

