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

motor leftFWheelMotor(PORT1); //These two are for turning (axis3 + axis 4)
motor rightFWheelMotor(PORT2); //(axis3 - axis4)

motor rearSlideWheels(PORT3);  // movement (axis 3)

motor leftArmMotor(PORT4); //These two are for arms up/down (axis 2)
motor rightArmMotor(PORT5);

motor leftBeltMotor(PORT6); //These two are feed belt (R1 *Top Bumper*)
motor rightBeltMotor(PORT7);

motor dolleyMotor(PORT8);

//Function for scaling down sensitivity of motors to stick at low throw
int scale(int axisVal) {
  double scaledVal;
  scaledVal = ((double)axisVal * abs(axisVal)) / 100.0;
  int newVal = (int)scaledVal;
  return newVal;
}


controller fakeXbox = controller();
int dolleyState = 0;

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
     
     //if R1 (bumper) is pressed, set velocity for 80%
     //if R2 (bumper) is pressed, set velocity for -80%
     int beltMotorVelocity = 0;
     if(fakeXbox.ButtonR1.pressing()){
       beltMotorVelocity = 80;
     }else if(fakeXbox.ButtonR2.pressing()){
       beltMotorVelocity = -80;
     }
     //if L1 (bumper) is pressed, set velocity for on
     //if L2 (bumper) is pressed, set velocity for on
     if(fakeXbox.ButtonL1.pressing()){
       beltMotorVelocity = 0;
     }else if(fakeXbox.ButtonL2.pressing()){
       beltMotorVelocity = 0;
     }
//****************************************************************
     //set velocity
    
     leftFWheelMotor.setVelocity(leftVelocity, velocityUnits::pct);
     rightFWheelMotor.setVelocity(rightVelocity, velocityUnits::pct);
     rearSlideWheels.setVelocity(rearWheelVelocity, velocityUnits::pct);
     //arms
     leftArmMotor.setVelocity(leftArmVelocity, velocityUnits::pct);
     rightArmMotor.setVelocity(rightArmVelocity, velocityUnits::pct);
     //belt
     leftBeltMotor.setVelocity(beltMotorVelocity, velocityUnits::pct);
     rightBeltMotor.setVelocity(beltMotorVelocity, velocityUnits::pct);

//*****************************************************************
     //spin all
     //wheels
     leftFWheelMotor.spin(directionType::fwd);
     rightFWheelMotor.spin(directionType::rev);
     rearSlideWheels.spin(directionType::fwd);
     //arms
     leftArmMotor.spin(directionType::fwd);
     rightArmMotor.spin(directionType::rev);
     //belt (positive velocity aka R1 should feed in)(negative velocity pushes out.)
     leftBeltMotor.spin(directionType::fwd);
     rightBeltMotor.spin(directionType::rev);

//*****************************************************
  //Dolley Event

  //State 0 -> Dolley is not upright.
  if(fakeXbox.ButtonX.pressing()){
    //dolleyMotor Speed
    dolleyMotor.setVelocity(50,velocityUnits::rpm);

    if(dolleyState == 0) { // moving from down -> upright

    dolleyMotor.spin(directionType::fwd);
    vex::task::sleep(3000);
    dolleyState = 1;
    }
    else { //moving from upright -> down

    dolleyMotor.spin(directionType::rev);
    vex::task::sleep(3000);
    dolleyState = 0;
    }
  }




     //sleep
     vex::task::sleep(10);
     
     if(fakeXbox.ButtonA.pressing()){
       return 1;
     }
              
  }
  
}