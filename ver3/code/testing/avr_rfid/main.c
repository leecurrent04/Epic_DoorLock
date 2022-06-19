#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#include "./include/UART.h"
#include "./include/mfrc522.h"
#include "./include/spi.h"

int main(void){
    UART_INIT();        // UART 통신 활성화

    uint8_t byte;       //
    uint8_t str[MAX_LEN];
    _delay_ms(50);

    spi_init();         // SPI 통신 활성화
    _delay_ms(1000);

    //init reader
    mfrc522_init();

    //check version of the reader
    byte = mfrc522_read(VersionReg);
    if(byte == 0x92)
    {
        UART_printString("MIFARE RC522v2\n");
    }else if(byte == 0x91 || byte==0x90)
    {
        UART_printString("MIFARE RC522v1\n");
    }else
    {
        UART_printString("No reader found\n");
    }

    byte = mfrc522_read(ComIEnReg);
    mfrc522_write(ComIEnReg,byte|0x20);
    byte = mfrc522_read(DivIEnReg);
    mfrc522_write(DivIEnReg,byte|0x80);

    _delay_ms(1500);

    while(1){
        byte = mfrc522_request(PICC_REQALL,str);

        if(byte == CARD_FOUND)
        {
            byte = mfrc522_get_card_serial(str);
            if(byte == CARD_FOUND)
            {
                for(byte=0;byte<4;byte++){
                //for(byte=0;byte<8;byte++){
                    //UART_transmit(str[byte]);
                    char temp[3]={0,};
                    sprintf(temp,"0x%02X ",str[byte]);
                    UART_printString(temp);
                }
                UART_printString("\n");
                char temp[2]={0,};
                sprintf(temp,"0x%02X ",0x0A);
                UART_printString(temp);

                char temp2[2]={0,};
                sprintf(temp2,"%d",0x0A==str[0]);
                UART_printString(temp2);

                _delay_ms(2500);
            }
            else
            {
                UART_printString("Error");
            }
        }

        _delay_ms(1000);
    }
}


