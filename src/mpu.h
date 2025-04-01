#ifndef MPU_H_
#define MPU_H_

#include"main.h"
void mpuSetup();
float readMpu();
float kalmanFilter(float newAngle, float newRate);
float output_roll();

#endif