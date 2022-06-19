#avrdude -p ?
MCU=atmega168p
PORT=/dev/ttyUSB0
OBJ_FILES="./lib/UART.c"

all:
	avr-gcc -Wall -mmcu=${MCU} -Os main.c ${OBJ_FILES} -o ./out/output.o

	avr-objcopy -j .text -j .data -O ihex ./out/output.o ./out/main.hex

flash:
	avrdude -v -p ${MCU} -c arduino -U flash:w:./out/main.hex:i -P ${PORT}

clean:
	rm -f ./out/*.o ./out/*.hex
