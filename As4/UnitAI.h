
#ifndef UNITAI_H_
#define UNITAI_H_

#include "Aspect.h"
#include "Command.h"
#include <list>
class Entity381;
class Engine;
class UnitAI: public Aspect
 {

public:

	std::list<Command*> commands;

	UnitAI(Entity381* ent,Engine*eng);
	~UnitAI();
    Entity381 *entity;
    Engine *engine;
	void Tick(float dt);
	void init();
	void SetCommand(Command *c);
	void AddCommand(Command *c);

};

#endif
