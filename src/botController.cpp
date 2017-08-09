#include "ros/ros.h"
#include "std_msgs/String.h"
#include "sensor_msgs/Joy.h"
#include "little_bots/botMsg.h"
#include <string>
#include <vector>
#include <tinyxml.h>
#include <map>

#include "effectClass.h"
#include "littleBot.h"

using namespace std;

//update rate 10Hz
int rate = 10;

///////Create Bots ///////

littleBot P1(string("bashy"));
littleBot P2(string("captionWOW"));

vector<effect> effectList;


little_bots::botMsg CMD_Message;

///forward Dec
void addEffect(string effName, littleBot* c, littleBot* t);
void updateCB(const ros::TimerEvent&);
void playerReadDemo(const char* pFilename);
void createPlayerXML (string name);
ros::Publisher botCMD_pub;





void joyCB(const sensor_msgs::Joy::ConstPtr& joy, const int &joyNo)
{
  littleBot *player, *target;
  //littleBot &target;
  switch(joyNo) {
      case 1 : {player = &P1; target = &P2;break;}
      case 2 : {player = &P2; target = &P1;break;}
  }

  player->setVelocity(joy->axes[1]);
  player->setTurning(joy->axes[3]);


  for (int i = 0; i <= 2; i++)
    {
     if (joy->buttons[i]){player->useEffect(i, target);}
    }

  // P2.setVelocity (joy->axes[1]);
  // P2.setTurning (joy->axes[3]);
  //   if (joy->buttons[0]){
  //   addEffect("stun", &P2, &P1);
  // }
  // if (joy->buttons[1]){
  //   addEffect("turboBoost", &P2, &P2);
  // }
  // if (joy->buttons[2]){
  //   addEffect("randomEff", &P2, &P1);
  // }
  //ROS_INFO("P1 current vel: [%f]", joy->axes[1]);
}





int main(int argc, char **argv)
{
	//createPlayerXML("captionWOW");

  ros::init(argc, argv, "botController");
  ros::NodeHandle n;

  ros::Rate update_rate(rate);

  ros::Subscriber sub1 = n.subscribe<sensor_msgs::Joy>("playerJoy1", 1, boost::bind(joyCB, _1, 1));
  ros::Subscriber sub2 = n.subscribe<sensor_msgs::Joy>("playerJoy2", 1, boost::bind(joyCB, _1, 2));

  botCMD_pub = n.advertise<little_bots::botMsg>("botCMD", 1);
  CMD_Message.num_players = 2;
  
  //addEffect("effect", &P1, &P1);
  // stun aa(&P1, &P1);
  // turboBoost bb(&P1, &P1);
  // effectList.push_back(aa);
  // effectList.push_back(bb);
  //effect* obj2 = effect::Create("turboBoost");
  //effect* obj1 = effect::Create("stun");

  //addEffect("turboBoost", &P1, &P1);

  ros::Timer timer = n.createTimer(ros::Duration(0.1), updateCB);
  ros::spin();



  return 0;
}



void addEffect(string effName, littleBot* c, littleBot* t){      
      bool onCD = false;
      vector <effect>::iterator it3;
      for (it3 = effectList.begin(); it3 != effectList.end(); ++it3) {
        if ( it3->checkCD(effName, c)){ onCD = true; }
      }
      if (!onCD){
        if (effName == "stun"){stun aa(c, t);effectList.push_back(aa);}
        else if (effName == "turboBoost"){turboBoost bb(c, t);effectList.push_back(bb);}
        else if (effName == "randomEff"){randomEff cc(c, t);effectList.push_back(cc);}

        //stun bb(c, t);
        
        cout << "effect added: " << effName << " To Player " << t <<endl;
      }else{
        //cout << "effect on Cool Down" <<endl;
      }
}


void effectUpdate(){
  vector <effect>::iterator it3;
  for (it3 = effectList.begin(); it3 != effectList.end(); ) {
    if (it3->checkTimeElapse()){ 
      //it3->~effect();
      //delete &it3;   
      it3 = effectList.erase(it3);
      return;
      //--it3;
    }else{
      if (it3->checkEffectActive()){
        it3->applyEffect();
      } 
      ++it3;
    }
  }

}

// vector <effect>::iterator it3;
//       for (it3 = effectList.begin(); it3 != effectList.end(); ++it3) {
//         if ( it3->get_name() == effName ){ 
//             //delete &it3;
//             it3->~effect();   
//             it3 = effectList.erase(it3);
//             --it3;
//             //effectList.erase(effectList.begin()+it3);
//         }

void updateCB(const ros::TimerEvent&)
{
  

  P1.update();
  P2.update();
  effectUpdate();
  CMD_Message.ip[0] = P1.getIP();
  CMD_Message.velocity[0] = P1.getVelocity();
  CMD_Message.turning[0] = P1.getTurning();
  CMD_Message.ip[1] = P2.getIP();
  CMD_Message.velocity[1] = P2.getVelocity();
  CMD_Message.turning[1] = P2.getTurning();


  botCMD_pub.publish(CMD_Message);


}



//////this is a default layout for xml creation/////
void createPlayerXML (string name)
{
	TiXmlDocument NewPlayer;
	TiXmlElement* player = new TiXmlElement("Player");
	NewPlayer.LinkEndChild(player);
  player->SetAttribute("Name", name);
		TiXmlElement* stats = new TiXmlElement("Stats");
		player->LinkEndChild(stats);
	 	stats->SetAttribute("velocityForwardMax", "50");
	 	stats->SetAttribute("velocityReverseMax", "30");
	 	stats->SetAttribute("turningMax", "20");
	 	stats->SetAttribute("acceleration", "5");
    stats->SetAttribute("ip", "192.168.1.172");

	 	TiXmlElement* abilities = new TiXmlElement("Abilities");
	 	player->LinkEndChild(abilities);
      TiXmlElement* abilityA = new TiXmlElement("AbilityA");
      abilities->LinkEndChild(abilityA);
        abilityA->SetAttribute("AbilityName", "stun");
        abilityA->SetAttribute("Duration", "2");
        abilityA->SetAttribute("CoolDown", "30");
      TiXmlElement* abilityB = new TiXmlElement("AbilityB");
      abilities->LinkEndChild(abilityB);
        abilityB->SetAttribute("AbilityName", "turboBoost");
        abilityB->SetAttribute("Duration", "3");
        abilityB->SetAttribute("CoolDown", "9");
      TiXmlElement* abilityX = new TiXmlElement("AbilityX");
      abilities->LinkEndChild(abilityX);
        abilityX->SetAttribute("AbilityName", "randomEff");
        abilityX->SetAttribute("Duration", "2");
        abilityX->SetAttribute("CoolDown", "15");
      TiXmlElement* abilityY = new TiXmlElement("AbilityY");
      abilities->LinkEndChild(abilityY);
        abilityY->SetAttribute("AbilityName", "na");
        abilityY->SetAttribute("Duration", "0");
        abilityY->SetAttribute("CoolDown", "0");

    std::stringstream ss;
    ss << "../littleBots_ws/src/little_bots/players/" << name << ".xml";
    const char * c = ss.str().c_str();
		NewPlayer.SaveFile(c);
}

