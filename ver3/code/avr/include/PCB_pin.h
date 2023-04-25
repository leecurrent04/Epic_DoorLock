//
// Created by leecurrent04 on 22. 5. 13.
//

#ifndef AVR_PCB_PIN_H
#define AVR_PCB_PIN_H

#include "mfrc522.h"

#define LED_C0 0x01     // PC0
#define LED_C1 0x02     // PC1
#define LED_C2 0x04     // PC2
#define BUZZ_C3 0x08    // PC3
#define BTN_D2 0x04     // PD2
#define BTN_D3 0x08     // PD3
#define BTN_D4 0x10     // PD4
#define D_BTN_D6 0x40   // PD6
#define ServoPin 0x20   // PD5

#define BuzzerTime 500
#define BtnDTime 100

#define Servo_PulseNum 20

uint16_t card_Num;

uint8_t doorState;
uint8_t btnPressed;     // 버튼의 눌림 기록

// mfc522
uint8_t byte;
uint8_t str[MAX_LEN];

//Function
uint8_t checkRFID(uint8_t,uint16_t card_Num);
uint8_t readRFID(uint16_t *, uint16_t *, uint16_t *, uint16_t *);

void board_setup(void);
void beep_buzzer(void);
void doorOpen(void);
void doorClose(void);

unsigned char AT24C_write_byte(unsigned int,unsigned char);
unsigned char AT24C_read_byte(unsigned int addr);

#endif //AVR_PCB_PIN_H
