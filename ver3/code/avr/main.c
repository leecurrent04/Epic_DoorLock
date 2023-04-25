#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include <avr/wdt.h>
#include "./include/PCB_pin.h"

// RFID MFRC522
#include "./include/spi.h"
#include "./include/mfrc522.h"

// 관리자 key의 개수. 주의 요망!
#define cardAdmin_Num 1
uint8_t cardAdmin_UID[cardAdmin_Num][4] = {
        {0x00, 0x00, 0x00, 0x00}
};


int main(void){
    board_setup();

    while(1){
        // RFID 인식 안되면 리셋
        byte = mfrc522_read(VersionReg);
        if(byte != 0x92) {
            wdt_reset();
        }

        //==============================
        // 문 열기 버튼이 눌렸을 때
        if( (PIND&BTN_D2)!=BTN_D2 ){
            // 버튼이 처음 눌리면)
            if(!( (btnPressed&0b100) >>2) ) {
                btnPressed |= 0b100;    // 버튼 상태 변수를 변경

                // 문열기
                if( (PIND&D_BTN_D6)!=D_BTN_D6 && doorState == 0b00 ){
                    doorState = 0b11;
                    doorOpen();
                }
            }
        }
        else{
            // 버튼에서 손을 때면
            if((btnPressed&0b100)>>2){
                btnPressed&=0b011;      // 초기 상태로 변경
                _delay_ms(BtnDTime);
            }
        }

        //==============================
        // 등록 버튼이 눌렸을 때
        if( (PIND&BTN_D3)!=BTN_D3 ) {
            if(!((btnPressed&0b010)>>1)) {
                btnPressed |= 0b010;
            }
        }
        else{
            if((btnPressed&0b010)>>1) {
                btnPressed&=0b101;
                _delay_ms(BtnDTime);
                PORTC |= LED_C1;

                uint8_t exitState = 0;
                // 관리자 권한 카드 인식 될 때까지 대기
                while (0 != checkRFID(1,card_Num)) {
                    // 카드 최대 개수(2Kbyte, addr: 0~2048)
                    // 2048÷4-1=511
                    if(card_Num>=511){
                        PORTC |= BUZZ_C3|LED_C0|LED_C1;
                        _delay_ms(BuzzerTime);
                        PORTC &= ~(BUZZ_C3|LED_C0|LED_C1);

                        exitState =1;
                        break;
                    }

                    // 버튼 누르면 나가기
                    if ((PIND & BTN_D3) != BTN_D3) {
                        // 만약 버튼을 처음 누른다면
                        if (!((btnPressed & 0b010) >> 1)) {
                            btnPressed |= 0b010;

                            // Buzzer
                            beep_buzzer();
                            PORTC &= ~LED_C1;

                            exitState = 1;
                        }
                    }
                    else {
                        // 버튼이 이미 눌려져 있었다면
                        if ((btnPressed & 0b010) >> 1) {
                            btnPressed &= 0b101;
                            _delay_ms(BuzzerTime);
                            break;
                        }
                    }
                }
                if (exitState){
                    continue;     // 나가기
                }

                // Buzzer
                beep_buzzer();

                uint16_t aUID[4] = {0,};      // UID 값을 읽기 위한 메모리
                uint8_t breakState;           // 이중 반복문을 나가기 위한 변수

                // 카드 등록할 때까지 대기
                while (1) {
                    breakState = 1;

                    // 빈 카드가 아니라면
                    if (0 == readRFID(&aUID[0], &aUID[1], &aUID[2], &aUID[3])) {
                        // 관리자 카드가 아니면 break
                        for (int i = 0; i < cardAdmin_Num; i++) {
                            if ((cardAdmin_UID[i][0] == aUID[0]) && (cardAdmin_UID[i][1] == aUID[1])
                                && (cardAdmin_UID[i][2] == aUID[2]) && (cardAdmin_UID[i][3] == aUID[3])) {
                                breakState = 0;
                                break;
                            }

                        }
                        // 기존에 등록된 카드가 아니면 break
                        for (uint16_t i = 0; i < card_Num; i++) {
                            if ((AT24C_read_byte(4*(i+1)) == aUID[0]) && (AT24C_read_byte(4*(i+1)+1) == aUID[1])
                                && (AT24C_read_byte(4*(i+1)+2) == aUID[2])&& (AT24C_read_byte(4*(i+1)+3) == aUID[3])) {
                                breakState = 0;
                                break;
                            }

                        }
                        if (breakState){
                            break;
                        }
                    }
                }

                //카드 값을 저장
                for (int i = 0; i < 4; i++) {
                    AT24C_write_byte(4*(card_Num+1)+i,aUID[i]);
                    _delay_ms(10);
                }
                // 등록된 카드 수를 늘리고 저장
                card_Num++;
                AT24C_write_byte(0,card_Num>>8);
                _delay_ms(10);
                AT24C_write_byte(1,card_Num&0xFF);
                _delay_ms(10);

                // Buzzer
                beep_buzzer();
                PORTC &= ~LED_C1;
            }
        }

        //==============================
        // 삭제 버튼
        if( (PIND&BTN_D4)!=BTN_D4 ){
            if(!(btnPressed&0b001))
                btnPressed|=0b001;
        }
        else{
            if(btnPressed&0b001){
                btnPressed&=0b110;
                _delay_ms(BtnDTime);
                PORTC |= LED_C2;

                uint8_t exitState = 0;
                // 관리자 카드 대기
                while(0!=checkRFID(1,card_Num)){
                    if((PIND&BTN_D4)!=BTN_D4){
                        btnPressed|=0b001;

                        // Buzzer
                        beep_buzzer();
                        PORTC &= ~LED_C2;

                        exitState = 1;
                    }
                    else{
                        if(btnPressed&0b001){
                            btnPressed&=0b110;
                            _delay_ms(BtnDTime);
                            break;
                        }
                    }
                }
                if(exitState) {
                    continue;
                }

                // 카드 갯수 초기화
                card_Num = 0;
                AT24C_write_byte(0,card_Num>>8);
                _delay_ms(10);
                AT24C_write_byte(1,card_Num&0xFF);
                _delay_ms(10);

                // Buzzer
                beep_buzzer();
                PORTC &= ~LED_C2;
            }
        }

        //==============================
        // 도어 스위치가 눌렸다면
        if( (PIND&D_BTN_D6)!=D_BTN_D6 ) {
            // 만약 문이 닫인 상황에서 카드가 인증되면
            if (!checkRFID(0,card_Num)) {
                // 문이 닫혀 있었다면 문 열기
                if (doorState == 0b00) {
                    doorState = 0b11;
                    doorOpen();
                }
            }

            // 만약 문을 닫았다면
            if(doorState==0b10) {
                doorState = 0b00;   // 초기 상태
                doorClose();        // 문 닫기
            }
        }
            // 만약 문을 열었다면
        else {
            // 문열림 버튼 상태를 변경
            if(doorState==0b11)
                doorState=0b10;
        }
    }
    return 0;
}


void board_setup(void){
    DDRC = 0x0F;          // LED, Buzzer
    DDRD = 0x20;          // Servo

    PORTC |= BUZZ_C3;     // 점검용 부저 켜기

    // UART_INIT();     // UART
    doorState = 0b00;     // 문 동작 관련 상태 변수. memo.md 파일 참고
    btnPressed = 0b000;   // 버튼 눌림 관련 상태 변수. memo.md 파일 참고

    // 문 닫기
    doorClose();

    spi_init();         // SPI 작동
    _delay_ms(50);

    mfrc522_init();     // rfid 리더기 연결

    // RFID 작동 안하면 리셋
    byte = mfrc522_read(VersionReg);
    if(byte != 0x92) {
        wdt_reset();
    }

    byte = mfrc522_read(ComIEnReg);
    mfrc522_write(ComIEnReg,byte|0x20);
    byte = mfrc522_read(DivIEnReg);
    mfrc522_write(DivIEnReg,byte|0x80);

    // I2C 작동(EEPROM)
    TWCR = (1<<TWEN);
    TWBR = 12;          //400khz

    // EEPROM 0,1번에서 1byte 씩 가져와 2byte 값으로
    card_Num = AT24C_read_byte(0)<<8|AT24C_read_byte(1);

    PORTC &= ~BUZZ_C3;  // 점검용 부저 끄기
    return;
}

void beep_buzzer(void){
    PORTC |= BUZZ_C3;
    _delay_ms(BuzzerTime);
    PORTC &= ~BUZZ_C3;
    return;
}


/*
 *  카드를 확인하는 함수
 *  boolAdmin) 1: Admin only, 0: All
 *  return) 1: Error, 0: Pass
 */
uint8_t checkRFID(uint8_t boolAdmin,uint16_t card_Num){
    byte = mfrc522_request(PICC_REQALL,str);

    if(byte == CARD_FOUND){
        byte = mfrc522_get_card_serial(str);
        if(byte == CARD_FOUND){
            // 관리자 카드 검사
            for(uint8_t n=0; n<cardAdmin_Num;n++){
                if( (str[0]==cardAdmin_UID[n][0]) && (str[1]==cardAdmin_UID[n][1]) &&
                    (str[2]==cardAdmin_UID[n][2]) && (str[3]==cardAdmin_UID[n][3]) ){
                    return 0;
                }
            }

            // 일반 사용자 카드도 검사
            if( !boolAdmin ){
                for(uint16_t n=0; n<card_Num;n++){
                    if( (str[0]== AT24C_read_byte(4*(n+1))) && (str[1]== AT24C_read_byte(4*(n+1)+1)) &&
                        (str[2]==AT24C_read_byte(4*(n+1)+2)) && (str[3]==AT24C_read_byte(4*(n+1)+3)) ){
                        return 0;
                    }
                }
            }
        }
    }
    return 1;
}

// RFID UID 값을 읽어오는 함수 (return 1: error)
// 포인터 주소 필요함.
uint8_t readRFID(uint16_t *tempUID0, uint16_t *tempUID1, uint16_t *tempUID2, uint16_t *tempUID3) {
    byte = mfrc522_request(PICC_REQALL, str);
    if (byte == CARD_FOUND) {

        byte = mfrc522_get_card_serial(str);
        if (byte == CARD_FOUND) {
            // 포인터에 카드 값을 입력
            *tempUID0 = str[0];
            *tempUID1 = str[1];
            *tempUID2 = str[2];
            *tempUID3 = str[3];

            return 0;
        }
    }
    return 1;
}

void doorOpen() {
    for (int i = 0; i < Servo_PulseNum; i++) {
        PORTD |= ServoPin;
        _delay_ms(2.5);
        PORTD &= ~ServoPin;
        _delay_ms(17.5);
    }

    // Buzzer
    beep_buzzer();
    return;
}

void doorClose(void){
    // 문 닫기
    for(int i=0;i<Servo_PulseNum;i++){
        PORTD |= ServoPin;
        _delay_ms(1.5);
        PORTD &= ~ServoPin;
        _delay_ms(18.5);
    }

    // Buzzer
    beep_buzzer();
    return;
}

