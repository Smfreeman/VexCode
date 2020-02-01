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
vex::motor leftMotor(vex::PORT1);
vex::motor rightMotor(vex::PORT10);
vex::controller fakeXbox = vex::controller();

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  while(1) {
     //grab controller axis values
     int stickAxis2 = fakeXbox.Axis2.value();
     int stickAxis1 = fakeXbox.Axis1.value();

     //calculate motor velocity settings
     int leftVelocity = stickAxis2 + stickAxis1; 
     int rightVelocity = stickAxis2 - stickAxis1;


     //set velocity
     leftMotor.setVelocity(leftVelocity, vex::velocityUnits::pct);
     rightMotor.setVelocity(rightVelocity, vex::velocityUnits::pct);
     //spin
     leftMotor.spin(vex::directionType::fwd);
     rightMotor.spin(vex::directionType::rev);

     //sleep
     vex::task::sleep(20);
     
     if(fakeXbox.ButtonA.pressing()){
       return 1;
     }
              
  }
  
}