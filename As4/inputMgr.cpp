
#include "inputMgr.h"
#include "engine.h"
#include <OgreFrameListener.h>
#include <OgreWindowEventUtilities.h>
#include "OgreRenderWindow.h"
static int cSpeed=50;
static float rpSpeed=.001;
InputMgr::InputMgr(Engine *eng) : Mgr(eng) {

}

InputMgr::~InputMgr() {

}

void InputMgr::init() {
    Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
    OIS::ParamList pl;
    size_t windowHnd = 0;
    std::ostringstream windowHndStr;
    engine->gfxMgr->mWindow->getCustomAttribute("WINDOW", &windowHnd);
    windowHndStr << windowHnd;
    pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));
    mInputManager = OIS::InputManager::createInputSystem(pl);
    mKeyboard = static_cast<OIS::Keyboard *>(mInputManager->createInputObject(OIS::OISKeyboard, true));
    mMouse = static_cast<OIS::Mouse *>(mInputManager->createInputObject(OIS::OISMouse, true));
    mMouse->setEventCallback(this);
    mKeyboard->setEventCallback(this);
    windowResized(engine->gfxMgr->mWindow);
    Ogre::WindowEventUtilities::addWindowEventListener(engine->gfxMgr->mWindow, this);
    OgreBites::InputContext inputContext;
	inputContext.mMouse = mMouse;
	inputContext.mKeyboard = mKeyboard;
    mTrayMgr = new OgreBites::SdkTrayManager("InterfaceName", engine->gfxMgr->mWindow, inputContext, this);
    engine->gfxMgr->mRoot->addFrameListener(this);
}

void InputMgr::tick(float dt) {
    if (engine->gfxMgr->mWindow->isClosed()) {
        engine->keepRunning = false;
    }
}

void InputMgr::loadLevel() {


}

void InputMgr::stop() {
//Remove ourself as a Window listener
    Ogre::WindowEventUtilities::removeWindowEventListener(engine->gfxMgr->mWindow, this);
    windowClosed(engine->gfxMgr->mWindow);


}

bool InputMgr::frameRenderingQueued(const Ogre::FrameEvent &evt) {

    if (engine->gfxMgr->mWindow->isClosed()) {
        engine->keepRunning = false;
        return false;
    }
    //Need to capture/update each device
    mKeyboard->capture();
    mMouse->capture();

    if (mKeyboard->isKeyDown(OIS::KC_ESCAPE)) {
        engine->keepRunning = false;
        return false;
    }

    if (!processUnbufferedInput(evt))
        return false;


    return true;
}

bool InputMgr::keyPressed(const OIS::KeyEvent &ke) {
    std::cout << "Key Pressed: " << ke.key << std::endl;
    if(ke.key==OIS::KC_LEFT)
    {
        leftAKeyPress=true;
    }
    return true;
}

bool InputMgr::keyReleased(const OIS::KeyEvent &ke) {
     switch (ke.key)
  {
    case OIS::KC_TAB:
       engine->entityMgr->SelectNextEntity();
       break;
    case OIS::KC_LEFT:
       leftAKeyPress=false;
       break;
    case OIS::KC_ESCAPE:
       engine->keepRunning = false;
       break;
    case OIS::KC_SPACE:
       engine->keepRunning = false;
       break;
    default:
       break;
   }
    return true;
}


bool InputMgr::mouseMoved(const OIS::MouseEvent &me) {
    mTrayMgr->showCursor();
    mTrayMgr->injectMouseMove(me);
    return true;
}

bool InputMgr::mousePressed(
        const OIS::MouseEvent &me, OIS::MouseButtonID id) {
    return true;
}

bool InputMgr::mouseReleased(
        const OIS::MouseEvent &me, OIS::MouseButtonID id) {
            // Left mouse button down
              if (id == OIS::MB_Left)
              {
                  mLMouseDown = true;
                  mRMouseDown=false;

              }
              // Right mouse button down
              else if (id == OIS::MB_Right)
              {
                mTrayMgr->hideCursor();
                mRMouseDown = true;
              }
            Ogre::Real screenWidth = Ogre::Root::getSingleton().getAutoCreatedWindow()->getWidth();
            Ogre::Real screenHeight = Ogre::Root::getSingleton().getAutoCreatedWindow()->getHeight();
            Ogre::Real offsetX = me.state.X.abs / screenWidth;
            Ogre::Real offsetY = me.state.Y.abs / screenHeight;
            Ogre::Ray mouseRay = engine->gfxMgr->mCamera->getCameraToViewportRay(offsetX, offsetY);
            engine->gfxMgr->mRaySceneQuery->setRay(mouseRay);
            engine->gfxMgr->mRaySceneQuery->setSortByDistance(true);
            Ogre::RaySceneQueryResult& result = engine->gfxMgr->mRaySceneQuery->execute();
            Ogre::RaySceneQueryResult::iterator it = result.begin();
            mMovableFound = false;
            for ( ; it != result.end(); it++)
            {
               mMovableFound =
               it->movable &&
               it->movable->getName() != "" &&
               it->movable->getName() != "PlayerCam";
              if (mMovableFound)
              {
                   mCurObject = it->movable->getParentSceneNode();
                   break;
              }
            }
            if(mCurObject1!=mCurObject&&mRMouseDown==false)
            {
              for(int i=0;i<5;i++)
              {
                   engine->gameMgr->entity[i]->isSelected=false;
               }
            }
            for(int i=0;i<5;i++)
            {
              if(mLMouseDown && mCurObject==(engine->gameMgr->entity[i]->ogreSceneNode))
              {
                 engine->gameMgr->entity[i]->isSelected=true;
                 mCurObject1=engine->gameMgr->entity[i]->ogreSceneNode;
              }
            }
           mLMouseDown=false;
           for(int i=0;i<5;i++)
           {
             if(mMovableFound && engine->gameMgr->entity[i]->isSelected==true)
             {
               if ((mCurObject->getName()) == "ground")
               {
                 if(mRMouseDown==true)
                 {
                    auto r = mouseRay.intersects(engine->gameMgr->plane);
                    auto mousePoint = mouseRay.getPoint(r.second);
                    //std::cout << "Mouse Click position" <<mousePoint<< std::endl;
                    if (mKeyboard->isKeyDown(OIS::KC_LSHIFT))
                    {
                       engine->gameMgr->entity[i]->a->AddCommand(new MoveTo(engine->gameMgr->entity[i], mousePoint,COMMAND_TYPE::moveTo));
                       // std::cout << "***********Add Command Completed**********" << std::endl;
                    }
                    else
                    {
                        engine->gameMgr->entity[i]->a->SetCommand(new MoveTo(engine->gameMgr->entity[i], mousePoint,COMMAND_TYPE::moveTo));

                    }
                   }
                }
              else if(mRMouseDown==true)
              {
                for(int j=0;j<5;j++)
                {
                  if(mCurObject==engine->gameMgr->entity[j]->ogreSceneNode)
                  {
                     engine->gameMgr->entity[i]->a->SetCommand(new Follow(engine->gameMgr->entity[i],engine->gameMgr->entity[j],COMMAND_TYPE::followEntity));
                     // Follow(Entity381 *ent, Entity381 *targetObj,COMMAND_TYPE ct)
                  }
                }
              }
           }
         }
        return true;
}


bool InputMgr::processUnbufferedInput(const Ogre::FrameEvent &fe) {
    static float rad1=0;
    static float rad2=0;
    static float rad3=0;
    static float rad4=0;
    static float radc1=0;
    static float radc2=0;
    if(leftAKeyPress==true)
    {
        cSpeed=200;
        rpSpeed=.005;
    }
    else if(leftAKeyPress==false)
    {
        cSpeed=50;
        rpSpeed=0.001;
    }
    for(int i=0;i<5;i++)
    {
         if (mKeyboard->isKeyDown(OIS::KC_NUMPAD8))
         {
           if(engine->gameMgr->entity[i]->isSelected)
           {
             if(engine->gameMgr->entity[i]->desiredSpeed<=engine->gameMgr->entity[i]->maxSpeed)
             {
                engine->gameMgr->entity[i]->desiredSpeed+=1;
             }
           }
         }
         if (mKeyboard->isKeyDown(OIS::KC_NUMPAD2))
         {
           if(engine->gameMgr->entity[i]->isSelected)
           {
             if(engine->gameMgr->entity[i]->desiredSpeed<=engine->gameMgr->entity[i]->maxSpeed)
             {
                engine->gameMgr->entity[i]->desiredSpeed-=1;
             }
           }
         }
         if (mKeyboard->isKeyDown(OIS::KC_NUMPAD6))
         {
           if(engine->gameMgr->entity[i]->isSelected)
           {
             engine->gameMgr->entity[i]->desiredHeading +=.01;
           }
         }
         if (mKeyboard->isKeyDown(OIS::KC_NUMPAD4))
         {
           if(engine->gameMgr->entity[i]->isSelected)
           {
             engine->gameMgr->entity[i]->desiredHeading -=.01;
           }
         }
      }
     //Camera Control
    Ogre::Vector3 cdirVec = engine->gfxMgr->mCamera->getPosition();
    if (mKeyboard->isKeyDown(OIS::KC_R))
        cdirVec.y += cSpeed * fe.timeSinceLastFrame;

    if (mKeyboard->isKeyDown(OIS::KC_F))
    {
         if(cdirVec.y>cSpeed)
        {
         cdirVec.y -= cSpeed * fe.timeSinceLastFrame;
        }
    }


    if (mKeyboard->isKeyDown(OIS::KC_S))
        cdirVec.z += cSpeed* fe.timeSinceLastFrame;

    if (mKeyboard->isKeyDown(OIS::KC_W))
        cdirVec.z -= cSpeed * fe.timeSinceLastFrame;
    if (mKeyboard->isKeyDown(OIS::KC_D))
        cdirVec.x += cSpeed * fe.timeSinceLastFrame;

    if (mKeyboard->isKeyDown(OIS::KC_A))
        cdirVec.x -= cSpeed * fe.timeSinceLastFrame;
    if(mKeyboard->isKeyDown(OIS::KC_E))
    {
       rad1+=rpSpeed;
       rad2=-rad1;
       radc2=-rad1;
       engine->gfxMgr->mCamera->setOrientation(Ogre::Quaternion::IDENTITY);
       engine->gfxMgr->mCamera->yaw(Ogre::Radian(-rad1));
       engine->gfxMgr->mCamera->pitch(Ogre::Radian(radc1));


    }
    if(mKeyboard->isKeyDown(OIS::KC_Q))
    {
       rad2+=rpSpeed;
       rad1=-rad2;
       radc2=rad2;
       engine->gfxMgr->mCamera->setOrientation(Ogre::Quaternion::IDENTITY);
       engine->gfxMgr->mCamera->yaw(Ogre::Radian(rad2));
       engine->gfxMgr->mCamera->pitch(Ogre::Radian(radc1));


    }
     if(mKeyboard->isKeyDown(OIS::KC_X))
    {
       rad3+=rpSpeed;
       rad4=-rad3;
       radc1=-rad3;
       if(rad3<.7)
       {
           engine->gfxMgr->mCamera->setOrientation(Ogre::Quaternion::IDENTITY);
           engine->gfxMgr->mCamera->pitch(Ogre::Radian(-rad3));
           engine->gfxMgr->mCamera->yaw(Ogre::Radian(radc2));
       }
    }
    if(mKeyboard->isKeyDown(OIS::KC_Z))
    {
       rad4+=rpSpeed;
       rad3=-rad4;
       radc1=rad4;
       if(rad4<.2)
       {
           engine->gfxMgr->mCamera->setOrientation(Ogre::Quaternion::IDENTITY);
           engine->gfxMgr->mCamera->pitch(Ogre::Radian(rad4));
           engine->gfxMgr->mCamera->yaw(Ogre::Radian(radc2));

       }
    }
    engine->gfxMgr->mCamera->setPosition(cdirVec);

    return true;
}


//Adjust mouse clipping area
void InputMgr::windowResized(Ogre::RenderWindow *rw) {
    unsigned int width, height, depth;
    int left, top;
    rw->getMetrics(width, height, depth, left, top);

    const OIS::MouseState &ms = mMouse->getMouseState();
    ms.width = width;
    ms.height = height;
}

//Unattach OIS before window shutdown (very important under Linux)
void InputMgr::windowClosed(Ogre::RenderWindow *rw) {
    //Only close for window that created OIS (the main window in these demos)
    if (rw == engine->gfxMgr->mWindow) {
        if (mInputManager) {
            mInputManager->destroyInputObject(mMouse);
            mInputManager->destroyInputObject(mKeyboard);

            OIS::InputManager::destroyInputSystem(mInputManager);
            mInputManager = 0;
        }
    }
}
