#include <SoftwareSerial.h>

#define COM_PIN 13
#define COM_BAUDRATE 1200

SoftwareSerial mySerial(COM_PIN, 3); // RX, TX

void setup() {
	Serial.begin(9600);
	while (!Serial);
	mySerial.begin(COM_BAUDRATE);
}

void loop() {
	if (mySerial.available()) {
		Serial.write(mySerial.read());
	}
}

