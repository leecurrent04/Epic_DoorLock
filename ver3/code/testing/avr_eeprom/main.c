#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "./include/UART.h"

unsigned char AT24C_write_byte(unsigned int,unsigned char);
unsigned char AT24C_read_byte(unsigned int addr);

int main(){
    UART_INIT();
    UART_printString("start\n");

    //TWI
    TWCR = (1<<TWEN);
    TWBR = 12;    //400khz

    for(unsigned int addr=0;addr<=10;addr++){
        if(AT24C_write_byte(addr,addr/4)==0){
            //Write Failed
            char temp[4]={0,};
            sprintf(temp,"%d",addr);
            UART_printString(addr);
            UART_printString(" : Fail\n\r");

            _delay_ms(1000);
            break;
        }
        _delay_ms(10);    //저장 시간 간격 필요함
    }

    _delay_ms(1000);

    //주소 0~1023 에 저장된 값 확인
    for(unsigned int addr=0;addr<=10;addr++)
    {
        char tempA[4]={0,};
        sprintf(tempA,"%d:",addr);
        UART_printString(tempA);

        char tempD[4]={0,};
        sprintf(tempD,"%d ",AT24C_read_byte(addr));
        UART_printString(tempD);

        if((addr%12) == 11){
            UART_printString("\n\r");
        }
    }

    while(1){
    }
}

unsigned char AT24C_write_byte(unsigned int addr,unsigned char data)
{
    // Byte write
    // START
    TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
    while(!(TWCR & (1<<TWINT)));            //TWINT flag 기다림

    //[device addr (0b10100000)] + [11bit addr (상위 3자리)] + [W:0]
    TWDR = 0xA0 | ((addr>>7) & 0x000E);
    TWCR = (1<<TWINT)|(1<<TWEN);            //전송
    while(!(TWCR & (1<<TWINT)));

    //[11bit addr (하위 8자리)]
    TWDR = 0x00ff & (addr);
    TWCR  =(1<<TWINT)|(1<<TWEN);            //전송
    while(!(TWCR & (1<<TWINT)));

    //data 쓰기
    TWDR = data;
    TWCR = (1<<TWINT)|(1<<TWEN);            //전송
    while(!(TWCR & (1<<TWINT)));

    TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);    //STOP

    return 1;
}

unsigned char AT24C_read_byte(unsigned int addr)
{
    unsigned char data;

    //Random read
    TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);    //START
    while(!(TWCR & (1<<TWINT)));

    //[device addr (0b10100000)] + [11bit addr (상위 3자리)] + [W:0]
    TWDR = 0xA0 | ((addr>>7) & 0x000E);
    TWCR = (1<<TWINT)|(1<<TWEN);        //전송
    while(!(TWCR & (1<<TWINT)));

    //[11bit addr (하위 8자리)]
    TWDR = 0x00ff & (addr);
    TWCR = (1<<TWINT)|(1<<TWEN);            //전송
    while(!(TWCR & (1<<TWINT)));

    TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);    //START
    while(!(TWCR & (1<<TWINT)));

    //[device addr (0b10100000)] + [11bit addr (상위 3자리)] + [R:1]
    TWDR = 0xA0 | ((addr>>7) & 0x0E) | 0x01;
    TWCR = (1<<TWINT)|(1<<TWEN);            //전송
    while(!(TWCR & (1<<TWINT)));

    TWCR = (1<<TWINT)|(1<<TWEN);            //전송
    while(!(TWCR & (1<<TWINT)));

    data = TWDR;                            //data 읽기
    TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);    //STOP

    return data;
}