#avrdude -p ?
MCU=atmega168p
PORT=/dev/ttyUSB0
OBJ_FILES="./lib/UART.c"

all:
	avr-gcc -Wall -mmcu=${MCU} -Os main.c ${OBJ_FILES} -o ./out/output.o

	avr-objcopy -j .text -j .data -O ihex ./out/output.o ./out/main.hex

flash:
	avrdude -v -p ${MCU} -c arduino -U flash:w:./out/main.hex:i -P ${PORT}
	#avrdude -C/home/whale/.arduino15/packages/MiniCore/hardware/avr/2.1.3/avrdude.conf -v -patmega168p -carduino -P/dev/ttyUSB0 -b115200 -D -Uflash:w:/tmp/arduino_build_797755/sketch_may08a.ino.hex:i

clean:
	rm -f ./out/*.o ./out/*.hex
