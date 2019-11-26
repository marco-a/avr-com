#define F_CPU 1000000

#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

/* Configuration */
/* Make sure this matches the definitions in */
/* arduino/main.cpp */
#define SYNC_PULSE 100
#define DATA_TIME 1000

/* Functions to set data and sync pins */
/* In this example: */
/* PA0 : SYNC */
/* PA1 : DATA */
void trans_init() {
	DDRA |= _BV(PA0) | _BV(PA1);
}

void trans_set_data(bool value) {
	if (value) {
		PORTA |= _BV(PA1);
	} else {
		PORTA &= ~_BV(PA1);
	}
}

void trans_set_sync(bool value) {
	if (value) {
		PORTA |= _BV(PA0);
	} else {
		PORTA &= ~_BV(PA0);
	}
}

#define trans_delay _delay_us

void _trans_pulse_sync() {
	trans_set_sync(1);
	trans_delay(SYNC_PULSE);
	trans_set_sync(0);
}

void _trans_send_byte(uint8_t byte) {
	for (uint8_t i = 0; i < 8; ++i) {
		uint8_t pos = 7 - i;
		uint8_t value = (byte & (1 << pos)) ? 1 : 0;
		trans_set_data(value);
		trans_delay(DATA_TIME);
	}
}

void trans_send_byte(uint8_t byte) {
	_trans_pulse_sync();
	_trans_send_byte(byte);
	_trans_send_byte(byte);
	trans_delay(DATA_TIME * 2);
}

void send_string(const char *str) {
	/* start of string marker */
	trans_send_byte(0xFF);

	for (int i = 0; i < strlen(str); ++i) {
		trans_send_byte(str[i]);
	}

	/* end of string marker */
	trans_send_byte(0x00);
}

int main() {
	trans_init();

	send_string("Initialized");

	while (true) {
		char buffer[100];

		sprintf(buffer, "Test %f", 1.0f);
		send_string(buffer);
	}
}
