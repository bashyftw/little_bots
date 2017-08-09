#ifndef EFFECTCLASS_H
#define EFFECTCLASS_H

using namespace std;
#include <string>
#include <ctime>
#include <list>

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

        static effect* Create(string type);
     	  virtual void applyEffect();
      	bool checkCD(string name, littleBot* caster);
      	bool checkTimeElapse();
      	bool checkEffectActive();
        string getName();
        void setName(string n);

};


class turboBoost : public effect{
	private:
		
	public:
    turboBoost();
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






 
#endif