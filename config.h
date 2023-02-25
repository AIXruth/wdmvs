#define SENSORS 5

struct sensor_struct {
    uint PIN;
    std::string PUBLISHTOPIC;
    std::string SNAME;
    bool invert;
    uint value;
};

