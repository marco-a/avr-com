#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "COM.h"

int main() {
	COM_init();

	while (true) {
		COM_sendString("Hallo, Welt\n");
	}
}
