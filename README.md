# wdmvs
Washing machines and dryer vibration sensor

This project uses an old Raspberry Pi 1a with different vibration sensors to detect activities of my washing and dryer machine.
The first section of main.cpp defines the PINs, where the sensors have been directly connected to without any additional resistance.
In the main loop I detect the activities in a ~60s loop and send the result via MQTT to my home automatisation, here iobroker. A one minute delay kicks in before the next loop starts. If there was no activity, this delay time increases up to 10 minutes.

As sensors I use a "Piezo blatt, percussion, vibration, schock sensor" and a "sw-420 sensor module".

To build the binary you have to install libmosquitto-dev and wiringPi from https://github.com/WiringPi/WiringPi.git
then just type "make" and execute ./mqttclient
