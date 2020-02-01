/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\seans                                            */
/*    Created:      Sat Sep 28 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"

using namespace vex;

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;
vex::motor leftMotor(vex::PORT1);
vex::motor rightMotor(vex::PORT10);
vex::controller fakeXbox = vex::controller();

// define your global instances of motors and other devices here


int main() {
   
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
