CC = g++
CFLAGS = -Wall -g -fsanitize=undefined
LIBS = -l mosquittopp -lwiringPi
all: mqttclient
mqttclient: main.cpp mqtt.cpp mqtt.h private.h config.h
	$(CC) $(CFLAGS) -o mqttclient  main.cpp mqtt.cpp $(LIBS)
debugbuild: mqttclient
	$(CC) $(CFLAGS) -o mqttclient  main.cpp mqtt.cpp $(LIBS) -DDEBUG
clean:
	rm mqttclient
