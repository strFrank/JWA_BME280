#ifndef __BMP280_BW_H__
#define __BMP280_BW_H__

#include <bme280.h>

/*!
 * @brief Type definition for results
 */
#ifdef BME280_FLOAT_ENABLE
typedef double bmeResult_t;
#define BME280_TEMPERATURE_SCALE 1.0
#define BME280_HUMIDITY_SCALE 1.0
#else
typedef uint32_t bmeResult_t;
#define BME280_TEMPERATURE_SCALE 100.0
#define BME280_HUMIDITY_SCALE 1024.0
#endif /* BME280_USE_FLOATING_POINT */

class Bme280BoschWrapper
{
  public:
    //true: uses forced mode, sensore measures values on demand
    //false: uses continuous measuring mode
    Bme280BoschWrapper(bool forcedMode);

    bool beginI2C(uint8_t dev_addr = 0x77);
    bool beginSPI(int8_t cspin);

    //this method performs measurement
    //be sure to call it before reading values
    bool measure();

    //Temperature in degrees of Celsius * 100
    bmeResult_t getTemperature();
    double getTemperatureScaling() { return BME280_TEMPERATURE_SCALE; }

    //Relative humidity in % * 1024
    bmeResult_t getHumidity();
    double getHumidityScaling() { return BME280_HUMIDITY_SCALE; }

    //Air pressure in Pa
    bmeResult_t getPressure();

  private:
    void I2CInit();
    void SPIInit();
    int8_t setSensorSettings();
  
    static int8_t I2CRead(uint8_t dev_addr, uint8_t reg_addr, uint8_t *reg_data, uint16_t cnt);
    static int8_t I2CWrite(uint8_t dev_addr, uint8_t reg_addr, uint8_t *reg_data, uint16_t cnt);
    static int8_t SPIRead(uint8_t dev_addr, uint8_t reg_addr, uint8_t *reg_data, uint16_t cnt);
    static int8_t SPIWrite(uint8_t dev_addr, uint8_t reg_addr, uint8_t *reg_data, uint16_t cnt);
    static void delaymsec(uint32_t msec);

    static int _cs;

    struct bme280_dev bme280;
    struct bme280_data comp_data;

    bool forced;
    bool error = false;
};

#endif

