//
// Created by whale on 22. 5. 8.
//

#include "../include/UART.h"

void UART_INIT(void){
    UCSR0A |= _BV(U2X0);    // speed 2X

    UBRR0H = 0x00;          // Baud Rate
    UBRR0L = 207;           // 9600

    UCSR0C |= 0x06;
    UCSR0B |= _BV(RXEN0);
    UCSR0B |= _BV(TXEN0);
}

unsigned char UART_received(void){
    while( !(UCSR0A & (1<<UDRE0)) );
    return UDR0;
}

void UART_transmit(unsigned char data){
    while( !(UCSR0A & (1<<UDRE0)) );
    UDR0 = data;
}

void UART_printString(char *str){
    for( int i=0; str[i]; i++)
        UART_transmit(str[i]);
}