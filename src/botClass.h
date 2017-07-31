#ifndef BOTCLASS_H
#define BOTCLASS_H
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
          
          littleBot(string ip, double vFM, double vRM, double tM, double acc);
          littleBot();
          littleBot(bool fullpower);

          double getVelocity();
          void setVelocity(double velCMD);
          void update();
          double getTurning();
          void setTurning (double turnCMD);
          void effectVelocity(double effect);
          void withinRange();
          string getIP();
          
};


 
#endif