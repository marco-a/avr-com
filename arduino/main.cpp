// Configuration
#define DATA_PIN 6
#define SYNC_PIN 5

#define SYNC_PULSE 100  /* in microseconds */
#define DATA_TIME 1000  /* in microseconds */

#define BAUDRATE 460800

void setup() {
	Serial.begin(460800);
	pinMode(DATA_PIN, INPUT);
	pinMode(SYNC_PIN, INPUT);
}

// used for edge detection
bool previousSync = false;
// not really neccessary..
bool values[16];

void loop() {
	bool sync = digitalRead(SYNC_PIN);

	// positive edge means transmission start
	if (sync && !previousSync) {
		// wait for sync pulse
		// to go low + half of data transmission time
		delayMicroseconds((SYNC_PULSE) + (DATA_TIME / 2));

		for (uint8_t i = 0; i < 16; ++i) {
			bool value = digitalRead(DATA_PIN);

			values[i] = value;

			delayMicroseconds(DATA_TIME);
		}

		// print to serial
		for (uint8_t i = 0; i < 16; ++i) {
			Serial.print(values[i] ? 1 : 0);
		}

		Serial.println("");
	}

	previousSync = sync;
}
