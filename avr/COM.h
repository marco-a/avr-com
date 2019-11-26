#ifndef COM_H
	#define COM_H

	#define COM_DATA_PORT A
	#define COM_DATA_PIN 0

	#define COM_SYNC_PORT A
	#define COM_SYNC_PIN 1

	#define COM_SYNC_LENGTH 100   /* in microseconds */
	#define COM_DATA_LENGTH 1000  /* in microseconds */

	void COM_init();
	void COM_sendString(const char *str);
#endif
