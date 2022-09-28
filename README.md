# EPIC Door Lock Project

![img](./ver3/guide/3d_model.png)

## 1. 프로젝트 소개

연초고등학교 EPIC 동아리(2021~2022) 에서 교내 학생들의 자발적인 탐구 활동을 장려하기 위해 진행한 프로젝트 입니다.

<br>


## 2. 다운로드

***수정중***

<br>


## 3. 컴파일

Makefile을 이용하여 컴파일하는 경우, Makefile과 같은 위치에 `out` 폴더를 생성해야 합니다.

| 필요한 패키지 | 설명               |
| :-----------: | :----------------- |
|    avr-gcc    | 컴파일러           |
|   avr-libc    | 라이브러리         |
|   avr-size    | 메모리 사용량 확인 |
|    avrdude    | 업로더             |

<br>

### 1. in Linux

1. set up(Debian)
<br>
패키지 설치는 Debian 기준으로 설명하고 있습니다. 자신의 환경에 맞추어 사용하시길 바랍니다.


```console
apt update && apt upgrade
apt install avr-gcc avr-libc avr-size avrdude
```

2. download source code
```console
git clone https://github.com/leecurrent04/Epic_DoorLock
cd ./Epic_DoorLock/ver3/code/avr/
mkdir out
make all
```
3. set admin card

4. set port
5. upload
```console
make flash
```

<br>


## 4. 참고 라이브러리

https://github.com/asif-mahmud/MIFARE-RFID-with-AVR


