#pragma once

#include <WiFiClient.h>
#include <PubSubClient.h>

#define CLIENT_ID "test_device_2"		// needs to be unique across brokers
#define RETRY_INTERVAL 3000

using MessageHandler = void (*)(char *, char *);

class Mqtt {
	
	public:

		Mqtt();

		// connect
		void setup(const char *, int);
		void maintain();
		bool is_connected = false;

		// publish
		void publish(const char *, const char *);
		void publish(const char *, float);
		void publish(const char *, int);
		void publish(const char *);

		// subscribe
		void set_subscriptions(const char **, int);

		// handle
		void set_callback(MessageHandler);
		
		// logging
		void enable_logging();

	private:

		WiFiClient _wifi_client;
		PubSubClient _mqtt_client;

		// connect
		unsigned long _retry_timer;
		bool _is_first = true;

		// publish
		void _publish(const char *, const char *);

		// subscribe
		const char ** _subscription_list = nullptr;
		int _sub_list_length = 0;
		void _subscribe_to_all();

		// handle
		MessageHandler _stored_handler;
		static void _callback_wrapper(char *, byte *, unsigned int);

		// logging
		bool _echo = true;
		bool _initial_subscription = true; 
		void _log_state();
		
};

extern Mqtt mqtt;