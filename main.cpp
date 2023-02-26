#include <unistd.h>
#include <wiringPi.h>

#include "mqtt.h"
#include "config.h"

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
  sensor[0].PUBLISHTOPIC = "WDMVS/BlueSensor1";
  sensor[0].SNAME = "Blue4 Sensor";
  sensor[0].value = 0;

  sensor[1].PIN = 5;
  sensor[1].PUBLISHTOPIC = "WDMVS/BlueSensor2";
  sensor[1].SNAME = "Blue5 Sensor";
  sensor[1].value = 0;

  sensor[2].PIN = 14;
  sensor[2].PUBLISHTOPIC = "WDMVS/RoundSensor1";
  sensor[2].SNAME = "Round sensor";
  sensor[2].value = 0;

  wiringPiSetup();  // Setup the library
  iot_client = new mqtt_client(client_id, topic, host, port);
  iot_client->send_message("ON");
  // iot_client->subscribe(NULL, SUBSCRIBE_TOPIC);
  
  int delay=1;
  while (1) {
    int r = 0;
    while (r <= 600) {  // delay loop
      for (int i = 0; i < SENSORS; i++) {
        if ( digitalRead(sensor[i].PIN) == 1 ) 
          sensor[i].value++;
        usleep(100000);  // 0.1s
        r++;
      }
    }
    int sum=0;
    int len[SENSORS];
    string s[SENSORS];
    for (int a = 0; a < SENSORS; a++) {
      s[a] = to_string(sensor[a].value);
      len[a] = s[a].length();
      sum += sensor[a].value;
      iot_client->publish(NULL, sensor[a].PUBLISHTOPIC.c_str(), len[a], s[a].c_str());
      #ifdef DEBUG
      cout << "s[" << a << "]=" << s[a] << endl;
      #endif
    }    
    for (int ii = 0; ii < SENSORS; ii++) sensor[ii].value = 0;  // set back to 0
    
    if (sum == 0) {  // routine to increase delay, if no activities. Longest delay = 10x
      if ( delay < 10 ) delay++;
    } else {
      delay = 1;
      sum = 0;
    }
    sleep(60*delay);  // next sensor request after 1 minute * delay 
  }
}
