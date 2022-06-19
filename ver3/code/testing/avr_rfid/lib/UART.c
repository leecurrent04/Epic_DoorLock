//
// Created by whale on 22. 5. 8.
//

#include "../include/UART.h"

void UART_INIT(void){
    UCSR0A |= _BV(U2X0);                // speed 2X

    UBRR0H = 0x00;                      // Baud Rate
    UBRR0L = 207;                       // 9600

    // 비동기, 8비트 데이터, 패리티 없음. 1비트 정지 비트 모드
    UCSR0C |= 0x06;
    UCSR0B |= _BV(RXEN0);               // 송수신 가능
    UCSR0B |= _BV(TXEN0);
}

unsigned char UART_received(void){      // 1바이트 수신
    while( !(UCSR0A & (1<<UDRE0)) );
    return UDR0;
}

void UART_transmit(unsigned char data){ // 1바이트 송신
    while( !(UCSR0A & (1<<UDRE0)) );    // 데이터 송신 가능 대기
    UDR0 = data;                        // 데이터 전송
}

void UART_printString(char *str){       // 문자열 송신
    for( int i=0; str[i]; i++)          // '\0' 문자를 만날 때까지 반복
        UART_transmit(str[i]);          // 바이트 단위 출력
}

void UART_print16bitNumber(uint16_t no){
    char numString[6] = "0";
    int i, index = 0;

    if(no > 0){
        for(i = 0; no!=0 ; i++){
            numString[i] = no % 10 +'0';
            no = no / 10;
        }
        numString[i] = '\0';
        index = i - 1;
    }

    for (i = index; i >= 0; i--)
        UART_transmit(numString[i]);

}