#ifndef ENGINE_H_
#define ENGINE_H_
#include "GfxMgr.h"
#include "inputMgr.h"
#include "EntityMgr.h"
#include "gameMgr.h"
#include "UnitAI.h"
class GameMgr;
class GfxMgr;
class InputMgr;
class EntityMgr;
class UnitAI;
class Entity381;
class Engine
{
private:
public:
	Engine();
	~Engine();
	EntityMgr* entityMgr;
    GfxMgr* gfxMgr;
	InputMgr* inputMgr;
	GameMgr* gameMgr;
	Entity381 *ent;
	UnitAI * unitAI;
	Entity381 *entity;
	//SelectionMgr* selectionMgr;
	//ControlMgr*   controlMgr;

	void init();
	void run();
	void tickAll(float dt);
	void stop();
	void shutdown();

	//
	bool keepRunning;


};

#endif /* ENGINE_H_ */
