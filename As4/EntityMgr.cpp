#include "EntityMgr.h"
#include "engine.h"
#include<iostream>

EntityMgr::EntityMgr(Engine *eng): Mgr(eng)
{
	entities.clear();
	selectedEntity = 0;
}

EntityMgr::~EntityMgr(){
	entities.clear();
}

void EntityMgr::tick(float dt){
	for (std::list<Entity381 *>::const_iterator it = entities.begin(); it != entities.end(); ++it){
		(*it)->Tick(dt);
		if ((*it)->isSelected)
			this->selectedEntity = (*it);
	}
}

void EntityMgr::init(){
	return;
}

void EntityMgr::loadLevel(){

}

void EntityMgr::stop(){
	return;
}

void EntityMgr::CreateOgreEntityAndNode(Entity381 *ent)
{
	if(ent) {
            //std::cout<<"CreateOgre Navin Adhikari"<<std::endl;
		    ent->ogreEntity=engine->gfxMgr->mSceneMgr->createEntity(ent->meshfile);
		    ent->ogreSceneNode = engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode(ent->pos);
		    ent->ogreSceneNode->attachObject(ent->ogreEntity);
		    ent->ogreSceneNode->yaw(Ogre::Radian(ent->heading));
		    //std::cout<<"Go Navin Kumar Adhikari"<<std::endl;
	}

}

Entity381* EntityMgr::CreateEntity(EntityType entityType, Ogre::Vector3 position, float heading){

	Entity381 *ent = 0;
	switch(entityType){
	case EntityType::ALIEN:
		ent = new Alien(position, heading);
		break;
	case EntityType::CIGARETTE:
		ent = new Cigarette(position, heading);
		break;
	case EntityType::DDG:
		ent = new Ddg(position, heading);
		break;
	case EntityType::CVN:
		ent = new Cvn(position, heading);
		break;
	case EntityType::FRIGATE:
		ent = new Frigate(position, heading);
		break;
	default:
		ent = new Ddg(position, heading);
		break;
	}
	CreateOgreEntityAndNode(ent);
	switch(entityType){
	case EntityType::ALIEN:
        ent->ogreEntity->setMaterialName("Examples/5");
		break;
	case EntityType::CIGARETTE:
		ent->ogreEntity->setMaterialName("Examples/5");
		break;DDG:
		ent->ogreEntity->setMaterialName("Examples/3");
		break;
	case EntityType::CVN:
		ent->ogreEntity->setMaterialName("Examples/4");
		break;
	case EntityType::FRIGATE:
		ent->ogreEntity->setMaterialName("Examples/2");
		break;
	default:
		break;
	}
	entities.push_front(ent);
	return ent;
}

void EntityMgr::SelectNextEntity(){
	int n = 0;
	bool inside=false;
    std::cout << "*********************************************************************Starting point of list**********************************************" << std::endl;
	for (std::list<Entity381 *>::const_iterator it = entities.begin(); it != entities.end(); ++it)
    {
		n++;
		if((*it)->isSelected)
        {
			inside=true;
			(*it)->isSelected = false;
			it++;
			if(it == entities.end())
            {
				std::cout << "End point of list" << std::endl;
				selectedEntity = *(entities.begin());
			} else
			 {
				selectedEntity = *it;
				std::cout << "End of ents" << std::endl;
             }
			selectedEntity->isSelected = true;
			break;
		  }
         if(n==5 && inside==false)
         {
             selectedEntity = *(entities.begin());
		     selectedEntity->isSelected = true;
		     std::cout << "#################################################################First time Selected##################################################" << std::endl;

         }

	}


}

