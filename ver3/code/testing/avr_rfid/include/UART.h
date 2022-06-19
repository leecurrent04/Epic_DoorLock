//
// Created by whale on 22. 5. 8.
//

#ifndef _UART_H
#define _UART_H

#include <avr/io.h>

void UART_INIT(void);
unsigned char UART_received(void);
void UART_transmit(unsigned char data);
void UART_printString(char *str);
void UART_print16bitNumber(uint16_t);

#endif //AVR_UART_H
