#ifndef LITTLEBOT_H
#define LITTLEBOT_H


using namespace std;
#include <string>

#include <list>
#include "effectClass.h"



class littleBot
{
     struct coolDown{
          string effectName;
          double startTime;
          int id;
     };

     struct activeEffect{
          string effectName;
          double effectCD;
          double effectDur;
     };

     private:
          string name;
          string ipAddress;
          double velocityForwardMax;
          double velocityReverseMax;   
          double turningMax;
          double acceleration;
          double currentVel;  
          double currentTurn;
          double velocityCMD;
          
          list<effect*>effectList;
          list<coolDown*>coolDownList;
          activeEffect activeEffectArray[6];
 

     public :
          littleBot(string Name);

          
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


          void useEffect(int E, littleBot* t);
          bool effectOnCD(string abilitySelected);
          void addEffect(effect* effectPtr);
          void printOutCurrentEffects();
                    
}; 
#endif