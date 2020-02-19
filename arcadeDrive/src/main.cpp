// To complete the VEXcode V5 Text project upgrade process, please follow the
// steps below.
// 
// 1. You can use the Robot Configuration window to recreate your V5 devices
//   - including any motors, sensors, 3-wire devices, and controllers.
// 
// 2. All previous code located in main.cpp has now been commented out. You
//   will need to migrate this code to the new "int main" structure created
//   below and keep in mind any new device names you may have set from the
//   Robot Configuration window. 
// 
// If you would like to go back to your original project, a complete backup
// of your original (pre-upgraded) project was created in a backup folder
// inside of this project's folder.

// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "math.h"
#include "cmath"

using namespace vex;

motor leftFWheelMotor(PORT18); //These two are for turning (axis3 + axis 4)
motor rightFWheelMotor(PORT20); //(axis3 - axis4)
motor rearSlideWheels(PORT11);  // movement (axis 3)
motor leftArmMotor(PORT19); //These two are for arms up/down (axis 2)
motor rightArmMotor(PORT1);
motor leftBeltMotor(PORT17); //These two are feed belt (R1 *Top Bumper*)
motor rightBeltMotor(PORT6);
motor dolleyMotor(PORT5);

//Function for scaling down sensitivity of motors to stick at low throw
int scale(int axisVal) {
  double scaledVal;
  scaledVal = ((double)axisVal * abs(axisVal)) / 100.0;
  int newVal = (int)scaledVal;
  return newVal;
}

controller fakeXbox = controller();

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  while(1) {
//************************************************************
    //calculate drivetrain velocity settings
    int leftVelocity = (int)((fakeXbox.Axis3.value() + fakeXbox.Axis4.value())*.75); //scaled (.75) for gear ratio to match.
    int rightVelocity = (int)((fakeXbox.Axis3.value() - fakeXbox.Axis4.value())*.75); //scaled (.75) for gear ratio to match.
    int rearWheelVelocity = fakeXbox.Axis3.value();
    //arm motors velocity - move feed arms up/down
    int leftArmVelocity = (int)(fakeXbox.Axis2.value() * 1/2); //scaled (.5) *full power might be too much*
    int rightArmVelocity = (int)(fakeXbox.Axis2.value() * 1/2); //scaled (.5) *full power might be too much*
    
    // belt motor
    if(fakeXbox.ButtonR1.pressing() || fakeXbox.ButtonR2.pressing()) {
      leftBeltMotor.setVelocity(80, velocityUnits::pct);
      rightBeltMotor.setVelocity(-80, velocityUnits::pct);
    }
    else if(fakeXbox.ButtonL1.pressing() || fakeXbox.ButtonL2.pressing()) {
      leftBeltMotor.setVelocity(-80, velocityUnits::pct);
      rightBeltMotor.setVelocity(80, velocityUnits::pct);
    }
    else if(!fakeXbox.ButtonR1.pressing() && !fakeXbox.ButtonR2.pressing() && !fakeXbox.ButtonL1.pressing() && !fakeXbox.ButtonL2.pressing()) {
      leftBeltMotor.setVelocity(0, velocityUnits::pct);
      rightBeltMotor.setVelocity(0, velocityUnits::pct);
    }
    rightBeltMotor.spin(directionType::fwd);
    leftBeltMotor.spin(directionType::fwd);

    //set velocities
    leftFWheelMotor.setVelocity(leftVelocity, velocityUnits::pct);
    rightFWheelMotor.setVelocity(rightVelocity, velocityUnits::pct);
    rearSlideWheels.setVelocity(rearWheelVelocity, velocityUnits::pct);
    //arms
    leftArmMotor.setVelocity(leftArmVelocity, velocityUnits::pct);
    rightArmMotor.setVelocity(rightArmVelocity, velocityUnits::pct);

    //spin all
    // wheels
    leftFWheelMotor.spin(directionType::fwd);
    rightFWheelMotor.spin(directionType::rev);
    rearSlideWheels.spin(directionType::fwd);
    //arms
    leftArmMotor.spin(directionType::fwd);
    rightArmMotor.spin(directionType::rev);

    //Dolley Event
    if (fakeXbox.ButtonUp.pressing())
      dolleyMotor.spin(directionType::fwd);
    if (fakeXbox.ButtonDown.pressing())
      dolleyMotor.spin(directionType::rev);

    // calibrate arms
    double angle = 0; // initialize common angle for both motors
    if (fakeXbox.Axis2.value() >= 30) angle = angle + 5;
    else if (fakeXbox.Axis2.value() >= 30) angle = angle - 5;
    
    // restrict angle value
    if (angle >= 90) angle = 90;
    if (angle <= 0) angle = 0;

    // set motor rotations
    rightArmMotor.setRotation(angle, rotationUnits::deg);
    leftArmMotor.setRotation(angle, rotationUnits::deg);
  
  } // end while loop
} // end main loop