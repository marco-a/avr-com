#!/bin/sh -eufx

avr-gcc -g -Os -DF_CPU=1000000 -mmcu=attiny84a -c main.c
avr-gcc -g -Os -DF_CPU=1000000 -mmcu=attiny84a -c COM.c
avr-gcc -g -Os -DF_CPU=1000000 -mmcu=attiny84a -c IO.c

avr-gcc -g -mmcu=attiny84a -o main.elf main.o IO.o COM.o
avr-objcopy -j .text -j .data -O ihex main.elf main.hex

rm main.elf main.o COM.o IO.o
