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
 // A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;
vex::motor leftFWheelMotor(vex::PORT1); //These two are for turning (axis3 + axis 4)
vex::motor rightFWheelMotor(vex::####); //(axis3 - axis4)

vex::motor rearSlideWheels(vex::####);  //mainly on for forward movement (axis 3)

vex::motor leftArmMotor(vex::####); //These two are for arms up/down (axis 2)
vex::motor rightArmMotor(vex::####);

vex::motor leftBeltMotor(vex::####); //These two are feed belt (R1 *Top Bumper*)
vex::motor rightBeltMotor(vex::####);

vex::motor dolleyMotor(vex::####);


int scale(int axisVal){

  double scaledVal;
  scaledVal = ((double)axisVal * abs(axisVal)) / 100.0;
  int newVal = (int)scaledVal;
  return newVal;
}


//vex::motor leftArmMotor(vex::####);
//vex::motor rightArmMotor(vex::####);

vex::controller fakeXbox = vex::controller();

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  while(1) {
     //grab controller axis values
     int stickAxis3 = fakeXbox.Axis3.value();
     int stickAxis4 = fakeXbox.Axis4.value();
     int stickAxis2 = fakeXbox.Axis2.value();
     int stickAxis1 = fakeXbox.Axis1.value();

     //scale axis values
     int scaledAxis3 = scale(stickAxis3);
     int scaledAxis4 = scale(stickAxis4);
     int scaledAxis2 = scale(stickAxis2);
     int scaledAxis1 = scale(stickAxis1);

     //calculate motor velocity settings
     int leftVelocity = (int)((scaledAxis3 + scaledAxis4)*.75); //scaled (.75) for gear ratio.
     int rightVelocity = (int)((scaledAxis3 - scaledAxis4)*.75); //scaled (.75) for gear ratio.
     int rearWheelVelocity = scaledAxis3;
            //arm motors
     int leftArmVelocity = (int)(scaledAxis2 * .50); //scaled (.5) *full power might be too much*
     int rightArmVelocity = (int)(scaledAxis2 * .50); //scaled (.5) *full power might be too much*


     //set velocity
     leftFWheelMotor.setVelocity(leftVelocity, vex::velocityUnits::pct);
     rightFWheelMotor.setVelocity(rightVelocity, vex::velocityUnits::pct);
     rearSlideWheels.setVelocity(rearWheelVelocity, vex::velocityUnits::pct);
     //spin
     leftFWheelMotor.spin(vex::directionType::fwd);
     rightFWheelMotor.spin(vex::directionType::rev);
     rearSlideWheels.spin(vex::directionType::fwd);

     //sleep
     vex::task::sleep(20);
     
     if(fakeXbox.ButtonA.pressing()){
       return 1;
     }
              
  }
  
}