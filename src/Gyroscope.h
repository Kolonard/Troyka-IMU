#ifndef __GYROSCOPE_H__
#define __GYROSCOPE_H__

#include "BaseIMU.h"

// I²C-address device
constexpr uint8_t L3G4200D_SLAVE_ADDRESS = 0x68;
constexpr uint8_t L3G4200D_SLAVE_ADDRESS_ALT = 0x69;

// Registers address
constexpr uint8_t L3G4200D_CTRL_REG4_FS0 = 0x10;
constexpr uint8_t L3G4200D_CTRL_REG4_FS1 = 0x20;

// Registers value bits
constexpr uint8_t L3G4200D_CTRL_REG1_X_EN = 0x01;
constexpr uint8_t L3G4200D_CTRL_REG1_Y_EN = 0x02;
constexpr uint8_t L3G4200D_CTRL_REG1_Z_EN = 0x04;
constexpr uint8_t L3G4200D_CTRL_REG1_PD = 0x08;

// Constans
constexpr float SENS_250DPS = 0.00875;
constexpr float SENS_500DPS = 0.0175;
constexpr float SENS_2000DPS = 0.07;

enum class GyroscopeRange {
    RANGE_250DPS = 1,
    RANGE_500DPS = 2,
    RANGE_2000DPS = 3
};

class Gyroscope : public BaseIMU {
public:
    Gyroscope(uint8_t slaveAddress = L3G4200D_SLAVE_ADDRESS);
    void begin(TwoWire& wire = Wire);
    void sleep(bool state);
    void setRange(GyroscopeRange range);
    float readRotationDegX();
    float readRotationDegY();
    float readRotationDegZ();
    float readRotationRadX();
    float readRotationRadY();
    float readRotationRadZ();
    void readRotationDegXYZ(float& gx, float& gy, float& gz);
    void readRotationRadXYZ(float& gx, float& gy, float& gz);

private:
    float _scalingFactor;
};

#endif // __GYROSCOPE_H__
