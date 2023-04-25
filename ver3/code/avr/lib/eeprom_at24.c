#include <avr/io.h>

// EEPROM(AT24) Write
unsigned char AT24C_write_byte(unsigned int addr,unsigned char data){
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

    TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO); //STOP

    return 1;
}

// EEPROM(AT24) Read
unsigned char AT24C_read_byte(unsigned int addr){
    unsigned char data;

    //Random read
    TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN); //START
    while(!(TWCR & (1<<TWINT)));

    //[device addr (0b10100000)] + [11bit addr (상위 3자리)] + [W:0]
    TWDR = 0xA0 | ((addr>>7) & 0x000E);
    TWCR = (1<<TWINT)|(1<<TWEN);            //전송
    while(!(TWCR & (1<<TWINT)));

    //[11bit addr (하위 8자리)]
    TWDR = 0x00ff & (addr);
    TWCR = (1<<TWINT)|(1<<TWEN);            //전송
    while(!(TWCR & (1<<TWINT)));

    TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN); //START
    while(!(TWCR & (1<<TWINT)));

    //[device addr (0b10100000)] + [11bit addr (상위 3자리)] + [R:1]
    TWDR = 0xA0 | ((addr>>7) & 0x0E) | 0x01;
    TWCR = (1<<TWINT)|(1<<TWEN);            //전송
    while(!(TWCR & (1<<TWINT)));

    TWCR = (1<<TWINT)|(1<<TWEN);            //전송
    while(!(TWCR & (1<<TWINT)));

    data = TWDR;                            //data 읽기
    TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO); //STOP

    return data;
}
