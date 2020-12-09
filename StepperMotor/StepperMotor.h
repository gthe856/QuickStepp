#include <Arduino.h>

#define ROTATE_CLOCKWISE 1
#define ROTATE_ANTICLOCKWISE 0
class StepperMotor
{
public:
    int stepper_enable;
    int m0;
    int m1;
    int m2;
    int stepper_reset;
    int stepper_sleep;
    int stepper_direction;
    int stepper_step;
    int fault;
    boolean motorDirection;
    int numberOfStepsTravelled;
    boolean step_state;
    int rpm = 120;
    int motorSteps = 200;
    
    StepperMotor(
        int stepper_enable,
        int m0,
        int m1,
        int m2,
        int stepper_reset,
        int stepper_sleep,
        int stepper_direction,
        int stepper_step,
        int fault);
        long stepper_count;
        void disableMotor();
        void enableMotor();
        void changeMotorDirection();
        void moveMotorBySteps(int direction, long steps);
        void clockMotor();
        void setMotorDirection(int direction);
        void setStepMode(int stepMode);
        void setPosition();
        void resetPosition();
        byte getStepMode();
    private:
        int clock_count;
        byte step_mode;
};