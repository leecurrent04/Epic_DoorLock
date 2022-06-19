// 500
// 1500
// 2500
#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "./include/UART.h"
#define ServoPin 1<<PD7
int main(){
    DDRD |= (1<<PD5);
    UART_INIT();
    UART_printString("START\n");

    while(1){
        for(int k=0; k<100; k++) {
            for (int i = 0; i < 50; i++) {
                PORTD |= ServoPin;
                _delay_ms(0.5);
                PORTD &= ~ServoPin;
                _delay_ms(18.5);
            }
            _delay_ms(300);

            for (int i = 0; i < 50; i++) {
                PORTD |= ServoPin;
                _delay_ms(1.5);
                PORTD &= ~ServoPin;
                _delay_ms(18.5);
            }
            _delay_ms(300);
            char Ttemp[5]={0,};
            sprintf(Ttemp,"%d\n",k);
            UART_printString(Ttemp);
        }
    }
}


