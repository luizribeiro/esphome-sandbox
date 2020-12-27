#include "esphome.h"
#include "bsec.h"

const uint8_t bsec_config_iaq[] = {
    #include "config/generic_33v_3s_28d/bsec_iaq.txt"
};

class BSECSensor : public PollingComponent, public Sensor {
 private:
  Bsec bsec;

 public:
  Sensor *temperatureSensor = new Sensor();
  Sensor *pressureSensor = new Sensor();
  Sensor *humiditySensor = new Sensor();
  Sensor *airQualitySensor = new Sensor();
  Sensor *gasResistanceSensor = new Sensor();

  BSECSensor() : PollingComponent(300000) { }

  void setup() override {
    bsec.begin(BME680_I2C_ADDR_SECONDARY, Wire);
    bsec.setConfig(bsec_config_iaq);
    bsec_virtual_sensor_t sensorList[] = {
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
    bsec.updateSubscription(
      sensorList,
      sizeof(sensorList) / sizeof(sensorList[0]),
      BSEC_SAMPLE_RATE_LP
    );
  }

  void update() override {
    bsec.run();

    if (bsec.status != BSEC_OK) {
      if (bsec.status < BSEC_OK) {
        ESP_LOGE("bsec", "BSEC error code: %d", bsec.status);
        status_set_error();
        return;
      } else {
        ESP_LOGW("bsec", "BSEC warning code: %d", bsec.status);
        status_set_warning();
      }
    }

    if (bsec.bme680Status < BME680_OK) {
      ESP_LOGE("bsec", "BSEC error code: %d", bsec.bme680Status);
      status_set_error();
      return;
    } else {
      ESP_LOGW("bsec", "BSEC warning code: %d", bsec.bme680Status);
      status_set_warning();
    }

    temperatureSensor->publish_state(bsec.temperature);
    pressureSensor->publish_state(bsec.pressure);
    humiditySensor->publish_state(bsec.humidity);
    airQualitySensor->publish_state(bsec.staticIaq);
    gasResistanceSensor->publish_state(bsec.gasResistance);
  }
};
