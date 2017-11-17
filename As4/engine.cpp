#include "engine.h"
#include <OgreTimer.h>
#include"Types.h"
Engine::Engine(){
    gfxMgr = 0;
	inputMgr = 0;
	entityMgr = 0;
    gameMgr = 0;
	keepRunning = true;

}

Engine::~Engine(){

}

void Engine::stop(){
	keepRunning = false;
}

void Engine::init(){
// construct
   gfxMgr = new GfxMgr(this);
   inputMgr = new InputMgr(this);
   entityMgr = new EntityMgr(this);
   gameMgr = new GameMgr(this);
   unitAI=new UnitAI(ent,this);
   Ogre::Timer* timer = new Ogre::Timer();
// initialize
	gfxMgr->init();
	inputMgr->init();
	entityMgr->init();
    gameMgr->init();
// load level to play
	gfxMgr->loadLevel();
	inputMgr->loadLevel();
	entityMgr->loadLevel();
    gameMgr->loadLevel();
}

void Engine::tickAll(float dt){
     gfxMgr->tick(dt);
     inputMgr->tick(dt);
	 entityMgr->tick(dt);
	 gameMgr->tick(dt);
}

void Engine::shutdown(){
	inputMgr->stop();
	gfxMgr->stop();
	entityMgr->stop();
	gameMgr->stop();
}
void Engine::run(){
   // gfxMgr->mSceneMgr->setAmbientLight(Ogre::ColourValue(.5, .5, .5));
	Ogre::Timer* timer = new Ogre::Timer();
	float oldTime = timer->getMilliseconds()/1000.0f;
	float newTime;
	float dt = 0.001f;
	while(keepRunning){
		newTime = timer->getMilliseconds()/1000.0f;
		dt = newTime - oldTime;
		oldTime = newTime;
		tickAll(dt);
	}
	shutdown();

	return;
}
