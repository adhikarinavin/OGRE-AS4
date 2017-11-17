#ifndef GFXMGR_H
#define GFXMGR_H

#include "mgr.h"
#include "engine.h"
#include <OgreRoot.h>
#include <OgreSceneManager.h>
#include <OgreCamera.h>
#include <SdkTrays.h>
class Engine;

//Initialize ogre graphics and camera
class GfxMgr : public Mgr {

private:
    Ogre::String mResourcesCfg;
    Ogre::String mPluginsCfg;

public:
    Ogre::Root *mRoot;
    Ogre::RenderWindow *mWindow;
    Ogre::Camera *mCamera;
    Ogre::SceneManager *mSceneMgr;
    Ogre::OverlaySystem *mOverlaySystem;
    Ogre::RaySceneQuery* mRaySceneQuery;

    GfxMgr(Engine *eng);

    ~GfxMgr();

    virtual void init();

    //calls renderoneframe
    virtual void tick(float dt);

    virtual void loadLevel();

    virtual void stop();


};

#endif //GFXMGR_H
