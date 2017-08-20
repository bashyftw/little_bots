#include "effectClass.h"
#include "littleBot.h"
#include "eventTimer.h"
#include <string>
#include <iostream>
#include <algorithm> 
#include <list>


using namespace std;


Timer effectTimer; 


//////Effect Base Class
effect::effect(){
}

effect::~effect(){
}

string effect::getName(){
	cout << name <<endl;
	return name;
}

void effect::setName(string n){
	name = n; 
}


bool effect::checkTimeElapse(){
	double runTime = 0;
	if (timerStart == 0){
		timerStart = effectTimer.elapsed();
		return false;
	}else{
		//cout << effectTimer.elapsed() <<endl;
		double runTime = effectTimer.elapsed() - timerStart;
		cout << name << "  " << runTime << endl;

		if (runTime >= duration){
			return true;
		}else{
			return false;
		}

	}

}

void effect::applyEffect(){
}

/////////////////////////////////
////////////Effects///////////////
///////////////////////////////////
turboBoost::turboBoost(littleBot* c, littleBot* t, double effectDur){
	caster = c;
	target = c;
	duration = effectDur;
	timerStart = 0;
	name = "turboBoost";
	c->addEffect(this);
}

void turboBoost::applyEffect(){
	target->effectVelocity(2);
}


///////////////////////////////////
stun::stun(littleBot* c, littleBot* t, double effectDur){
	caster = c;
	target = t;
	duration = effectDur;
	timerStart = 0;
	name = "stun";
	t->addEffect(this);
}

void stun::applyEffect(){
	target->effectTurning(0);
	target->effectVelocity(0);
}


///////////////////////////////////
randomEff::randomEff(littleBot* c, littleBot* t, double effectDur){
	caster = c;
	target = t;
	timerStart = 0;
	duration = effectDur;
	name = "randomEff";
	t->addEffect(this);
}

void randomEff::applyEffect(){
	double vel = rand() % 120 -60;
	double turn = rand() % 120 -60;
	target->effectSetVelocity(vel);
	target->effectSetTurning(turn);
}



/////// Effect Selector //////////////
effect* effect::Create(string type, littleBot* c, littleBot* t, double effectDur) {
    if ( type == "turboBoost" ) return new turboBoost(c, t, effectDur);
    if ( type == "stun" ) return new stun(c, t, effectDur);
    if ( type == "randomEff" ) return new randomEff(c, t, effectDur);
    return NULL;

}