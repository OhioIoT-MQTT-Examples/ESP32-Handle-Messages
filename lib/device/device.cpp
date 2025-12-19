#include "device.h"
#include "mqtt.h"


Device::Device() {}

Device device;



void Device::begin() {
	
	static const char * subscription_list[] = {
		"temperature",
		"humidity",
		"luminosity"
	};

	mqtt.set_subscriptions(subscription_list, 3);
	mqtt.set_callback(message_handler);
}

void Device::check() {

}


void Device::message_handler(char * topic, char * message) {
	Serial.print("\treceived: ");
	Serial.print(topic);
	Serial.print(" / ");
	Serial.println(message);
}