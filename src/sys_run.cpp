#include "sys_run.h"

ESC Controller(27, 26);
Button myButton(14);
float roll;
float speed_out;
float speed_left;
float speed_right;

bool flag = false;
void Esc_setup()
{
    myButton.init();
    while(!myButton.getState()){
    }
    Controller.attach(27, 26);
    Controller.calibrate();
}

void flagChange(){
    if(myButton.getState()){
        flag = !flag;
    }
}

void Sys_run()
{
    flagChange();
    if (!flag)  
    {
        Controller.run(0, 0);
    }
    // else
    // {
    //     roll = output_roll();
    //     Speed_out = pid_motor.Update(SET_POINT, roll);

    //     Speed_right = SPEED_RIGHT_AVG - Speed_out;
    //     if(Speed_out > 0)
    //     {
    //         Speed_left = SPEED_LEFT_AVG + Speed_out;
    //         Speed_right = SPEED_RIGHT_AVG - Speed_out;
    //     }
    //     else
    //     {
    //         Speed_left = SPEED_LEFT_AVG + Speed_out;
    //         Speed_right = SPEED_RIGHT_AVG - Speed_out;
    //     }
    //     Speed_right = constrain(Speed_right, PWM_MIN_RIGHT, PWM_MAX_RIGHT);
    //     Speed_left = constrain(Speed_left, PWM_MIN_LEFT, PWM_MAX_LEFT);
        // Controller.run(Speed_right, Speed_left);
    else{
        roll = output_roll();
        speed_out = pid_motor.Update(SET_POINT, roll);
        // Serial.print("Roll: ");
        // Serial.print(roll);
        // Serial.print(" P: ");
        // Serial.print(pid_motor.P);
        // Serial.print(" I: ");
        // Serial.print(pid_motor.I);
        // Serial.print(" D: ");
        // Serial.println(pid_motor.D);
        speed_left = 5500 + speed_out; // yeu hon 
        speed_right = 5500 - speed_out;
        Controller.run(speed_right, speed_left);
        // ledcWrite(0, speed_right);
        // ledcWrite(1, speed_left);
    }
//    }

}
