//
//  GameMenuScene.cpp
//  example12-1
//
//  Created by shuoquan man on 12-10-13.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "GameMenuScene.h"
#include "GameMainScene.h"
#include "GameAboutScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

Scene* GameMenu::scene()
{
    Scene *scene = Scene::create();
    
    GameMenu *layer = GameMenu::create();
    
    scene->addChild(layer);
    
    return scene;
}
bool GameMenu::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size size = Director::getInstance()->getVisibleSize();
    
    Sprite* bg = Sprite::create("MainMenu.png");
    bg->setPosition(Point(size.width/2, size.height/2));
    this->addChild(bg, 0,0);
   
    MenuItemImage *newGameItem = MenuItemImage::create("newgameA.png", "newgameB.png",CC_CALLBACK_1(GameMenu::menuNewGameCallback,this));
    newGameItem->setPosition(Point(size.width / 2 + 40,size.height / 2 - 20));
    newGameItem->setEnabled(false);
    MenuItemImage *continueItem = MenuItemImage::create("continueA.png", "continueB.png",CC_CALLBACK_1(GameMenu::menuContinueCallback,this));
    continueItem->setPosition(Point(size.width / 2 + 40,size.height / 2 - 100));
    continueItem->setEnabled(false);
    MenuItemImage *aboutItem = MenuItemImage::create("aboutA.png", "aboutB.png",CC_CALLBACK_1(GameMenu::menuAboutCallback,this));
    aboutItem->setPosition(Point(size.width / 2 + 40,size.height / 2 - 180));
    aboutItem->setEnabled(false);
    soundItem = MenuItemImage::create("sound-on-A.png", "sound-on-B.png",CC_CALLBACK_1(GameMenu::menuSoundCallback,this));
    soundItem->setEnabled(false);
    soundItem->setPosition(Point(40,40));
    Menu* mainmenu = Menu::create(newGameItem,continueItem,aboutItem,soundItem,NULL);
    mainmenu->setPosition(Point(0,0));
    mainmenu->setEnabled(true);
    this->addChild(mainmenu,1,3);
    issound = true;
    
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic( "background.mp3" );
    SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5);
    SimpleAudioEngine::getInstance()->playBackgroundMusic("background.mp3", true);
    return true;
}
void GameMenu::onEnter(){
    CCLayer::onEnter();
    
    Size size = Director::getInstance()->getWinSize();
    Node* mainmenu = this->getChildByTag(3);
    mainmenu->setOpacity(0);
    mainmenu->runAction(Sequence::create(FadeIn::create(0.5),
                                         CallFuncN::create(CC_CALLBACK_1(GameMenu::menuEnter,this)),
                                         NULL));
}
void GameMenu::menuEnter(cocos2d::Ref* pSender){
    Menu * mainmenu = (Menu *)this->getChildByTag(3);
    mainmenu->setEnabled(true);
    for(auto child:mainmenu->getChildren())
       ((MenuItemImage *)child)->setEnabled(true);
}
void GameMenu::onExit(){
    CCLayer::onExit();
}
void GameMenu::menuNewGameCallback(Ref* pSender)
{
    Director::getInstance()->setDepthTest(true);
    Director::getInstance()->replaceScene(TransitionPageTurn::create(0.5,GameMain::scene(), false));
}
void GameMenu::menuContinueCallback(Ref* pSender)
{
    Director::getInstance()->setDepthTest(true);
    Director::getInstance()->replaceScene(TransitionPageTurn::create(0.5,GameMain::scene(), false));
}
void GameMenu::menuAboutCallback(Ref* pSender)
{
    Director::getInstance()->setDepthTest(true);
    Director::getInstance()->replaceScene(TransitionPageTurn::create(0.5,GameAbout::scene(), false));
}
void GameMenu::onEnterTransitionDidFinish()
{
    Layer::onEnterTransitionDidFinish();
    Director::getInstance()->setDepthTest(false);
    Menu * mainmenu = (Menu *)this->getChildByTag(3);
    mainmenu->setEnabled(true);
}

void GameMenu::onExitTransitionDidStart()
{
    Layer::onExitTransitionDidStart();
}
void GameMenu::menuSoundCallback(Ref* pSender)
{
    
    if(! issound){
        soundItem->setNormalImage(CCSprite::create("sound-on-A.png"));
        soundItem->setDisabledImage(CCSprite::create("sound-on-B.png"));
        SimpleAudioEngine::getInstance()->playBackgroundMusic("background.mp3", true);
       issound = true;
    }else{
        soundItem->setNormalImage(CCSprite::create("sound-off-A.png"));
        soundItem->setDisabledImage(CCSprite::create("sound-off-B.png"));
        SimpleAudioEngine::getInstance()->stopBackgroundMusic();
       issound = false;
    }
}