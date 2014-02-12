#include <math.h>
#include <PID_v1.h>

//Turning sensitivity for curveDrive
double sensitivity = 0.5;

//TODO: Use PIDAutoTune to get tuning parameters.

//Variables for PID Controller
double setpoint, flameSensorInput, rotationalOutput;
double kp = 1;
double ki = 0;
double kd = 0;

//Specify links and initial tuning parameters
PID rotationalAlignmentPID(&flameSensorInput, &rotationalOutput, &setpoint, kp, ki, kd, DIRECT);


/*Adds functionality for driving given a speed and a curve from -1 to 1, left to right
Speed is the magnitude from -255 to 255, full reverse to full forward
Given the speed and the curve, this function will power the motors to drive and turn simultaneously.
The algorithm tries to maintain a consistent turning radius at different speeds.*/

void curveDrive(motorSpeed, curve){
  
  //Handle out of range inputs of motorSpeed
  if (motorSpeed < -255){
    
    motorSpeed = -255;
  } else if (motorSpeed > 255) {
    
    motorSpeed = 255;
  }
  
  int leftOutput;
  int rightOutput;
  
  double valuex = log(abs(curve));
  
  double ratio = (value-sensitivity)/(value+sensitivity)
  
  //If the ratio is 0, prevent divide by zero by setting it to near zero
  if (ratio == 0){
    
    ratio = .000001;
  }
  
  //Handle turning left or right appropriately to curve's value
  if (curve < 0){
    
    leftOutput = motorSpeed/ratio;
    rightOutput = motorSpeed;
  }  else if (curve > 0){
    
    leftOutput = motorSpeed;
    rightOutput = motorSpeed/ratio;
  } else {
    
    leftOutput = motorSpeed;
    rightOutput = motorSpeed;
  }
  
  //Handle direction, driving forward or backward.
  if (motorSpeed > 0){
    
    motorLeft.run(FORWARD);
    motorRight.run(FORWARD);
  } else if (motorSpeed < 0){
    
    motorLeft.run(BACKWARD);
    motorRight.run(BACKWARD);
  } else if (motorSpeed == 0){
    
    motorLeft.run(RELEASE);
    motorRight.run(RELEASE);
  }
  
  
  motorLeft.setSpeed(leftOutput);
  motorRight.setSpeed(rightOutput);
}


void autoAlign(double flameDirection, double flameDistance){
  
//TODO: Implement one main function that runs two PID controllers to set two variables, speed and curve.
//      One controller should run with flameDirection as an input and control curve as an output.
//      The second controller should take flameDistance as an input, and control speed as an output.

  double curve = 0;
  double moveSpeed = 0;
  
  rotationController(flameDirection, &curve);
}

void rotationController(double flameDirection, double *curve){
  rotationalAlignmentPID(
}
