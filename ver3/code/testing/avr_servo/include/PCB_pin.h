//
// Created by whale on 22. 5. 13.
//

#ifndef AVR_PCB_PIN_H
#define AVR_PCB_PIN_H

#define LED_C0 0x01     // PC0
#define LED_C1 0x02     // PC1
#define LED_C2 0x04     // PC2
//#define BUZZ_C3 0x08    // PC3
#define BUZZ_C3 0x01    // PC3
#define BTN_D2 0x04     // PD2
#define BTN_D3 0x08     // PD3
#define BTN_D4 0x10     // PD4
#define D_BTN_D6 0x40   // PD6

#define BuzzerTime 500
#define BtnDTime 100

#define PULSE_MIN 1300
#define PULSE_MID 3000
#define PULSE_MAX 4700

uint8_t doorState;
uint8_t btnPressed;                         // 버튼의 눌림 기록


//Function
uint8_t checkRFID(uint8_t);                 // 카드를 확인(1-관리자 권한만 활성화, return 1: Error)
uint8_t readRFID(uint16_t *, uint16_t *);   // 카드 정보 읽어오기
void doorOpen();
void INIT_TIMER0(void);

#endif //AVR_PCB_PIN_H
