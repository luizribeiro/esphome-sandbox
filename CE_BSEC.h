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
    iaqSensor.begin(BME680_I2C_ADDR_SECONDARY, Wire);
    bsec_virtual_sensor_t sensorList[10] = {
      BSEC_OUTPUT_RAW_TEMPERATURE,
      BSEC_OUTPUT_RAW_PRESSURE,
      BSEC_OUTPUT_RAW_HUMIDITY,
      BSEC_OUTPUT_RAW_GAS,
      BSEC_OUTPUT_IAQ,
      BSEC_OUTPUT_STATIC_IAQ,
      BSEC_OUTPUT_CO2_EQUIVALENT,
      BSEC_OUTPUT_BREATH_VOC_EQUIVALENT,
      BSEC_OUTPUT_SENSOR_HEAT_COMPENSATED_TEMPERATURE,
      BSEC_OUTPUT_SENSOR_HEAT_COMPENSATED_HUMIDITY,
    };
    iaqSensor.updateSubscription(sensorList, 10, BSEC_SAMPLE_RATE_LP);
  }

  void update() override {
    iaqSensor.run();

    float Temp = iaqSensor.temperature;
    TSensor->publish_state(Temp);
    
    float Press = iaqSensor.pressure;
    PSensor->publish_state(Press);
    
    float Hum = iaqSensor.humidity;
    HSensor->publish_state(Hum);
    
    float Qual = iaqSensor.staticIaq;
    AQSensor->publish_state(Qual);
    
    float Resis = iaqSensor.gasResistance;
    GRSensor->publish_state(Resis);
  }
};
