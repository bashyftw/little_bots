#ifndef LITTLEBOT_H
#define LITTLEBOT_H


using namespace std;
#include <string>




class littleBot
{
     private:
          string ipAddress;
          double velocityForwardMax;
          double velocityReverseMax;   
          double turningMax;
          double acceleration;
          double currentVel;  
          double currentTurn;
          double velocityCMD;   

     public :
          littleBot(string Name);
          
          littleBot(bool fullpower);
          
          double getVelocity();
          void setVelocity(double velCMD);
          void update();
          double getTurning();
          void setTurning (double turnCMD);
          void effectVelocity(double effect);
          void effectTurning(double effect);
          void effectSetVelocity(double effect);
          void effectSetTurning(double effect);

          void effectWithinRange();
          void withinRange();
          string getIP();




                    
};


 
#endif