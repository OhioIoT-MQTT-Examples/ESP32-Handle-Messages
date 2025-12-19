#include "mqtt.h"

void Mqtt::publish(const char * topic, const char * payload) {
	_publish(topic, payload);
}

void Mqtt::publish(const char * topic, float number) {
	char payload[32];
	dtostrf(number, 0, 2, payload);
	_publish(topic, payload);
}

void Mqtt::publish(const char * topic, int number) {
	char payload[32];
	itoa(number, payload, 10);
	_publish(topic, payload);
}

void Mqtt::publish(const char * topic) {
	_publish(topic, "");
}

void Mqtt::_publish(const char * topic, const char * payload) {
	if (is_connected) {
		_mqtt_client.publish(topic, payload);
		if (_echo) {
			Serial.print("\tsending --- topic: ");
			Serial.print(topic);
			Serial.print(" / payload: ");
			Serial.println(payload);
		}
	}
}