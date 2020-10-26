#include "Gyroscope.h"

Gyroscope::Gyroscope(uint8_t slaveAddress)
    : BaseIMU(slaveAddress) { }

void Gyroscope::begin(TwoWire& wire) {
    _wire = &wire;
    _wire->begin();
    _ctrlReg1 |= L3G4200D_CTRL_REG1_X_EN | L3G4200D_CTRL_REG1_Y_EN
                 | L3G4200D_CTRL_REG1_Z_EN;
    _ctrlReg1 |= L3G4200D_CTRL_REG1_PD;
    _writeByte(BASE_IMU_CTRL_REG1, _ctrlReg1);
    setRange(GyroscopeRange::RANGE_2000DPS);
}

// Set range scale output data from datasheet
void Gyroscope::setRange(GyroscopeRange range) {
    switch (range) {
    case GyroscopeRange::RANGE_250DPS: {
        _ctrlReg4 = 0;
        _scalingFactor = SENS_250DPS;
        break;
    }
    case GyroscopeRange::RANGE_500DPS: {
        _ctrlReg4 = L3G4200D_CTRL_REG4_FS0;
        _scalingFactor = SENS_500DPS;
        break;
    }
    case GyroscopeRange::RANGE_2000DPS: {
        _ctrlReg4 = L3G4200D_CTRL_REG4_FS0 | L3G4200D_CTRL_REG4_FS1;
        _scalingFactor = SENS_2000DPS;
        break;
    }
    default: {
        _scalingFactor = SENS_250DPS;
    } break;
    }
    _writeByte(BASE_IMU_CTRL_REG4, _ctrlReg4);
}

void Gyroscope::sleep(bool state) {
    if (state) {
        _ctrlReg1 &= ~L3G4200D_CTRL_REG1_PD;
    } else {
        _ctrlReg1 |= L3G4200D_CTRL_REG1_PD;
    }
    _writeByte(BASE_IMU_CTRL_REG1, _ctrlReg1);
}

float Gyroscope::readRotationDegX() { return readX() * _scalingFactor; }

float Gyroscope::readRotationDegY() { return readY() * _scalingFactor; }

float Gyroscope::readRotationDegZ() { return readZ() * _scalingFactor; }

float Gyroscope::readRotationRadX() { return readRotationDegX() * DEG_TO_RAD; }

float Gyroscope::readRotationRadY() { return readRotationDegY() * DEG_TO_RAD; }

float Gyroscope::readRotationRadZ() { return readRotationDegZ() * DEG_TO_RAD; }

void Gyroscope::readRotationDegXYZ(float& gx, float& gy, float& gz) {
    int16_t x, y, z;
    readXYZ(x, y, z);
    gx = x * _scalingFactor;
    gy = y * _scalingFactor;
    gz = z * _scalingFactor;
}

void Gyroscope::readRotationRadXYZ(float& gx, float& gy, float& gz) {
    readRotationDegXYZ(gx, gy, gz);
    gx *= DEG_TO_RAD;
    gy *= DEG_TO_RAD;
    gz *= DEG_TO_RAD;
}
