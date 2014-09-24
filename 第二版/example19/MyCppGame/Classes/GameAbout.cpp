#include "GameAbout.h"
#include "GameMainMenu.h"

using namespace cocos2d;

Scene* GameAbout::scene()
{
    Scene *scene = Scene::create();
    
    GameAbout *layer = GameAbout::create();
    
    scene->addChild(layer);
    
    return scene;
}
bool GameAbout::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size size = Director::getInstance()->getVisibleSize();
    
    Sprite* bg = Sprite::create("bgmain.png");
    bg->setPosition(Point(size.width/2, size.height/2) );
    this->addChild(bg, 0,0);
    //
    Sprite*kuang = Sprite::create("bg_p.png");
    kuang->setRotation(90);
    kuang->setPosition(Point(size.width/2, size.height/2));
    this->addChild(kuang,2,2);
    char inf[256];
    sprintf(inf,"name:mini worldcup\n\nprogram:shuoquan man\n\nart design:peng xu\n\ncompany:hz books\n\n    powered by cocos2D-X");
    LabelTTF * myjineng = LabelTTF::create(inf,"Marker Felt",40,Size(400,400),TextHAlignment::LEFT);
    myjineng->setAnchorPoint(Point(0,1));
    myjineng->setColor(Color3B(0,0,0));
    myjineng->setPosition(Point(300,500));
    this->addChild(myjineng);
    
    Button* backbtn = Button::create();
    backbtn->setTouchEnabled(true);
    backbtn->loadTextures("contral1.png","contral2.png", "");
    backbtn->setPosition(Point(size.width - 100,size.height - 100));
    backbtn->addTouchEventListener(this, toucheventselector(GameAbout::menuBackCallback));
    this->addChild(backbtn,2,3);
    
    return true;
}
void GameAbout::menuBackCallback(Ref *pSender, TouchEventType type){
    Director::getInstance()->setDepthTest(true);
    Director::getInstance()->replaceScene(CCTransitionPageTurn::create(0.5,GameMainMenu::scene(), true));
}
void GameAbout::onEnterTransitionDidFinish()
{
    Layer::onEnterTransitionDidFinish();
    Director::getInstance()->setDepthTest(false);
}

void GameAbout::onExitTransitionDidStart()
{
    Layer::onExitTransitionDidStart();
}
void GameAbout::onExit(){
    Layer::onExit();
}
void GameAbout::onEnter(){
    Layer::onEnter();
}
