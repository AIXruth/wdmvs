
#define SUBSCRIBE_TOPIC "WDMVS/BACK2PI"
#include "private.h"

#ifndef _PRIVAT_HEADER
#define CLIENT_ID "Client_ID123_please_change"
#define BROKER_ADDRESS "yourIobrokerHost"
#define MQTT_PORT 1883
#define USER "mqttpi"
#define PASSWORD "pWd123"
#endif

#include <iostream>
#include <mosquittopp.h>
#include <cstring>
#include <cstdio>
#include <thread>
#include <future>

#define MAX_PAYLOAD 50
#define DEFAULT_KEEP_ALIVE 60

class mqtt_client : public mosqpp::mosquittopp {
private:
    const char * host;
    const char * id;
    const char * topic;
    int          port;
    int          keepalive;

    void on_disconnect(int rc);
    void on_connect(int rc);
    void on_message(const struct mosquitto_message *message);
    void on_subscribe(int mid, int qos_count, const int *granted_qos);
    void on_publish(int mid);
public:
    mqtt_client (const char *_id, const char *_topic, const char *_host, int _port);
    ~mqtt_client();
    bool send_message(const char * _message);

};


