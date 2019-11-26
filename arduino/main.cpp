// Configuration
#define COM_DATA_PIN 6
#define COM_SYNC_PIN 5

#define COM_SYNC_LENGTH 100   /* in microseconds */
#define COM_DATA_LENGTH 1000  /* in microseconds */

#define BAUDRATE 460800

void setup() {
	Serial.begin(BAUDRATE);
	pinMode(COM_DATA_PIN, INPUT);
	pinMode(COM_SYNC_PIN, INPUT);
}

// used for edge detection
bool previousSync = false;

void loop() {
	bool sync = digitalRead(COM_SYNC_PIN);

	// positive edge means transmission start
	if (sync && !previousSync) {
		// wait for sync pulse
		// to go low + half of data transmission time
		delayMicroseconds((COM_SYNC_LENGTH) + (COM_DATA_LENGTH / 2));

		for (uint8_t i = 0; i < 16; ++i) {
			bool value = digitalRead(COM_DATA_PIN);

			Serial.print(value ? 1 : 0);

			delayMicroseconds(COM_DATA_LENGTH);
		}

		Serial.println("");
	}

	previousSync = sync;
}
