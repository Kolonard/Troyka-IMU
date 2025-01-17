# TroykaIMU with SoftI2C

Based on "Arduino library to interface with the [Amperka IMU 10-DOF Sensor](https://amperka.ru/product/troyka-imu-10-dof) [https://github.com/amperka/Troyka-IMU] " 

Added support for working with software implementation of I2C based on SoftI2C library. The choice between <Wire.h> and <SoftI2C.h> is made by adding “#define SOFT_I2C_MODE_” to BaseIMU.h.