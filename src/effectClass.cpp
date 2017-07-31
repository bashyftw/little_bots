#include "effectClass.h"
#include "littleBot.h"
#include <string>
#include <iostream>
#include <algorithm> 


using namespace std;
Timer tmr;


//////Effect Base Class
effect::effect(littleBot* c, littleBot* t){
	timerStart = 0;
	name = "testing 123";
	cout << "effect constructor" << endl;
	duration = 10000;
}

bool effect::checkTimeElapse(){
	
	if (timerStart == 0){
		timerStart = tmr.elapsed();
		return false;
	}else{
		double runTime = tmr.elapsed() - timerStart;
		cout << name << "  " << runTime << endl;

		if (runTime>(max(duration,coolDown))){
			return true;
		}else{
			return false;
		}

	}

}

bool effect::checkEffectActive(){
	double runTime = tmr.elapsed() - timerStart;
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


effect::effect(){

}



///////////////////////////////////
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
stun::stun(){};

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
randomEff::randomEff(){};

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


