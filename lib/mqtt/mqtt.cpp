#include "mqtt.h"

Mqtt::Mqtt() {}

Mqtt mqtt;


void Mqtt::enable_logging() {
	_echo = true;
}


void Mqtt::setup(const char * mqtt_host, int mqtt_port) {
	_mqtt_client.setClient(_wifi_client);
	_mqtt_client.setServer(mqtt_host, mqtt_port);
	// _mqtt_client.setCallback(message_handler);
}


void Mqtt::maintain() {
	if (!_mqtt_client.connected() || !is_connected) {
		bool should_reconnect = _is_first || millis() - _retry_timer > RETRY_INTERVAL;
		if (should_reconnect) {
			_is_first = false;
			if (_echo) Serial.println("\tmqtt connecting...");
			if (_mqtt_client.connect(CLIENT_ID)) {
				if (_echo) Serial.println("\tmqtt connected...");
				_is_first = true;
				is_connected = true;
				_subscribe_to_all();
			} else {
				if (_echo) _log_state();
				is_connected = false;
			}
			_retry_timer = millis();
		}
	} else {
		_mqtt_client.loop();
	}
}


void Mqtt::_log_state() {
	int conn_state = _mqtt_client.state();
	Serial.print("\tfailed to connect -- conn state: ");
	if (conn_state == -4) Serial.println("MQTT_CONNECTION_TIMEOUT");     
	if (conn_state == -3) Serial.println("MQTT_CONNECTION_LOST");        
	if (conn_state == -2) Serial.println("MQTT_CONNECT_FAILED");         
	if (conn_state == -1) Serial.println("MQTT_DISCONNECTED");           
	if (conn_state == 1)  Serial.println("MQTT_CONNECT_BAD_PROTOCOL");   
	if (conn_state == 2)  Serial.println("MQTT_CONNECT_BAD_CLIENT_ID");  
	if (conn_state == 3)  Serial.println("MQTT_CONNECT_UNAVAILABLE");    
	if (conn_state == 4)  Serial.println("MQTT_CONNECT_BAD_CREDENTIALS");
	if (conn_state == 5)  Serial.println("MQTT_CONNECT_UNAUTHORIZED");   
}
