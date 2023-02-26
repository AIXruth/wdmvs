#define SENSORS 3

struct sensor_struct {
    unsigned int PIN;
    std::string PUBLISHTOPIC;
    std::string SNAME;
    int value;
};

