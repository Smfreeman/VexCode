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

using namespace vex;
 // A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;
vex::motor leftFWheelMotor(vex::PORT1); //These two are for turning (axis 4)
vex::motor rightFWheelMotor(vex::####);

vex::motor rearSlideWheels(vex::####);  //mainly on for forward movement (axis 3)

vex::motor leftFWheelMotor(vex::####); //These two are for arms up/down (axis 2)
vex::motor rightFWheelMotor(vex::####);

vex::motor leftFWheelMotor(vex::####); //These two are feed belt (R1 *Top Bumper*)
vex::motor rightFWheelMotor(vex::####);




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

     //calculate motor velocity settings
     int leftVelocity = stickAxis3 + stickAxis4; 
     int rightVelocity = stickAxis3 - stickAxis4;


     //set velocity
     leftFWheelMotor.setVelocity(leftVelocity, vex::velocityUnits::pct);
     rightFWheelMotor.setVelocity(rightVelocity, vex::velocityUnits::pct);
     //spin
     leftFWheelMotor.spin(vex::directionType::fwd);
     rightFWheelMotor.spin(vex::directionType::rev);

     //sleep
     vex::task::sleep(20);
     
     if(fakeXbox.ButtonA.pressing()){
       return 1;
     }
              
  }
  
}