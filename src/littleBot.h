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
          string ipAddress;
          double velocityForwardMax;
          double velocityReverseMax;   
          double turningMax;
          double acceleration;
          double currentVel;  
          double currentTurn;
          double velocityCMD;
          effect* Ability;
          list<effect*>effectList;
          list<coolDown*>coolDownList;
          activeEffect activeEffectArray[6];

          string AbilityA;
          double ACD;
          double ADur;

          string AbilityB;
          double BCD;
          double BDur;

          string AbilityX;
          double XCD;
          double XDur;

          string AbilityY;
          double YCD;
          double YDur;



 

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


          void useEffect(int E, littleBot* t);
          bool effectOnCD(string abilitySelected);


                    
};

class Timer
{
public:
    Timer() { clock_gettime(CLOCK_REALTIME, &beg_); }

    double elapsed() {
        clock_gettime(CLOCK_REALTIME, &end_);
        return end_.tv_sec - beg_.tv_sec +
            (end_.tv_nsec - beg_.tv_nsec) / 1000000000.;
    }

    void reset() { clock_gettime(CLOCK_REALTIME, &beg_); }

private:
    timespec beg_, end_;
};


 
#endif