#pragma once

#include <Arduino.h>

class Device {

	public:

		Device();

		void begin();
		void check();

		static void message_handler(char *, char *);

	private:



};

extern Device device;