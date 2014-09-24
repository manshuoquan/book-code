//
//  GameAboutScene.cpp
//  example12-1
//
//  Created by shuoquan man on 12-10-14.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "GameAboutScene.h"
#include "GameMenuScene.h"

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
    
    Sprite* bg = Sprite::create("back_1.png");
    bg->setPosition(Point(size.width/2, size.height/2) );
    this->addChild(bg, 0,0);
    
    Sprite*kuang = Sprite::create("tb.png");
    kuang->setRotation(90);
    kuang->setPosition(Point(size.width/2, size.height/2));
    this->addChild(kuang,2,2);
    char inf[256];
    sprintf(inf,"name:loli run\n\nprogram:shuoquan man\n\nart design:zuyi li\n\ncompany:hz books\n\n    powered by cocos2D-x");
    LabelTTF * myjineng = LabelTTF::create(inf,"Marker Felt",40,Size(400,400),TextHAlignment::LEFT);
    myjineng->setAnchorPoint(Point(0,1));
    myjineng->setColor(Color3B(0,0,0));
    myjineng->setPosition(Point(200,500));
    this->addChild(myjineng);
    
    Sprite*abouttitle = Sprite::create("about.png");
    abouttitle->setPosition(Point(size.width/2, size.height - 20));
    this->addChild(abouttitle,3,3);
    
    MenuItemImage *back = MenuItemImage::create("backA.png","backB.png",CC_CALLBACK_1(GameAbout::menuBackCallback,this));
    back->setPosition(Point(size.width - 20,size.height - 20));
    back->setEnabled(false);
    Menu* mainmenu = Menu::create(back,NULL);
    mainmenu->setPosition(Point(0,0));
    this->addChild(mainmenu,3,4);
    return true;
}
void GameAbout::menuBackCallback(Ref* pSender){
    Director::getInstance()->setDepthTest(true);
    Director::getInstance()->replaceScene(CCTransitionPageTurn::create(0.5,GameMenu::scene(), true));
}
void GameAbout::onEnterTransitionDidFinish()
{
    CCLayer::onEnterTransitionDidFinish();
    Director::getInstance()->setDepthTest(false);
}

void GameAbout::onExitTransitionDidStart()
{
    CCLayer::onExitTransitionDidStart();
}
void GameAbout::onExit(){
    CCLayer::onExit();
}
void GameAbout::onEnter(){
    CCLayer::onEnter();
   
    Node* mainmenu = this->getChildByTag(4);
    auto temp = mainmenu->getChildren();
    ((MenuItemImage *)temp.at(0))->setEnabled(true);
}