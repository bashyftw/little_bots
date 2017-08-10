#ifndef EFFECTCLASS_H
#define EFFECTCLASS_H

using namespace std;
#include <string>
#include <ctime>
#include <list>

//forward Dec///
class littleBot;




class effect{
  protected:
    string name;
    string description;
    littleBot* target;
    littleBot* caster;
    double duration;
    double timerStart;

  public:
    effect();
    ~effect();

    static effect* Create(string type, littleBot* c, littleBot* t, double effectDur);
    virtual void applyEffect();
    bool checkTimeElapse();
    string getName();
    void setName(string n);

};


class turboBoost : public effect{
	private:
		
	public:
		turboBoost(littleBot* c, littleBot* t, double effectDur);
		void applyEffect();

};

class stun : public effect{
	private:
		
	public:
		stun(littleBot* c, littleBot* t, double effectDur);
		void applyEffect();

};

class randomEff : public effect{
	private:
		
	public:
		randomEff(littleBot* c, littleBot* t, double effectDur);
		void applyEffect();

};






 
#endif