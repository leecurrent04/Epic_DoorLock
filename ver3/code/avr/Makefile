MCU=atmega168p
PORT=/dev/ttyUSB0		# SET YOUR PORT
OBJ_FILES=./lib/*
BaudRate=115200
PROGRAMMER=arduino

all:
	@echo "" && date

	@# Compile
	avr-gcc -Wall -mmcu=${MCU} -Os main.c ${OBJ_FILES} -o ./out/output.o
	avr-objcopy -j .text -j .data -O ihex ./out/output.o ./out/main.hex

	@echo "\n========================================\n"

	@# 메모리 사용량 표시
	@avr-size -C --mcu=${MCU} ./out/output.o

flash:
	@echo "" && date

	avrdude -v -p ${MCU} -c ${PROGRAMMER} -P ${PORT} -b ${BaudRate} -U flash:w:./out/main.hex:i


clean:
	rm -f ./out/*.o ./out/*.hex
