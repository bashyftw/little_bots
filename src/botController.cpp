#include "ros/ros.h"
#include "std_msgs/String.h"
#include "sensor_msgs/Joy.h"
#include "little_bots/botMsg.h"
#include <string>
#include <vector>
#include <tinyxml.h>

#include "effectClass.h"
#include "littleBot.h"

using namespace std;
//tinyxml2::XMLDocument xmlDoc("hello.xml");



//update rate 10Hz
int rate = 10;

//Create Bots
//littleBot P2("192.168.1.172",5,2,1,0.05);
littleBot P1;
littleBot P2(true);

vector<effect> effectList;


little_bots::botMsg CMD_Message;

///forward Dec
void addEffect(string effName, littleBot* c, littleBot* t);
void updateCB(const ros::TimerEvent&);
void dump_to_stdout(const char* pFilename);
int dump_attribs_to_stdout(TiXmlElement* pElement, unsigned int indent);
ros::Publisher botCMD_pub;





void joyCB1(const sensor_msgs::Joy::ConstPtr& joy)
{
  P1.setVelocity (joy->axes[1]);
  P1.setTurning (joy->axes[3]);
  if (joy->buttons[0]){
    addEffect("stun", &P1, &P2);
  }
  if (joy->buttons[1]){
    addEffect("turboBoost", &P1, &P1);
  }
  if (joy->buttons[2]){
    addEffect("randomEff", &P1, &P2);
  }
}

void joyCB2(const sensor_msgs::Joy::ConstPtr& joy)
{
  P2.setVelocity (joy->axes[1]);
  P2.setTurning (joy->axes[3]);
    if (joy->buttons[0]){
    addEffect("stun", &P2, &P1);
  }
  if (joy->buttons[1]){
    addEffect("turboBoost", &P2, &P2);
  }
  if (joy->buttons[2]){
    addEffect("randomEff", &P2, &P1);
  }
  //ROS_INFO("P1 current vel: [%f]", joy->axes[1]);
}



int main(int argc, char **argv)
{
	dump_to_stdout("../littleBots_ws/src/little_bots/findme.xml");

  ros::init(argc, argv, "botController");
  ros::NodeHandle n;

  ros::Rate update_rate(rate);

  ros::Subscriber sub1 = n.subscribe("playerJoy1", 1, joyCB1);
  ros::Subscriber sub2 = n.subscribe("playerJoy2", 1, joyCB2);
  botCMD_pub = n.advertise<little_bots::botMsg>("botCMD", 1);
  CMD_Message.num_players = 2;
  
  //addEffect("effect", &P1, &P1);
  // stun aa(&P1, &P1);
  // turboBoost bb(&P1, &P1);
  // effectList.push_back(aa);
  // effectList.push_back(bb);


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

void dump_to_stdout(const char* pFilename)
{
	TiXmlDocument doc(pFilename);
	bool loadOkay = doc.LoadFile();
	if (loadOkay)
	{
		printf("\n%s:\n", pFilename);

                TiXmlHandle hDoc(&doc);
                TiXmlElement *pRoot, *pParm;
                pRoot = doc.FirstChildElement("Player");
                if(pRoot)
                {
                    pParm = pRoot->FirstChildElement("Stats");
                    while(pParm)
                    {
                        P1.setVelocity(atoi(pParm->Attribute("velocityForwardMax")));
                        printf("%s\n", pParm->Attribute("velocityForwardMax"));
                        pParm = pParm->NextSiblingElement("Stats");
                    }
                }

	}
	else
	{
		printf("Failed to load file \"%s\"\n", pFilename);
	
		}

	TiXmlDocument NewPlayer;
	TiXmlElement* player = new TiXmlElement("Player");
	NewPlayer.LinkEndChild(player);
		TiXmlElement* stats = new TiXmlElement("Stats");
		player->LinkEndChild(stats);
	 	stats->SetAttribute("velocityForwardMax", "50");
	 	stats->SetAttribute("velocityReverseMax", "30");
	 	stats->SetAttribute("turningMax", "20");
	 	stats->SetAttribute("acceleration", "5");

	 	TiXmlElement* abilities = new TiXmlElement("Abilities");
	 	player->LinkEndChild(abilities);
	 	abilities->SetAttribute("abilityA", "stun");
	 	abilities->SetAttribute("abilityB", "turboBoost");
	 	abilities->SetAttribute("abilityX", "randomEff");
	 	abilities->SetAttribute("abilityY", "empty");
		NewPlayer.SaveFile("../littleBots_ws/src/little_bots/findme.xml");
}

