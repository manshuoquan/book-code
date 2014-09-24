#include "GamePause.h"
#include "GameMainMenu.h"
#include "GameMain.h"

bool GamePause::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size size = Director::getInstance()->getVisibleSize();
    //
    Sprite* bg = Sprite::create("bg_p.png");
    bg->setPosition(Point(size.width/2, size.height/2));
    this->addChild(bg,0,0);
    
    //
    Button* startbtn = Button::create();
    startbtn->setTouchEnabled(true);
    startbtn->loadTextures("resumebtn1.png", "resumebtn2.png", "");
    startbtn->setPosition(Point(size.width / 2,320));
    startbtn->addTouchEventListener(this, toucheventselector(GamePause::menuNewGameCallback));
    this->addChild(startbtn,1,1);
    Button* continuebtn = Button::create();
    continuebtn->setTouchEnabled(true);
    continuebtn->loadTextures("restartbtn1.png", "restartbtn2.png", "");
    continuebtn->setPosition(Point(size.width / 2,220));
    continuebtn->addTouchEventListener(this, toucheventselector(GamePause::menuContinueCallback));
    this->addChild(continuebtn,1,2);
    Button* aboutbtn = Button::create();
    aboutbtn->setTouchEnabled(true);
    aboutbtn->loadTextures("quitbtn1.png", "quitbtn2.png", "");
    aboutbtn->setPosition(Point(size.width / 2,120));
    aboutbtn->addTouchEventListener(this, toucheventselector(GamePause::menuQuitCallback));
    this->addChild(aboutbtn,1,2);
    Button* soundbtn = Button::create();
    soundbtn->setTouchEnabled(true);
    soundbtn->loadTextures("sound.png","", "");
    soundbtn->setPosition(Point(100,600));
    soundbtn->addTouchEventListener(this, toucheventselector(GamePause::menuSoundCallback));
    this->addChild(soundbtn,1,3);
    //
    m_soundflag = Sprite::create("x.png");
    m_soundflag->setPosition(Point(100,600));
    this->addChild(m_soundflag,1,4);
    m_soundflag->setVisible(false);
    
    Layer * titleNode = Layer::create();
    titleNode->ignoreAnchorPointForPosition(false);
    titleNode->setContentSize(Size(400,200));
    titleNode->setPosition(Point(size.width / 2,size.height / 4 * 3));
    this->addChild(titleNode,1,5);
    Sprite *title = Sprite::create("pause.png");
    title->setPosition(Point(200,100));
    titleNode->addChild(title,0,1);
    
    issound = true;
    return true;
}
void GamePause::onEnter(){
    CCLayer::onEnter();
}
void GamePause::onExit(){
    CCLayer::onExit();
}
void GamePause::menuNewGameCallback(Ref *pSender, TouchEventType type)
{
    if(type == TOUCH_EVENT_ENDED){
        this->removeFromParentAndCleanup(true);
    }
}
void GamePause::menuContinueCallback(Ref *pSender, TouchEventType type)
{
    if(type == TOUCH_EVENT_ENDED){
        Director::getInstance()->setDepthTest(true);
        Director::getInstance()->replaceScene(TransitionPageTurn::create(0.5,GameMain::scene(), false));
    }
}
void GamePause::menuQuitCallback(Ref *pSender, TouchEventType type)
{
    if(type == TOUCH_EVENT_ENDED){
        Director::getInstance()->setDepthTest(true);
        Director::getInstance()->replaceScene(TransitionPageTurn::create(0.5,GameMainMenu::scene(), false));
    }
}
void GamePause::onEnterTransitionDidFinish()
{
    Layer::onEnterTransitionDidFinish();
}

void GamePause::onExitTransitionDidStart()
{
    Layer::onExitTransitionDidStart();
}
void GamePause::menuSoundCallback(Ref *pSender, TouchEventType type)
{
    if(type == TOUCH_EVENT_ENDED){
        //
        if(! issound){
            m_soundflag->setVisible(false);
            SimpleAudioEngine::getInstance()->playBackgroundMusic("background.mp3", true);
            issound = true;
        }else{
            m_soundflag->setVisible(true);
            SimpleAudioEngine::getInstance()->stopBackgroundMusic();
            issound = false;
        }
    }
}