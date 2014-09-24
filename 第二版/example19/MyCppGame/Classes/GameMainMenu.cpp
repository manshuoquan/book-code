#include "GameMainMenu.h"
#include "GameMain.h"
#include "GameAbout.h"
#include "GameResult.h"
#include "GamePause.h"
Scene* GameMainMenu::scene()
{
    Scene *scene = Scene::create();
    
    GameMainMenu *layer = GameMainMenu::create();
    
    scene->addChild(layer);
    
    return scene;
}
bool GameMainMenu::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size size = Director::getInstance()->getVisibleSize();

    Sprite* bg = Sprite::create("bgmain.png");
    bg->setPosition(Point(size.width/2, size.height/2));
    this->addChild(bg,0,0);
    
    
    Button* startbtn = Button::create();
    startbtn->setTouchEnabled(true);
    startbtn->loadTextures("startbtn1.png", "startbtn2.png", "");
    startbtn->setPosition(Point(size.width / 2,320));
    startbtn->addTouchEventListener(this, toucheventselector(GameMainMenu::menuNewGameCallback));
    this->addChild(startbtn,1,1);
    Button* continuebtn = Button::create();
    continuebtn->setTouchEnabled(true);
    continuebtn->loadTextures("restartbtn1.png", "restartbtn2.png", "");
    continuebtn->setPosition(Point(size.width / 2,220));
    continuebtn->addTouchEventListener(this, toucheventselector(GameMainMenu::menuContinueCallback));
    this->addChild(continuebtn,1,2);
    Button* aboutbtn = Button::create();
    aboutbtn->setTouchEnabled(true);
    aboutbtn->loadTextures("aboutbtn1.png", "aboutbtn2.png", "");
    aboutbtn->setPosition(Point(size.width / 2,120));
    aboutbtn->addTouchEventListener(this, toucheventselector(GameMainMenu::menuAboutCallback));
    this->addChild(aboutbtn,1,2);
    Button* soundbtn = Button::create();
    soundbtn->setTouchEnabled(true);
    soundbtn->loadTextures("sound.png","", "");
    soundbtn->setPosition(Point(100,600));
    soundbtn->addTouchEventListener(this, toucheventselector(GameMainMenu::menuSoundCallback));
    this->addChild(soundbtn,1,3);
    
    m_soundflag = Sprite::create("x.png");
    m_soundflag->setPosition(Point(100,600));
    this->addChild(m_soundflag,1,4);
    m_soundflag->setVisible(false);
    
    Layer * titleNode = Layer::create();
    titleNode->ignoreAnchorPointForPosition(false);
    titleNode->setContentSize(Size(400,200));
    titleNode->setPosition(Point(size.width / 2,size.height / 4 * 3));
    this->addChild(titleNode,1,5);
    Sprite *cup = Sprite::create("maincup1.png");
    cup->setPosition(Point(200,150));
    titleNode->addChild(cup,0,2);
    Sprite *title = Sprite::create("name.png");
    title->setPosition(Point(200,100));
    titleNode->addChild(title,0,1);
    
    issound = true;
    
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic( "background.mp3" );
    SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5);
    SimpleAudioEngine::getInstance()->playBackgroundMusic("background.mp3", true);
    return true;
}
void GameMainMenu::onEnter(){
    CCLayer::onEnter();
}
void GameMainMenu::onExit(){
    CCLayer::onExit();
}
void GameMainMenu::menuNewGameCallback(Ref *pSender, TouchEventType type)
{
    if(type == TOUCH_EVENT_ENDED){
        Director::getInstance()->setDepthTest(true);
        Director::getInstance()->replaceScene(TransitionPageTurn::create(0.5,GameMain::scene(), false));
    }
}
void GameMainMenu::menuContinueCallback(Ref *pSender, TouchEventType type)
{
    if(type == TOUCH_EVENT_ENDED){
        Director::getInstance()->setDepthTest(true);
        Director::getInstance()->replaceScene(TransitionPageTurn::create(0.5,GameMain::scene(), false));
    }
}
void GameMainMenu::menuAboutCallback(Ref *pSender, TouchEventType type)
{
    if(type == TOUCH_EVENT_ENDED){
        Director::getInstance()->setDepthTest(true);
        Director::getInstance()->replaceScene(TransitionPageTurn::create(0.5,GameAbout::scene(), false));
    }
}
void GameMainMenu::onEnterTransitionDidFinish()
{
    Layer::onEnterTransitionDidFinish();
}

void GameMainMenu::onExitTransitionDidStart()
{
    Layer::onExitTransitionDidStart();
}
void GameMainMenu::menuSoundCallback(Ref *pSender, TouchEventType type)
{
    if(type == TOUCH_EVENT_ENDED){
        
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