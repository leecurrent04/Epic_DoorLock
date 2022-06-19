#avrdude -p ?

MCU=atmega168p
PORT=/dev/ttyUSB0
OBJ_FILES=./lib/*
BAUDRATE=115200
PROGRAMMER=arduino

all:
	avr-gcc -Wall -mmcu=${MCU} -Os main.c ${OBJ_FILES} -o ./out/output.o
	avr-objcopy -j .text -j .data -O ihex ./out/output.o ./out/main.hex

flash:
	avrdude -v -p ${MCU} -c ${PROGRAMMER} -P ${PORT} -b ${BAUDRATE} -U flash:w:./out/main.hex:i
	

clean:
	rm -f ./out/*.o ./out/*.hex
