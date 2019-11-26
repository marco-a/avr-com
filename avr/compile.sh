#!/bin/sh

avr-gcc -g -Os  -mmcu=attiny84a -c main.c 
avr-gcc -g -mmcu=attiny84a -o main.elf main.o -Wl,-u,vfprintf -lprintf_flt
avr-objcopy -j .text -j .data -O ihex main.elf main.hex

rm main.elf main.o
