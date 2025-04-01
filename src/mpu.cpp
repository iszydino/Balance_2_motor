#include "mpu.h"
float ax, ay, az, gx;

Adafruit_MPU6050 mpu;

// Biến Kalman
float Q_angle = 0.0001;  // Quá trình nhiễu cho góc
float Q_bias = 0.0004;   // Quá trình nhiễu cho bias
float R_measure = 0.004; // Nhiễu đo lường

float angleF = 0; // Góc được lọc
float bias = 0;  // Bias của con quay
float P[2][2] = {{0, 0}, {0, 0}}; // Ma trận lỗi

float dt = 0.01;

unsigned long lastTime = 0;
void updateDeltaTime() {
    unsigned long currentTime = millis();
    dt = (currentTime - lastTime) / 1000.0;
    lastTime = currentTime;
}


void mpuSetup()
{
    if (!mpu.begin())
    {
        Serial.println("Failed to find MPU6050 chip");
        while (1)
        {
            delay(10);
        }
    }

    Wire.begin();

    mpu.setAccelerometerRange(MPU6050_RANGE_8_G);

    mpu.setGyroRange(MPU6050_RANGE_500_DEG);

    mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);

    delay(100);
}

float readMpu()
{
    sensors_event_t a, g, temp;

    mpu.getEvent(&a, &g, &temp);

    ax = a.acceleration.x;

    ay = a.acceleration.y;

    az = a.acceleration.z;

    gx = g.gyro.x;

    // float roll = atan2(ay, az); 
    float roll  = atan2(ay, sqrt(ax * ax + az * az)) * 180.0 / 3.142;
    return roll;
}

float kalmanFilter(float newAngle, float newRate) {
    angleF += dt * (newRate - bias);

    P[0][0] += dt * (dt*P[1][1] - P[0][1] - P[1][0] + Q_angle);
    P[0][1] -= dt * P[1][1];
    P[1][0] -= dt * P[1][1];
    P[1][1] += Q_bias * dt;

    float S = P[0][0] + R_measure;
    float K[2];
    K[0] = P[0][0] / S;
    K[1] = P[1][0] / S;

    float y = newAngle - angleF;
    angleF += K[0] * y;
    bias += K[1] * y;

    P[0][0] -= K[0] * P[0][0];
    P[0][1] -= K[0] * P[0][1];
    P[1][0] -= K[1] * P[0][0];
    P[1][1] -= K[1] * P[0][1];

    return angleF;
}

float output_roll(){
    float accAngle = readMpu();
    float gyroRate = gx;
    float filteredRoll = kalmanFilter(accAngle, gyroRate);
    return filteredRoll;
}