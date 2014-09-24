#include "GameResult.h"
#include "GameMainMenu.h"
#include "GameMain.h"
#include "GameAbout.h"
Scene* GameResult::scene(int result)
{
    Scene *scene = Scene::create();
    
    GameResult *layer = GameResult::create();
    
    layer->setResult(result);
    
    scene->addChild(layer);
    
    return scene;
}
bool GameResult::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size size = Director::getInstance()->getVisibleSize();
    //
    Sprite* bg = Sprite::create("bg_jiesuan.png");
    bg->setPosition(Point(size.width/2, size.height/2));
    this->addChild(bg,0,0);
    
    //
    Button* startbtn = Button::create();
    startbtn->setTouchEnabled(true);
    startbtn->loadTextures("nextbtn1.png", "nextbtn2.png", "");
    startbtn->setPosition(Point(size.width/2,270));
    startbtn->addTouchEventListener(this, toucheventselector(GameResult::menuNextCallback));
    this->addChild(startbtn,1,1);
    Button* continuebtn = Button::create();
    continuebtn->setTouchEnabled(true);
    continuebtn->loadTextures("trybtn1.png", "", "");
    continuebtn->setPosition(Point(size.width/2,160));
    continuebtn->addTouchEventListener(this, toucheventselector(GameResult::menuContinueCallback));
    this->addChild(continuebtn,1,2);
    Button* aboutbtn = Button::create();
    aboutbtn->setTouchEnabled(true);
    aboutbtn->loadTextures("quitbtn1.png", "quitbtn2.png", "");
    aboutbtn->setPosition(Point(size.width / 2,50));
    aboutbtn->addTouchEventListener(this, toucheventselector(GameResult::menuQuitCallback));
    this->addChild(aboutbtn,1,2);
    
    Layer * titleNode = Layer::create();
    titleNode->ignoreAnchorPointForPosition(false);
    titleNode->setContentSize(Size(400,200));
    titleNode->setPosition(Point(size.width / 2,size.height / 4 * 3));
    this->addChild(titleNode,1,5);
    Sprite *title = Sprite::create("gameover.png");
    title->setPosition(Point(200,200));
    titleNode->addChild(title,0,1);
    //
    Sprite *iconLeft = Sprite::create("flag_1.png");
    iconLeft->setScale(2);
    iconLeft->setPosition(Point(size.width / 4 - 100,350));
    this->addChild(iconLeft,1,6);
    
    Sprite *iconRight = Sprite::create("flag_2.png");
    iconRight->setScale(2);
    iconRight->setPosition(Point(size.width / 4 * 3 + 100,350));
    this->addChild(iconRight,1,7);
    
    return true;
}
void GameResult::setResult(int result){
    //
    Size size = Director::getInstance()->getVisibleSize();
    Sprite *resultLeft = Sprite::create("win.png");
    this->addChild(resultLeft,1,8);
    
    Sprite *resultRight = Sprite::create("lose.png");
    this->addChild(resultRight,1,9);
    if(result == 0){
        resultLeft->setPosition(Point(size.width / 4 - 100,500));
        resultRight->setPosition(Point(size.width / 4 * 3 + 100,500));
    }else{
        resultLeft->setPosition(Point(size.width / 4 * 3 + 100,500));
        resultRight->setPosition(Point(size.width / 4 - 100,500));
    }
}
void GameResult::onEnter(){
    CCLayer::onEnter();
}
void GameResult::onExit(){
    CCLayer::onExit();
}
void GameResult::menuNextCallback(Ref *pSender, TouchEventType type)
{
    if(type == TOUCH_EVENT_ENDED){
        Director::getInstance()->setDepthTest(true);
        Director::getInstance()->replaceScene(TransitionPageTurn::create(0.5,GameMain::scene(), false));
    }
}
void GameResult::menuContinueCallback(Ref *pSender, TouchEventType type)
{
    if(type == TOUCH_EVENT_ENDED){
        Director::getInstance()->setDepthTest(true);
        Director::getInstance()->replaceScene(TransitionPageTurn::create(0.5,GameMain::scene(), false));
    }
}
void GameResult::menuQuitCallback(Ref *pSender, TouchEventType type)
{
    if(type == TOUCH_EVENT_ENDED){
        Director::getInstance()->setDepthTest(true);
        Director::getInstance()->replaceScene(TransitionPageTurn::create(0.5,GameMainMenu::scene(), false));
    }
}
void GameResult::onEnterTransitionDidFinish()
{
    Layer::onEnterTransitionDidFinish();
}

void GameResult::onExitTransitionDidStart()
{
    Layer::onExitTransitionDidStart();
}