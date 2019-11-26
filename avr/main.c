#include "COM.h"

int main() {
	COM_init();

	while (1) {
		COM_sendString("Hello, World");
		COM_sendString("This is a test.");
	}
}
