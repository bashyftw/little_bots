#ifndef EFFECTCLASS_H
#define EFFECTCLASS_H

using namespace std;
#include <string>
#include <ctime>

class littleBot;




class effect{
     protected:
        string name;
        string description;
        littleBot* target;
        littleBot* caster;
       	double duration;
       	double coolDown;
       	double timerStart;

     public:
     	effect();
     	effect(littleBot* c, littleBot* t);


     	virtual void applyEffect();
      	bool checkCD(string name, littleBot* caster);
      	bool checkTimeElapse();
      	bool checkEffectActive();
};


class turboBoost : public effect{
	private:
		
	public:
		turboBoost(littleBot* c, littleBot* t);
		void applyEffect();

};

class stun : public effect{
	private:
		
	public:
		stun();
		stun(littleBot* c, littleBot* t);
		void applyEffect();

};


class randomEff : public effect{
	private:
		
	public:
		randomEff();
		randomEff(littleBot* c, littleBot* t);
		void applyEffect();

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