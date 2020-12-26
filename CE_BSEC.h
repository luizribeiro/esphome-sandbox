#include "esphome.h"
#include "bsec.h"

class CE_BSEC : public PollingComponent, public Sensor {
 public:
  // constructor
  Bsec iaqSensor;
  Sensor *TSensor = new Sensor();
  Sensor *PSensor = new Sensor();
  Sensor *HSensor = new Sensor();
  Sensor *AQSensor = new Sensor();
  Sensor *GRSensor = new Sensor();

  CE_BSEC() : PollingComponent(30000) { }

  void setup() override {
    // This will be called by App.setup()
    iaqSensor.begin(0x77, Wire);
  }

  void update() override {
    float Temp = iaqSensor.temperature;
    TSensor->publish_state(Temp);
    
    float Press = iaqSensor.pressure;
    PSensor->publish_state(Press);
    
    float Hum = iaqSensor.humidity;
    HSensor->publish_state(Hum);
    
    float Qual = iaqSensor.iaq;
    AQSensor->publish_state(Qual);
    
    float Resis = iaqSensor.gasResistance;
    GRSensor->publish_state(Resis);
  }
};
