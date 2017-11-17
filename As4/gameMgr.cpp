#include "engine.h"
#include <OgreEntity.h>
#include <OgreMeshManager.h>


GameMgr::GameMgr(Engine *eng) : Mgr(eng) {

}

GameMgr::~GameMgr() {

}

void GameMgr::init() {
   b1=Ogre::Vector3 (0,0,0);
   b2=Ogre::Vector3 (100,0,0);
   b3=Ogre::Vector3 (0,0,-300);
   b4=Ogre::Vector3 (0,0,-700);
   b5=Ogre::Vector3 (-200,0,-200);
   head=0.0;
}

void GameMgr::tick(float dt) {


}

void GameMgr::loadLevel() {

    engine->gfxMgr->mSceneMgr->setAmbientLight(Ogre::ColourValue(.5,.5,.5));
    engine->gfxMgr->mCamera->setPosition(0,220,300);
    Ogre::Light *pointLight =  engine->gfxMgr->mSceneMgr->createLight("PointLight");
    pointLight->setType(Ogre::Light::LT_POINT);
    pointLight->setPosition(250, 150, 250);
    pointLight->setDiffuseColour(Ogre::ColourValue::White);
    pointLight->setSpecularColour(Ogre::ColourValue::White);
    // Create ground
    plane=Ogre::Plane(Ogre::Vector3::UNIT_Y, 0);
    Ogre::MeshManager::getSingleton().createPlane("ground",
            Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
            plane, 10000, 10000, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);

    Ogre::Entity *groundEntity =  engine->gfxMgr->mSceneMgr->createEntity("ground");
    engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode("ground")->attachObject(groundEntity);
    groundEntity->setMaterialName("Examples/sea");

    entity[0]=engine->entityMgr->CreateEntity(EntityType::ALIEN,b1,head);
    entity[1]=engine->entityMgr->CreateEntity( EntityType::CIGARETTE,b2,head);
    entity[2]=engine->entityMgr->CreateEntity( EntityType::DDG,b3, head);
    entity[3]=engine->entityMgr->CreateEntity( EntityType::CVN,b4,head);
    entity[4]=engine->entityMgr->CreateEntity( EntityType::FRIGATE,b5,head);


}

void GameMgr::stop() {


}
