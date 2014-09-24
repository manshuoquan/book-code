//
//  GameObjHero.cpp
//  example12-1
//
//  Created by shuoquan man on 12-10-14.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//
#include "GameObjHero.h"
#include "GameMainScene.h"
GameObjHero::GameObjHero(void)
{
}

GameObjHero::~GameObjHero(void)
{
}
Rect GameObjHero::rect()
{
    Size s = Size(100,125);
    return Rect(-s.width / 2, -s.height / 2, s.width, s.height);
}
void GameObjHero::onEnter()
{
    Node::onEnter();
    this->setContentSize(Size(85,90));
    Sprite * obj = Sprite::create("s_hurt.png");
    hurt = obj->getTexture();
    obj = CCSprite::create("s_jump.png");
    jump = obj->getTexture();
    mainsprite = CCSprite::create("s_1.png");
    
    Animation * animation = Animation::create();
    animation->addSpriteFrameWithFile("s_1.png");
    animation->addSpriteFrameWithFile("s_2.png");
    animation->addSpriteFrameWithFile("s_3.png");
    animation->addSpriteFrameWithFile("s_4.png");
    animation->addSpriteFrameWithFile("s_5.png");
    animation->addSpriteFrameWithFile("s_6.png");
    animation->setDelayPerUnit(0.1f);
    animation->setRestoreOriginalFrame(true);
    
    mainsprite->runAction(CCRepeatForever::create(CCAnimate::create(animation)));
    state = 0;
    addChild(mainsprite);
    auto _touchListener = EventListenerTouchOneByOne::create();
    _touchListener->setSwallowTouches(false);
    
    _touchListener->onTouchBegan = CC_CALLBACK_2(GameObjHero::ccTouchBegan, this);
    _touchListener->onTouchMoved = CC_CALLBACK_2(GameObjHero::ccTouchMoved, this);
    _touchListener->onTouchEnded = CC_CALLBACK_2(GameObjHero::ccTouchEnded, this);
    
    _eventDispatcher->addEventListenerWithFixedPriority(_touchListener, -129);
}
void GameObjHero::setState(short var){
    if(state == var)
        return;
    state = var;
    switch(state){
        case 1:
            this->stopAllActions();
            mainsprite->stopAllActions();
            mainsprite->setTexture(jump);
            this->runAction(Sequence::create(JumpBy::create(2.5,Point(0,0),100,1),
                                             CallFuncN::create(CC_CALLBACK_1(GameObjHero::jumpend,this)),
                                             NULL));
            break;
        case 2:
            this->stopAllActions();
            mainsprite->stopAllActions();
            mainsprite->setTexture(hurt);
            this->runAction(Sequence::create(Blink::create(3, 10),
                                             CallFuncN::create(CC_CALLBACK_1(GameObjHero::hurtend,this)),
                                             NULL));
            ((GameMain *)this->getParent())->setover();
            break;
        case 0:
            this->stopAllActions();
            mainsprite->stopAllActions();
            Animation * animation = Animation::create();
            animation->addSpriteFrameWithFile("s_1.png");
            animation->addSpriteFrameWithFile("s_2.png");
            animation->addSpriteFrameWithFile("s_3.png");
            animation->addSpriteFrameWithFile("s_4.png");
            animation->addSpriteFrameWithFile("s_5.png");
            animation->addSpriteFrameWithFile("s_6.png");
            animation->setDelayPerUnit(0.1f);
            animation->setRestoreOriginalFrame(true);
            mainsprite->runAction(RepeatForever::create(Animate::create(animation)));
            break;
    }
}
void GameObjHero::jumpend(cocos2d::Ref* pSender){
    setState(0);
}
void GameObjHero::hurtend(cocos2d::Ref* pSender){
    setState(0);
}
void GameObjHero::onExit()
{
    _eventDispatcher->removeAllEventListeners();
    CCNode::onExit();
}    
bool GameObjHero::ccTouchBegan(Touch  *touch, Event  *event)
{
    if(((GameMain *)this->getParent())->isover)
        return false;
    //设置运动状态
    setState(1);
    return true;   
}
void GameObjHero::ccTouchMoved(Touch* touch,Event* event)
{
}
void GameObjHero::ccTouchEnded(Touch* touch,Event* event)
{
}