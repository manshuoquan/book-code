//
//  GameMainScene.cpp
//  example12-1
//
//  Created by shuoquan man on 12-10-21.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "GameMainScene.h"
#include "GameMenuScene.h"
#include "GameObjMap.h"
#include "GameConst.h"
#include "GameObjStar.h"
using namespace cocos2d;

Scene* GameMain::scene()
{
    Scene *scene = Scene::create();
    
    GameMain *layer = GameMain::create();
    
    scene->addChild(layer);
    
    return scene;
}
bool GameMain::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    Size size = Director::getInstance()->getVisibleSize();   
    map = new GameObjMap();
    map->setAnchorPoint(Point(0,1));
    map->setPosition(Point(0,size.height));
    addChild(map,0);
    hero = new GameObjHero();
    hero->setPosition(Point(200,320));
    addChild(hero,1);
    gamemark = new GameMark();
    addChild(gamemark,4);
    gamemark = new GameMark();
    addChild(gamemark,4);
   
    gameover = CCSprite::create("gameover.png");
    gameover->setAnchorPoint(Point(0.5,0.5));
    gameover->setPosition(Point(0,0));
    gameover->setPosition(Point(size.width/2,size.height/2 + 70));
    gameover->setVisible(false);
    addChild(gameover,5);
   
    MenuItemImage *pCloseItem = MenuItemImage::create("back.png","back.png",
                                                       CC_CALLBACK_1(GameMain::menuBackCallback,this));
    pCloseItem->setPosition( Point(size.width/2,size.height/2 - 50) );
    pCloseItem->setScale(0.5);
    Menu* pMenu = Menu::create(pCloseItem, NULL);
    pMenu->setPosition(Point::ZERO);
    this->addChild(pMenu,5,25);
    pMenu->setVisible(false);
    pMenu->setEnabled(false);
    isover = false;
    scheduleUpdate();
    return true;
}
void GameMain::setover(){
    
    Menu* pMenu = (Menu *)this->getChildByTag(25);
    pMenu->setVisible(true);
    pMenu->setEnabled(true);
    gameover->setVisible(true);
    gameover->setOpacity(0);
    pMenu->setOpacity(0);
    pMenu->runAction(FadeIn::create(0.5));
    gameover->runAction(FadeIn::create(0.5));
    isover = true;
}
void GameMain::isherodrop(){
    
    Point p1 = (map->getChildByTag(0))->getPosition();
    Point p2 = (map->getChildByTag(1))->getPosition();    
    int temp;
    if(p1.x <= 200 && (p1.x + 960) >= 200){
        temp = (200 - p1.x) / 128;
        if(bg1shu[temp] == -1){
           hero->setState(2);
        }
    }else{
        temp = (200 - p2.x) / 128;
        if(bg2shu[temp] == -1){
            hero->setState(2);
        } 
    }
}
bool GameMain::isCollion(Point p1,Point p2,int w1,int h1,int w2,int h2){
    if(abs(p1.x - p2.x) < w1 + w2 && abs(p1.y - p2.y) < h1 + h2){
        return true;
    }
    return false;
};
void GameMain::update(float time){
    if(hero->state == 0)
       isherodrop();
    Point p1 = (map->getChildByTag(0))->getPosition();
    Point p2 = (map->getChildByTag(1))->getPosition();
    
    for(int i = 0;i < 5;i ++){
        if(p1.x <= 100 && (p1.x + 480) >= 100){
            GameObjStar *obj = (GameObjStar *)(map->stars1)->getObjectAtIndex(i);
            if(obj->get_visable() && isCollion(Point(100,hero->getPosition().y + 62.5),Point(p1.x + 86 + 96 * i,280),40,35,18.25,17.75)){
                obj->set_visable(false);
                gamemark->addnumber(200);
            }
        }else{
            GameObjStar *obj = (GameObjStar *)(map->stars2)->getObjectAtIndex(i);
            if(obj->get_visable() && isCollion(Point(100,hero->getPosition().y + 62.5),Point(p2.x + 86 + 96 * i,280),40,35,18.25,17.75)){
                obj->set_visable(false);
                gamemark->addnumber(200);
            }
        }
    }
}
void GameMain::menuBackCallback(cocos2d::Ref* pSender){
    Director::getInstance()->setDepthTest(true);
    Director::getInstance()->replaceScene(CCTransitionPageTurn::create(0.5,GameMenu::scene(), true));
}
void GameMain::onEnterTransitionDidFinish()
{
    Layer::onEnterTransitionDidFinish();
    Director::getInstance()->setDepthTest(false);
}

void GameMain::onExitTransitionDidStart()
{
    Layer::onExitTransitionDidStart();
}
void GameMain::onExit(){
    Layer::onExit();
}
void GameMain::onEnter(){
    Layer::onEnter();
}
