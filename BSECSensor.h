#include "esphome.h"
#include "bsec.h"

class BSECSensor : public PollingComponent, public Sensor {
 private:
  Bsec bsec;

 public:
  Sensor *temperatureSensor = new Sensor();
  Sensor *pressureSensor = new Sensor();
  Sensor *humiditySensor = new Sensor();
  Sensor *airQualitySensor = new Sensor();
  Sensor *gasResistanceSensor = new Sensor();

  BSECSensor() : PollingComponent(30000) { }

  void setup() override {
    bsec.begin(BME680_I2C_ADDR_SECONDARY, Wire);
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
    bsec.updateSubscription(sensorList, 10, BSEC_SAMPLE_RATE_LP);
  }

  void update() override {
    bsec.run();

    float Temp = bsec.temperature;
    temperatureSensor->publish_state(Temp);
    
    float Press = bsec.pressure;
    pressureSensor->publish_state(Press);
    
    float Hum = bsec.humidity;
    humiditySensor->publish_state(Hum);
    
    float Qual = bsec.staticIaq;
    airQualitySensor->publish_state(Qual);
    
    float Resis = bsec.gasResistance;
    gasResistanceSensor->publish_state(Resis);
  }
};
