#include <StepperMotor.h>



StepperMotor::StepperMotor(
    int _stepper_enable,
    int _m0,
    int _m1,
    int _m2,
    int _stepper_reset,
    int _stepper_sleep,
    int _stepper_direction,
    int _stepper_step,
    int _fault)
{
    pinMode(_stepper_enable, OUTPUT);
    pinMode(_m0, OUTPUT);
    pinMode(_m1, OUTPUT);
    pinMode(_m2, OUTPUT);
    pinMode(_stepper_reset, OUTPUT);
    pinMode(_stepper_sleep, OUTPUT);
    pinMode(_stepper_direction, OUTPUT);
    pinMode(_stepper_step, OUTPUT);
    pinMode(_fault, INPUT);
    stepper_enable = _stepper_enable;
    m0 = _m0;
    m1 = _m1;
    m2 = _m2;
    stepper_reset = _stepper_reset;
    stepper_sleep = _stepper_sleep;
    stepper_direction = _stepper_direction;
    stepper_step = _stepper_step;
    fault = _fault;
    motorDirection = false;
    rpm = 120;
    motorSteps = 200;
}

void StepperMotor::disableMotor()
{
    digitalWrite(stepper_enable, HIGH);
}
void StepperMotor::enableMotor(){
    digitalWrite(stepper_enable,LOW);
}
void StepperMotor::setMotorDirection(int direction)
{
    digitalWrite(stepper_direction, direction);
}
void StepperMotor::changeMotorDirection()
{
    motorDirection ? digitalWrite(stepper_direction, LOW) : digitalWrite(stepper_direction, HIGH);
}
void StepperMotor::moveMotorBySteps(int direction, long steps)
{
    long delayTime = (rpm * 1000) / (60 * motorSteps);
    digitalWrite(stepper_direction, direction == 1 ? 1 : 0);
    for (int i = 0; i < steps; i++)
    {
        digitalWrite(stepper_step, HIGH);
        delay(delayTime);
        digitalWrite(stepper_step, LOW);
        delay(delayTime);
    }
}
void StepperMotor::setStepMode(int stepMode){
    stepMode = stepMode >5 ? 7 :stepMode;
    step_mode = stepMode;
    digitalWrite(m0,stepMode &1);
    digitalWrite(m1,(stepMode>>1) &1);
    digitalWrite(m2,(stepMode>>2) &1);
}
void StepperMotor:: clockMotor()
{
    step_state = !step_state;
    digitalWrite(stepper_step, step_state ? HIGH : LOW);
    this->clock_count = this->clock_count > 2 ? 0: this->clock_count+1;
    setPosition();
}
byte StepperMotor::getStepMode(){
    return this->step_mode;
}
void StepperMotor::setPosition(){
    this->stepper_count = this->clock_count == 0? this->stepper_count + pow(2,this->step_mode):this->stepper_count;
}
void StepperMotor::resetPosition(){
    this->stepper_count = 0;
}