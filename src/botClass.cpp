#include "botClass.h"
//using namespace std;
#include <string>







void littleBot::effectVelocity(double effect){
     currentVel = currentVel * effect;
     withinRange();
}

string littleBot::getIP(){
     return ipAddress;
}

double littleBot::getTurning (){
     return currentTurn;
}

void littleBot::setTurning (double turnCMD){
     currentTurn = turnCMD * turningMax;
}

double littleBot::getVelocity (){
     return currentVel;
}

void littleBot::setVelocity(double velCMD){
     if ((velCMD < 0.1) && (velCMD > -0.1)){velCMD = 0;}
     if (velCMD > 0){
          velocityCMD = velCMD * velocityForwardMax;
     }else{
          velocityCMD = velCMD * velocityReverseMax;
     }
     
}


void littleBot::update(){
     if (currentVel>0){                           // robot moving forward
          currentVel = currentVel + acceleration;
          if (currentVel > velocityCMD) {currentVel = velocityCMD;}
          if (currentVel < 0){currentVel = 0;}    //check not negetive
          
     }else if(currentVel<0){                      //robot moving backward
          currentVel = currentVel - acceleration;
          if (currentVel < velocityCMD) {currentVel = velocityCMD;} 
          if (currentVel > 0){currentVel = 0;}    //check not positive
          
     }else{
          if(velocityCMD > 0){
               currentVel = acceleration;
     }else if(velocityCMD < 0){
               currentVel = -acceleration;
     }else{
               currentVel = 0;
          }
     }

     withinRange();
}

void littleBot::withinRange(){
     //check forward max speed
     if (currentVel > velocityForwardMax && currentVel > 0)
          {currentVel = velocityForwardMax;}
     //check max reverse speed
     if (currentVel < -velocityReverseMax && currentVel < 0)
          {currentVel = -velocityReverseMax;}  
}

//Class Constructor
littleBot::littleBot(string ip, double vFM, double vRM, double tM, double acc){
     ipAddress = ip;
     velocityForwardMax = vFM;
     velocityReverseMax = vRM;
     turningMax = tM;
     acceleration = acc;
}

//Class Constructor default
littleBot::littleBot(){
     ipAddress = "192.168.1.174";
     velocityForwardMax = 80;
     velocityReverseMax = 40;
     turningMax = 30;
     acceleration = 10;
}

littleBot::littleBot(bool fullpower){
     ipAddress = "192.168.1.174";
     velocityForwardMax = 100;
     velocityReverseMax = 100;
     turningMax = 100;
     acceleration = 2;

}
