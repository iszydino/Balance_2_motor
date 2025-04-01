#include "Setup_Esc.h"

void ESC::attach(int rightPin, int leftPin)
{
    // escRight.attach(rightPin);
    // escLeft.attach(leftPin);
    ledcSetup(0, 50, 16);  // Channel 0, 50Hz, 16-bit resolution
    ledcSetup(1, 50, 16);
    ledcAttachPin(rightPin, 0);
    ledcAttachPin(leftPin, 1);
}

void ESC::run(int rightSpeed, int leftSpeed)
{
    int rightPwmValue = constrain(rightSpeed, 3277, 6553);
    int leftPwmValue  = constrain(leftSpeed, 3277, 6553);
    ledcWrite(0, rightPwmValue);
    ledcWrite(1, leftPwmValue);
    // escRight.writeMicroseconds(rightSpeed);
    // escLeft.writeMicroseconds(leftSpeed);
    // Serial.print(" | OutputR: ");
    // Serial.print(rightSpeed);
    // Serial.print(" | OutputL: ");
    // Serial.println(leftSpeed);
    // Serial.println();
}

void ESC::calibrate()
{
    Serial.println("Calibrating ESC...");

    ledcWrite(0, 6553); // Max pulse width (~2000us)
    ledcWrite(1, 6553); // Max pulse width (~2000us)
    Serial.println("Max throttle signal sent");
    delay(2000);

  // Min throttle
    ledcWrite(0, 3277);  // Min pulse width (~1000us)
    ledcWrite(1, 3277);  // Min pulse width (~1000us)
    delay(2000); // Đợi ESC nhận tín hiệu hiệu chỉnh

    Serial.println("Calibration Done!");
}
