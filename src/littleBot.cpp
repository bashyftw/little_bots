#include "littleBot.h"
#include "effectClass.h"
#include <iostream>
#include <tinyxml.h>

using namespace std;
#include <string>




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

//Class Constructor

littleBot::littleBot(bool fullpower){
     cout << "creating player fullpower" << endl;
     ipAddress = "192.168.1.172";
     velocityForwardMax = 60;
     velocityReverseMax = 40;
     turningMax = 40;
     acceleration = 10;

     

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
          pStats = pRoot->FirstChildElement("Stats");
               velocityForwardMax = atoi(pStats->Attribute("velocityForwardMax"));
               velocityReverseMax = atoi(pStats->Attribute("velocityReverseMax"));
               turningMax = atoi(pStats->Attribute("turningMax"));
               acceleration = atoi(pStats->Attribute("acceleration"));
               ipAddress = pStats->Attribute("ip");
               cout << ipAddress << endl;
          pAbilities = pStats->NextSiblingElement("Abilities"); // currently only looking at forst two abilities
               pAbilities = pAbilities->FirstChildElement("AbilityA");
                    effect* AbilityA = effect::Create(pAbilities->Attribute("AbilityName")); 
               pAbilities = pAbilities->NextSiblingElement("AbilityB");
                    effect* AbilityB = effect::Create(pAbilities->Attribute("AbilityName")); 

     }
     else
     {
          printf("Failed to load file \"%s\"\n", filename);
     
     }
}
     







