//
//  GameMark.cpp
//  example12-1
//
//  Created by shuoquan man on 12-10-20.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "GameMark.h"
GameMark::GameMark(void)
{
}

GameMark::~GameMark(void)
{
}
void GameMark::onExit()
{
    Node::onExit();
}
void GameMark::onEnter()
{
    Node::onEnter();
    Size size = Director::getInstance()->getVisibleSize();
    this->setContentSize(size);
    bits = __Array::create();
    
    Sprite *title = Sprite::create("score.png");
    title->setPosition(Point(size.width/2 + 120,size.height - 15));
    addChild(title);
    
    for(int i = 0;i < 5;i ++){
        Sprite * shu = Sprite::create("shu.png");
        ui = shu->getTexture();
        shu->setTextureRect(Rect(234,0,26,31));
        shu->setPosition(Point(size.width - 30 - i * 30,size.height - 15));
        bits->addObject(shu);
        addChild(shu);
    }
    bits->retain();
    mark = 0;
}
void GameMark::addnumber(int var){
    
    mark += var;
    int temp = mark % 10;
    if(temp > 0){
        ((Sprite *)bits->getObjectAtIndex(0))->setTexture(ui);
        ((Sprite *)bits->getObjectAtIndex(0))->setTextureRect(Rect((temp - 1) * 26,0,26,31));
    }else{
        ((Sprite *)bits->getObjectAtIndex(0))->setTexture(ui);
        ((Sprite *)bits->getObjectAtIndex(0))->setTextureRect(Rect(234,0,26,31)); 
    }
    temp = (mark % 100) / 10;
    if(temp > 0){
        ((Sprite *)bits->getObjectAtIndex(0))->setTexture(ui);
        ((Sprite *)bits->getObjectAtIndex(1))->setTextureRect(Rect((temp - 1) * 26,0,26,31));  
 
    }else{
        ((Sprite *)bits->getObjectAtIndex(0))->setTexture(ui);
        ((Sprite *)bits->getObjectAtIndex(1))->setTextureRect(Rect(234,0,26,31));
    }
    temp = (mark % 1000) / 100;
    if(temp > 0){
        ((Sprite *)bits->getObjectAtIndex(0))->setTexture(ui);
        ((Sprite *)bits->getObjectAtIndex(2))->setTextureRect(Rect((temp - 1) * 26,0,26,31));
 
    }else{
        ((Sprite *)bits->getObjectAtIndex(0))->setTexture(ui);
        ((Sprite *)bits->getObjectAtIndex(2))->setTextureRect(Rect(234,0,26,31));
    }
    temp = (mark % 10000) / 1000;
    if(temp > 0){
        ((Sprite *)bits->getObjectAtIndex(0))->setTexture(ui);
        ((Sprite *)bits->getObjectAtIndex(3))->setTextureRect(Rect((temp - 1) * 26,0,26,31));
 
    }else{
        ((Sprite *)bits->getObjectAtIndex(0))->setTexture(ui);
        ((Sprite *)bits->getObjectAtIndex(3))->setTextureRect(Rect(234,0,26,31));
    }
    temp = mark / 10000;
    if(temp > 0){
        ((Sprite *)bits->getObjectAtIndex(0))->setTexture(ui);
        ((Sprite *)bits->getObjectAtIndex(4))->setTextureRect(Rect((temp - 1) * 26,0,26,31));
 
    }else{
        ((Sprite *)bits->getObjectAtIndex(0))->setTexture(ui);
        ((Sprite *)bits->getObjectAtIndex(4))->setTextureRect(Rect(234,0,26,31));
    }
}