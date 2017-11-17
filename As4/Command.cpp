#include "Command.h"
   Command::Command(Entity381* ent, COMMAND_TYPE ct)
	{
      this->entity=ent;
      this->commandType=ct;
	}
   Command::~Command()
	{

	}

	void  Command::init()
	{

	}
	void  Command::tick(float dt)
	{

	}
    bool  Command::done()
	{

	}

	MoveTo::MoveTo(Entity381* ent, Ogre::Vector3 location,COMMAND_TYPE ct):Command(ent,ct)
	{
	   this->targetLocation=location;
	}
	MoveTo::~MoveTo()
	{

	}

	void MoveTo::init()
	{

	}
	void MoveTo::tick(float dt)
	{
       //std::cout<<"*************************************Navin Kumar Adhikari***************************************************"<<std::endl;
       Ogre::Vector3 currentpos=entity->ogreSceneNode->getPosition();
       float dx=targetLocation.x-currentpos.x;
       float dz=targetLocation.z-currentpos.z;
       entity->desiredHeading= atan2(dz,dx);
       float d = currentpos.distance(targetLocation);
       if(d>25.0)
       {
         entity->desiredSpeed=entity->maxSpeed;
       }
       if(d<25)
       {
         targetDone=true;
         entity->vel=Ogre::Vector3::ZERO;
         entity->desiredSpeed=0;
         entity->speed=0;
       }
       std::cout << "Desired Heading" << entity->desiredHeading<<std::endl;
	}
	bool MoveTo::done()
	{
      return targetDone;
	}
	Follow:: Follow(Entity381 *ent, Entity381 *targetObj,COMMAND_TYPE ct):Command(ent,ct)
	{
	   this->targetEntity=targetObj;
	}
	Follow::~Follow()
	{

	}

	void Follow::init()
	{

	}
	void Follow::tick(float dt)
	{
       Ogre::Vector3 currentpos=entity->ogreSceneNode->getPosition();
       Ogre::Vector3 targetLocation=targetEntity->ogreSceneNode->getPosition();
       float dx=targetLocation.x-currentpos.x;
       float dz=targetLocation.z-currentpos.z;
       entity->desiredHeading= atan2(dz,dx);
       float d = currentpos.distance(targetLocation);
       if(d>100.0)
       {
         entity->desiredSpeed=entity->maxSpeed;
       }
       if(d<100)
       {
         targetDone=true;
         entity->vel=Ogre::Vector3::ZERO;
         entity->desiredSpeed=0;
         entity->speed=0;
       }
       std::cout << "Inside the tick function of Follow class"<<std::endl;
	}
	bool Follow::done()
	{
       return targetDone;
	}

