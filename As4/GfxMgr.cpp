#include "engine.h"
#include <OgreConfigFile.h>
#include <OgreRenderWindow.h>
#include <OgreViewport.h>
#include "OgreFrameListener.h"
#include "OgreWindowEventUtilities.h"


GfxMgr::GfxMgr(Engine *eng) : Mgr(eng) {

}


GfxMgr::~GfxMgr() {

}


void GfxMgr::init() {
    mResourcesCfg = "resources.cfg";
    mPluginsCfg = "plugins.cfg";
    mRoot = new Ogre::Root(mPluginsCfg);
    Ogre::ConfigFile cf;
    cf.load(mResourcesCfg);
    Ogre::String name, locType;
    Ogre::ConfigFile::SectionIterator secIt = cf.getSectionIterator();
    while (secIt.hasMoreElements()) {
        Ogre::ConfigFile::SettingsMultiMap *settings = secIt.getNext();
        Ogre::ConfigFile::SettingsMultiMap::iterator it;
        for (it = settings->begin(); it != settings->end(); ++it) {
            locType = it->first;
            name = it->second;
            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(name, locType);
        }
    }

    if (!(mRoot->restoreConfig() || mRoot->showConfigDialog())) {
        return;
    }

    mWindow = mRoot->initialise(true, "TutorialApplication Render Window");
    mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC);
    mOverlaySystem = new Ogre::OverlaySystem();
	mSceneMgr->addRenderQueueListener(mOverlaySystem);
    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
    mRaySceneQuery = mSceneMgr->createRayQuery(Ogre::Ray());
    mCamera = mSceneMgr->createCamera("MainCam");

    mCamera->setPosition(0, 200, 500);
    mCamera->lookAt(0, 0, 0);
    mCamera->setNearClipDistance(5);

    Ogre::Viewport *vp = mWindow->addViewport(mCamera);

    vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));

    mCamera->setAspectRatio(
            Ogre::Real(vp->getActualWidth()) /
            Ogre::Real(vp->getActualHeight()));
}

void GfxMgr::tick(float dt) {

    Ogre::WindowEventUtilities::messagePump();
    if (mWindow->isClosed()) return;

    if (!mRoot->renderOneFrame()) return;
}

void GfxMgr::loadLevel() {


}

void GfxMgr::stop() {
    delete mRoot;
}
