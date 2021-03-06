#include "littleBot.h"
#include "effectClass.h"
#include "eventTimer.h"
#include <iostream>
#include <tinyxml.h>
#include <list> 

using namespace std;
#include <string>

///globle timer for all players
Timer playersTimer; 



void littleBot::effectVelocity(double effect){
     currentVel = currentVel * effect;
     effectWithinRange();
}

void littleBot::effectTurning(double effect){
     currentTurn = currentTurn * effect;
     effectWithinRange();
}
void littleBot::effectSetVelocity(double effect){
     currentVel = effect;
     effectWithinRange();
}

void littleBot::effectSetTurning(double effect){
     currentTurn = effect;
     effectWithinRange();
}

string littleBot::getIP(){
     return ipAddress;
}

double littleBot::getTurning (){
     return currentTurn;
}

void littleBot::setTurning (double turnCMD){
     currentTurn = turnCMD * turningMax;
}

double littleBot::getVelocity (){
     return currentVel;
}

void littleBot::addEffect(effect* effectPtr){
     effectList.push_back(effectPtr);
}

void littleBot::printOutCurrentEffects(){
     cout << "player " << name <<" is effected by the following:" << endl;
     for(list<effect*>::iterator i = effectList.begin(); i !=effectList.end(); i++)
     {
          effect* effectPtr = *i;
          effectPtr->getName();
     }
}


void littleBot::setVelocity(double velCMD){
     if ((velCMD < 0.1) && (velCMD > -0.1)){velCMD = 0;}
     if (velCMD > 0){
          velocityCMD = velCMD * velocityForwardMax;
     }else{
          velocityCMD = velCMD * velocityReverseMax;
     }
     
}


void littleBot::update(){
     if (currentVel>0){                           // robot moving forward
          currentVel = currentVel + acceleration;
          if (currentVel > velocityCMD) {currentVel = velocityCMD;}
          if (currentVel < 0){currentVel = 0;}    //check not negetive
          
     }else if(currentVel<0){                      //robot moving backward
          currentVel = currentVel - acceleration;
          if (currentVel < velocityCMD) {currentVel = velocityCMD;} 
          if (currentVel > 0){currentVel = 0;}    //check not positive
          
     }else{
          if(velocityCMD > 0){
               currentVel = acceleration;
     }else if(velocityCMD < 0){
               currentVel = -acceleration;
     }else{
               currentVel = 0;
          }
     }

     withinRange();

     /////check cooldowns and remove//////////
     for(list<coolDown*>::iterator i = coolDownList.begin(); i !=coolDownList.end(); i++)
     {
          coolDown* CDPtr = *i;
          if( (playersTimer.elapsed() - CDPtr->startTime) > activeEffectArray[CDPtr->id].effectCD){
               delete CDPtr;
               coolDownList.erase(i++); // not sure why i++ not i
          } 
     }

     //printOutCurrentEffects();
     ////Apply effects /////
     for(list<effect*>::iterator i = effectList.begin(); i !=effectList.end(); i++)
     {
          effect* effectPtr = *i;
          if(effectPtr->checkTimeElapse()){
               delete effectPtr; 
               effectList.erase(i++);
          }else{
               effectPtr->applyEffect();

          }

     }



}

void littleBot::withinRange(){
     //check forward max speed
     if (currentVel > velocityForwardMax && currentVel > 0)
          {currentVel = velocityForwardMax;}
     //check max reverse speed
     if (currentVel < -velocityReverseMax && currentVel < 0)
          {currentVel = -velocityReverseMax;}
          //check forward max speed
     if (currentTurn > 100)
          {currentTurn = 100;}
     if (currentTurn < -100)
          {currentTurn = -100;}    
}

void littleBot::effectWithinRange(){
     //check forward max speed
     if (currentVel > 100 && currentVel > 0)
          {currentVel = 100;}
     //check max reverse speed
     if (currentVel < -100 && currentVel < 0)
          {currentVel = -100;}
          //check forward max speed
     if (currentTurn > 100)
          {currentTurn = 100;}
     if (currentTurn < -100)
          {currentTurn = -100;}    
}


void littleBot::useEffect(int E, littleBot* t){
     if (!effectOnCD(activeEffectArray[E].effectName)){
          ////Creates effect
          effect::Create(activeEffectArray[E].effectName, this, t, activeEffectArray[E].effectDur);
          //creates cool Down
          coolDown * CDptr = new coolDown();
          CDptr->effectName = activeEffectArray[E].effectName;
          CDptr->startTime = playersTimer.elapsed();
          CDptr->id = E;
          coolDownList.push_back(CDptr);
     }else {
          cout << "on CD" << endl;
     }

     
}

bool littleBot::effectOnCD(string abilitySelected){
     for(list<coolDown*>::iterator i = coolDownList.begin(); i !=coolDownList.end(); i++)
     {
          coolDown* test = *i;
          if( test->effectName == abilitySelected){return true;} 
     }
     return false;

}


littleBot::littleBot(string Name){

     cout << "creating player by file" << endl;
     std::stringstream ss;
     ss << "../littleBots_ws/src/little_bots/players/" << Name << ".xml";
     const char * filename = ss.str().c_str();
     TiXmlDocument doc(filename);
     bool loadOkay = doc.LoadFile();
     if (loadOkay)
     {
          printf("Player file loaded :  \"%s\"\n", filename);
          TiXmlHandle hDoc(&doc);
          TiXmlElement *pRoot, *pStats, *pAbilities; 
          pRoot = doc.FirstChildElement("Player");
          name = pRoot->Attribute("Name");
          pStats = pRoot->FirstChildElement("Stats");
               velocityForwardMax = atoi(pStats->Attribute("velocityForwardMax"))*0.75;
               velocityReverseMax = atoi(pStats->Attribute("velocityReverseMax"))*0.75;
               turningMax = atoi(pStats->Attribute("turningMax"));
               acceleration = atoi(pStats->Attribute("acceleration"));
               ipAddress = pStats->Attribute("ip");
               cout << ipAddress << endl;
          pAbilities = pStats->NextSiblingElement("Abilities"); // currently only looking at first three abilities should be loop
               pAbilities = pAbilities->FirstChildElement("AbilityA");
                    activeEffectArray[0].effectName = string(pAbilities->Attribute("AbilityName"));
                    activeEffectArray[0].effectCD = atof(pAbilities->Attribute("CoolDown")); 
                    activeEffectArray[0].effectDur = atof(pAbilities->Attribute("Duration"));
               pAbilities = pAbilities->NextSiblingElement("AbilityB");
                    activeEffectArray[1].effectName = string(pAbilities->Attribute("AbilityName"));
                    activeEffectArray[1].effectCD = atof(pAbilities->Attribute("CoolDown")); 
                    activeEffectArray[1].effectDur = atof(pAbilities->Attribute("Duration"));
               pAbilities = pAbilities->NextSiblingElement("AbilityX");
                    activeEffectArray[2].effectName = string(pAbilities->Attribute("AbilityName"));
                    activeEffectArray[2].effectCD = atof(pAbilities->Attribute("CoolDown")); 
                    activeEffectArray[2].effectDur = atof(pAbilities->Attribute("Duration")); 

     }
     else
     {
          printf("Failed to load file \"%s\"\n", filename);
     
     }
}
     







