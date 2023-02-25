#include "mqtt.h"
#include "config.h"
#include <wiringPi.h>
#include <unistd.h>

std::string input_reader() {
  std::string s;
  if (std::cin.good() && std::cin >> s) return s;
  return std::string();
}

int main(int argc, char *argv[]) {
  using namespace std;
  class mqtt_client *iot_client;
  // int rc;
  std::string input;

  char client_id[] = CLIENT_ID;
  char topic[] = SUBSCRIBE_TOPIC;
  char host[] = BROKER_ADDRESS;
  int port = MQTT_PORT;

  sensor_struct sensor[SENSORS];

  sensor[0].PIN = 4;
  sensor[0].PUBLISHTOPIC = "WDMVS/Sensor0";
  sensor[0].SNAME = "Blue4 Sensor";
  sensor[0].invert = false;
  sensor[0].value = 0;

  sensor[1].PIN = 5;
  sensor[1].PUBLISHTOPIC = "WDMVS/Sensor1";
  sensor[1].SNAME = "Blue5 Sensor";
  sensor[1].invert = false;
  sensor[1].value = 0;

  sensor[2].PIN = 10;
  sensor[2].PUBLISHTOPIC = "WDMVS/Sensor2";
  sensor[2].SNAME = "Double Sensor Out1";
  sensor[2].invert = true;
  sensor[2].value = 0;

  sensor[3].PIN = 11;
  sensor[3].PUBLISHTOPIC = "WDMVS/Sensor3";
  sensor[3].SNAME = "Double Sensor Out2";
  sensor[3].invert = true;
  sensor[3].value = 0;

  sensor[4].PIN = 14;
  sensor[4].PUBLISHTOPIC = "WDMVS/Sensor4";
  sensor[4].SNAME = "Round sensor";
  sensor[4].invert = false;
  sensor[4].value = 0;

  wiringPiSetup();  // Setup the library
  iot_client = new mqtt_client(client_id, topic, host, port);
  iot_client->send_message("ON");
    // iot_client->subscribe(NULL, SUBSCRIBE_TOPIC);

  while (1) {
    int r = 0;
    while (r <= 100) {  // delay loop
      for (int i=0; i < SENSORS; i++) {
        if ((digitalRead(sensor[i].PIN) ^ sensor[i].invert) == 1)
          sensor[0].value++;
        usleep(100000);  // 0.1s
        r++;
      }
      int len[SENSORS];
      // string s[SENSORS];
      for (int a=0; a < SENSORS; a++) {
        // s[a] = sensor[a].value;
        // len[a] = s[a].length;

        len[a] = sizeof(sensor[a].value);
        iot_client->publish(NULL, sensor[a].PUBLISHTOPIC.c_str(), len[a], &sensor[a].value);
        // iot_client->publish(NULL, sensor[a].PUBLISHTOPIC.c_str(), len[a], s[a].c_str());
      }
      for (int ii=0; ii < SENSORS; ii++) sensor[ii].value = 0;  // set back to 0
    }

    // int len = input.length();
    // iot_client->publish(NULL, PUBLISH_TOPIC1, len, input.c_str());
  }
}
