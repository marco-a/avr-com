#ifndef COM_H
	#define COM_H

	#define COM_PORT      A
	#define COM_PIN       1
	#define COM_BAUDRATE  1200

	void COM_init();
	void COM_sendChar(const char);
	void COM_sendString(const char *);
#endif
