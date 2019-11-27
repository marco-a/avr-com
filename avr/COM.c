#include "COM.h"
#include <util/delay.h> /* _delay_us */
#include <stdint.h> /* uint8_t */
#include <string.h> /* strlen */
#include <stdbool.h> /* bool */
#include <avr/io.h> /* PORTx, DDRx */

#define _CONCAT(_1, _2) _1 ## _2
#define CONCAT(_1, _2) _CONCAT(_1, _2)

#define COM_DELAY (int)((1.0f / COM_BAUDRATE) * 1000000.0f)

static inline void set_pin(bool value) {
	if (value) {
		CONCAT(PORT, COM_PORT) |= _BV(COM_PIN);
	} else {
		CONCAT(PORT, COM_PORT) &= ~_BV(COM_PIN);
	}
}

void COM_init() {
	CONCAT(DDR, COM_PORT) |= _BV(COM_PIN);
	set_pin(true);
}

void COM_sendChar(const char ch) {
	set_pin(false);
	_delay_us(COM_DELAY);

	for (uint8_t i = 0; i < 8; ++i) {
		set_pin(ch & _BV(i));
		_delay_us(COM_DELAY);
	}

	set_pin(true);
	_delay_us(COM_DELAY);
}

void COM_sendString(const char *str) {
	for (int i = 0; i < strlen(str); ++i) {
		COM_sendChar(str[i]);
	}
}
