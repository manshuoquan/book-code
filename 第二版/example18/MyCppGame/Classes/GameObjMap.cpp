//
//  GameObjMap.cpp
//  example12-1
//
//  Created by shuoquan man on 12-10-21.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "GameObjMap.h"
#include "GameConst.h"
#include "GameObjStar.h"

GameObjMap::GameObjMap(){
    
}

GameObjMap::~GameObjMap(){
    
}
void GameObjMap::bg1change(cocos2d::Ref* pSender){
    Sprite * bg = (Sprite *)this->getChildByTag(0);
    bg->setPosition(Point(960,320));
    bg->runAction(Sequence::create(MoveBy::create(20,Point(-1920,0)),
                                   CallFuncN::create(CC_CALLBACK_1(GameObjMap::bg1change,this)),
                                   NULL));
    for(int i = 0;i < 5;i ++){
        ((GameObjStar *)stars1->getObjectAtIndex(i))->set_visable(true);
    }
}
void GameObjMap::bg2change(cocos2d::Ref* pSender){
    Sprite * bg = (Sprite *)this->getChildByTag(1);
    bg->setPosition(Point(960,320));
    bg->runAction(Sequence::create(MoveBy::create(20,Point(-1920,0)),
                                   CallFuncN::create(CC_CALLBACK_1(GameObjMap::bg2change,this)),
                                   NULL));
    for(int i = 0;i < 5;i ++){
        ((GameObjStar *)stars2->getObjectAtIndex(i))->set_visable(true);
    }
}
void GameObjMap::onEnter(){
    CCNode::onEnter();
    Size size = Director::getInstance()->getVisibleSize();
    this->setContentSize(Size(960,320));
    
    Sprite* bg1 = Sprite::create("back_1.png");
    //bg1->setScale(0.5);
    bg1->setAnchorPoint(Point(0,1));
    bg1->setPosition(Point(0, size.height / 2) );
    this->addChild(bg1,0,0);
    Sprite* bgdi1 = Sprite::create("back_5.png");
    bgdi1->setAnchorPoint(Point(0,0));
    bgdi1->setPosition(Point(0,-124) );
    bg1->addChild(bgdi1,1);
    Sprite* bg2 = Sprite::create("back_1.png");
    //bg2->setScale(0.5);
    bg2->setAnchorPoint(Point(0,1));
    bg2->setPosition(Point(size.width, size.height / 2) );
    this->addChild(bg2,0,1);
    Sprite* bgdi2 = Sprite::create("back_5.png");
    bgdi2->setAnchorPoint(Point(0,0));
    bgdi2->setPosition(Point(0,-124) );
    bg2->addChild(bgdi2,1);
    bg1->runAction(CCSequence::create(MoveBy::create(10,Point(-960,0)),
                                      CallFuncN::create(CC_CALLBACK_1(GameObjMap::bg1change,this)),
                                      NULL));
    bg2->runAction(CCSequence::create(MoveBy::create(20,Point(-1920,0)),
                                      CallFuncN::create(CC_CALLBACK_1(GameObjMap::bg2change,this)),
                                      NULL));
    stars1 = __Array::create();
    stars2 = __Array::create();
    for(int i = 0;i < 5;i ++){
        GameObjStar* obj = new GameObjStar();
        obj->setPosition(Point(172 + 192 * i,350));
        stars1->addObject(obj);
        bg1->addChild(obj,3);
        obj = new GameObjStar();
        obj->setPosition(Point(172 + 192 * i,350));
        stars2->addObject(obj);
        bg2->addChild(obj,3);
    }
    stars1->retain();
    stars2->retain();
    
    for(int i = 0;i < 7;i ++){
        Sprite* roaddi;
        Sprite* plant;
        if(bg1shu[i] != -1){
           Sprite* road;
           switch(bg1shu[i]){
            case 0:
                plant = Sprite::create("back_2.png");
                plant->setAnchorPoint(Point(0.5,0));
                plant->setPosition( Point(128 * i + 64,117) );
                bg1->addChild(plant,1);
                road = Sprite::create("road_2.png");
                road->setAnchorPoint(Point(0,0));
                road->setPosition( Point(128 * i,0) );
                roaddi = Sprite::create("road_3.png");
                roaddi->setAnchorPoint(Point(0,1));
                roaddi->setPosition( Point(128 * i,0) );
                bg1->addChild(roaddi,1);
                break;
            case 1:
                road = Sprite::create("road_1.png");
                road->setAnchorPoint(Point(0,0));
                road->setPosition( Point(26 + 128 * i,0) );
                roaddi = Sprite::create("road_4.png");
                
                roaddi->setAnchorPoint(Point(0,1));
                roaddi->setPosition( Point(26 + 128 * i,0) );
                bg1->addChild(roaddi,1);
                break;
            case 2:
                plant = Sprite::create("enemy.png");
                plant->setAnchorPoint(Point(0.5,0));
                plant->setPosition( Point(128 * i + 64,112) );
                bg1->addChild(plant,1);
                road = Sprite::create("road_1.png");
                road->setFlippedX(true);
                road->setAnchorPoint(Point(0,0));
                road->setPosition( Point(128 * i,0) );
                roaddi = CCSprite::create("road_4.png");
                roaddi->setFlippedX(true);
                roaddi->setAnchorPoint(Point(0,1));
                roaddi->setPosition( Point(128 * i,0) );
                bg1->addChild(roaddi,1);
                break;
            case 3:
                road = Sprite::create("road_5.png");
                road->setAnchorPoint(Point(0,0));
                road->setPosition( Point(128 * i,0) );
                break;
            
           }
           bg1->addChild(road,1);
        }
        if(bg2shu[i] != -1){
           Sprite* road1;
           switch(bg2shu[i]){
            case 0:
                road1 = Sprite::create("road_2.png");
                road1->setAnchorPoint(Point(0,0));
                road1->setPosition( Point(128 * i,0) );
                roaddi = Sprite::create("road_3.png");
                
                roaddi->setAnchorPoint(Point(0,1));
                roaddi->setPosition( Point(128 * i,0) );
                bg2->addChild(roaddi,1);
                break;
            case 1:
                plant = Sprite::create("back_3.png");
                plant->setAnchorPoint(Point(0.5,0));
                plant->setPosition( Point(128 * i + 128,117) );
                bg2->addChild(plant,1);
                road1 = Sprite::create("road_1.png");
                road1->setAnchorPoint(Point(0,0));
                road1->setPosition( Point(26 + 128 * i,0) );
                roaddi = Sprite::create("road_4.png");
                
                roaddi->setAnchorPoint(Point(0,1));
                roaddi->setPosition( Point(26 + 128 * i,0) );
                bg2->addChild(roaddi,1);
                break;
            case 2:
                road1 = Sprite::create("road_1.png");
                road1->setFlippedX(true);
                road1->setAnchorPoint(Point(0,0));
                road1->setPosition( Point(128 * i,0) );
                roaddi = Sprite::create("road_4.png");
                roaddi->setFlippedX(true);
                roaddi->setAnchorPoint(Point(0,1));
                roaddi->setPosition( Point(128 * i,0) );
                bg2->addChild(roaddi,1);
                break;
            case 3:
                road1 = Sprite::create("road_5.png");
                road1->setAnchorPoint(Point(0,0));
                road1->setPosition( Point(128 * i,0) );
                break;
                
            }
            bg2->addChild(road1,1);
        }
    }
    state = 0;
}

void GameObjMap::onExit(){
    CCNode::onExit();
}