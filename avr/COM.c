#include "COM.h"
#include <util/delay.h> /* _delay_us */
#include <stdint.h> /* uint8_t */
#include <avr/io.h> /* DDR, PORT */
#include <string.h> /* strlen */
#include <stdbool.h> /* bool */

#define _COM_DELAY _delay_us

#define __COM_CONCAT(_1, _2) _1 ## _2
#define _COM_CONCAT(_1, _2) __COM_CONCAT(_1, _2)

#define _COM_DATA_DDR _COM_CONCAT(DDR, COM_DATA_PORT)
#define _COM_SYNC_DDR _COM_CONCAT(DDR, COM_SYNC_PORT)

#define _COM_DATA_PORT _COM_CONCAT(PORT, COM_DATA_PORT)
#define _COM_SYNC_PORT _COM_CONCAT(PORT, COM_SYNC_PORT)

#define _COM_DATA_PIN _COM_CONCAT(_COM_CONCAT(P, COM_DATA_PORT), COM_DATA_PIN)
#define _COM_SYNC_PIN _COM_CONCAT(_COM_CONCAT(P, COM_SYNC_PORT), COM_SYNC_PIN)

static void _COM_setDataPin(bool value) {
	if (value) {
		_COM_DATA_PORT |= _BV(_COM_DATA_PIN);
	} else {
		_COM_DATA_PORT &= ~_BV(_COM_DATA_PIN);
	}
}

static void _COM_setSyncPin(bool value) {
	if (value) {
		_COM_SYNC_PORT |= _BV(_COM_SYNC_PIN);
	} else {
		_COM_SYNC_PORT &= ~_BV(_COM_SYNC_PIN);
	}
}

void COM_init() {
	_COM_DATA_DDR |= _BV(_COM_DATA_PIN);
	_COM_SYNC_DDR |= _BV(_COM_SYNC_PIN);

	_COM_setDataPin(false);
	_COM_setSyncPin(false);
}

static void _COM_pulseSyncPin() {
	_COM_setSyncPin(true);
	_COM_DELAY(COM_SYNC_LENGTH);
	_COM_setSyncPin(false);
}

static void _COM_transmitByte(uint8_t byte) {
	for (uint8_t i = 0; i < 8; ++i) {
		uint8_t pos = 7 - i;
		bool value = (byte & (1 << pos));

		_COM_setDataPin(value);
		_COM_DELAY(COM_DATA_LENGTH);
	}
}

static void _COM_sendByte(uint8_t byte) {
	_COM_pulseSyncPin();
	_COM_transmitByte(byte);
	_COM_transmitByte(byte);
	_COM_DELAY(COM_DATA_LENGTH * 2);
}

void COM_sendString(const char *str) {
	/* start of string marker */
	_COM_sendByte(0xFF);

	for (int i = 0; i < strlen(str); ++i) {
		_COM_sendByte(str[i]);
	}

	/* end of string marker */
	_COM_sendByte(0x00);
}
