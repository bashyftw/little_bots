#include "effectClass.h"
#include "littleBot.h"
#include <string>
#include <iostream>
#include <algorithm> 
#include <list>


using namespace std;






//////Effect Base Class
effect::effect(littleBot* c, littleBot* t){
	timerStart = 0;
	name = "testing 123";
	cout << "effect constructor" << endl;
	duration = 10000;
}

effect::effect(){
	cout << "effect constructor" << endl;
	name = "testing 123";
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
		//timerStart = tmr.elapsed();
		return false;
	}else{
		//double runTime = tmr.elapsed() - timerStart;
		//cout << name << "  " << runTime << endl;

		if (runTime>(max(duration,coolDown))){
			return true;
		}else{
			return false;
		}

	}

}

bool effect::checkEffectActive(){
	double runTime = 0;
	//double runTime = tmr.elapsed() - timerStart;
	if (runTime<duration){
			return true;
		}else{
			return false;
		}
}


void effect::applyEffect(){
	if (name == "turboBoost"){
		target->effectVelocity(2);
		target->effectTurning(2);
	}else if(name == "stun"){
		target->effectVelocity(0);
		target->effectTurning(0);
	}else if(name == "randomEff"){
		double vel = rand() % 120 -60;
		double turn = rand() % 120 -60;
		target->effectSetVelocity(vel);
		target->effectSetTurning(turn);
	}else{
		cout << "wrong effect" << endl;
	}
}


bool effect::checkCD(string n, littleBot* c){
if (name == n && c == caster)
{
	return true;
}else
	return false;
}








///////////////////////////////////
turboBoost::turboBoost(){
	name = "turboBoost";
	cout << "turbo baby" << endl;
};

turboBoost::turboBoost(littleBot* c, littleBot* t){
	caster = c;
	target = t;
	duration = 3;
	coolDown = 10;
	timerStart = 0;
	name = "turboBoost";
	cout << "turboBoost constructor" << endl;
}



void turboBoost::applyEffect(){

	target->effectVelocity(2);
}


///////////////////////////////////
stun::stun(){
	name = "stun";
	cout << "get stunned" << endl;
};

stun::stun(littleBot* c, littleBot* t){
	caster = c;
	target = t;
	duration = 1;
	coolDown = 30;
	timerStart = 0;
	name = "stun";
	cout << "stun constructor" << endl;
}


void stun::applyEffect(){

	target->effectVelocity(0);
}


///////////////////////////////////
randomEff::randomEff(){
	name = "randomEff";
	cout << "randimer" << endl;
};

randomEff::randomEff(littleBot* c, littleBot* t){
	caster = c;
	target = t;
	duration = 2;
	coolDown = 15;
	timerStart = 0;
	name = "randomEff";
	cout << "randomEff constructor" << endl;
}


void randomEff::applyEffect(){

	target->effectVelocity(0);
}


effect* effect::Create(string type) {
    if ( type == "turboBoost" ) return new turboBoost();
    if ( type == "stun" ) return new stun();
    if ( type == "randomEff" ) return new randomEff();
    return NULL;

}