<p> 수정 중</p>
<br/>

# EPIC Door Lock Project

## 1. 프로젝트 소개
## 2. 다운로드
## 3. 컴파일

Makefile을 이용하여 컴파일하는 경우, Makefile과 같은 위치에 `out` 폴더를 생성해야 합니다.

| 필요한 패키지 | 설명               |
| :-----------: | :----------------- |
|    avr-gcc    | 컴파일러           |
|   avr-libc    | 라이브러리         |
|   avr-size    | 메모리 사용량 확인 |
|    avrdude    | 업로더             |


### 1. in Linux

1. set up

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

<br/>
