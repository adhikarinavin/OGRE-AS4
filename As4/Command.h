#ifndef COMMAND_H_
#define COMMAND_H_

#include "Entity381.h"
#include <OgreVector3.h>
#include "CommandTypes.h"

class Entity381;
class Command
{

public:
	Command(Entity381* ent, COMMAND_TYPE ct);
	virtual ~Command();

	virtual void init();
	virtual void tick(float dt);
	virtual bool done();

	Entity381* entity;
	COMMAND_TYPE commandType;

};

class MoveTo: public Command
{

public:
	MoveTo(Entity381* ent, Ogre::Vector3 location,COMMAND_TYPE ct);
	~MoveTo();

	void init();
	void tick(float dt);
	bool done();

	Ogre::Vector3 targetLocation;
	float MOVE_DISTANCE_THRESHOLD=25;
	bool targetDone=false;
};
class Follow : public Command
{

public:
    Follow(Entity381 *ent, Entity381 *targetObj,COMMAND_TYPE ct);

    ~Follow();

    void init();

    void tick(float dt);

    bool done();

    Entity381 *targetEntity;
    float MOVE_DISTANCE_THRESHOLD = 25;
    bool targetDone=false;

};






#endif
