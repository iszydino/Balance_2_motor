#ifndef SYS_RUN_H
#define SYS_RUN_H

#include "main.h"
#include "pid.h"
#include "mpu.h"
#include "Setup_Esc.h"
#include "Button.h"

#define MAX_OUTPUT          1700// 1700
#define AVG_SPEED           1400
#define PWM_MIN             1000
// #define PWM_MIN_RIGHT 1300
// #define PWM_MAX_RIGHT 1690

// #define PWM_MIN_LEFT 1240
// #define PWM_MAX_LEFT 1347

// #define SPEED_LEFT_AVG 1299
// #define SPEED_RIGHT_AVG 1577

#define SET_POINT          0

#define KP                  0// Tăng độ nhạy P
#define KI                  0                     
#define KD                  0// Giảm dao động

extern PID pid_motor;
extern float roll;
extern ESC Controller;
// extern float Speed_left;
// extern float Speed_right;

void Esc_setup();
void flagChange();
void Esc_run();

#endif
