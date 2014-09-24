#include "GamePrepare.h"
#include "GameMain.h"
using namespace cocos2d;

bool GamePrepare::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size size = Director::getInstance()->getVisibleSize();
    
    Sprite* bgvs = Sprite::create("bg_vs.png");
    bgvs->setPosition(Point(size.width/2, size.height/2 - 50) );
    this->addChild(bgvs, 0,1);
    //
    Sprite*iconSp1 = Sprite::create("person/p1.png");
    iconSp1->setPosition(Point(size.width/4, size.height/2));
    iconSp1->setScale(5);
    this->addChild(iconSp1,1,2);
    Sprite*iconSp2 = Sprite::create("person/p2.png");
    iconSp2->setPosition(Point(size.width/4 * 3, size.height/2));
    iconSp2->setFlippedX(true);
    iconSp2->setScale(5);
    this->addChild(iconSp2,1,3);
    //
    Sprite* vs_thunder = Sprite::create("vs_thunder.png");
    vs_thunder->setPosition(Point(size.width/2, size.height/2));
    this->addChild(vs_thunder,2,4);
    Sprite* v_sp = Sprite::create("zimu_v.png");
    v_sp->setPosition(Point(size.width/2 - 60, size.height/2 + 50));
    this->addChild(v_sp,2,5);
    Sprite* s_sp = Sprite::create("zimu_s.png");
    s_sp->setPosition(Point(size.width/2 + 100, size.height/2 - 50));
    this->addChild(s_sp,2,6);
    Button* ballbtn = Button::create();
    ballbtn->setTouchEnabled(true);
    ballbtn->loadTextures("vs_ball.png","", "");
    ballbtn->setPosition(Point(size.width/2, size.height/2));
    ballbtn->addTouchEventListener(this, toucheventselector(GamePrepare::menuBackCallback));
    this->addChild(ballbtn,2,7);
    return true;
}
void GamePrepare::menuBackCallback(Ref *pSender, TouchEventType type){
    GameMain * parent = (GameMain *)this->getParent();
    parent->startGame();
    this->removeFromParentAndCleanup(true);
}
void GamePrepare::onEnterTransitionDidFinish()
{
    Layer::onEnterTransitionDidFinish();
    Director::getInstance()->setDepthTest(false);
}

void GamePrepare::onExitTransitionDidStart()
{
    Layer::onExitTransitionDidStart();
}
void GamePrepare::onExit(){
    Layer::onExit();
}
void GamePrepare::onEnter(){
    Layer::onEnter();
}