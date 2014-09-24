//
//  GameObjStar.cpp
//  example12-1
//
//  Created by shuoquan man on 12-10-21.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//
#include "GameObjStar.h"
void GameObjStar::set_visable(bool var){
    _visable = var;
    this->setVisible(var);
}
bool GameObjStar::get_visable(){
    return _visable;
}
GameObjStar::GameObjStar(){
    
}

GameObjStar::~GameObjStar(){
    
}
void GameObjStar::onEnter(){
    CCNode::onEnter();
    this->setContentSize(Size(73,71));
    Sprite* star = Sprite::create("star.png");
    _visable = true;
    addChild(star,1);
}
void GameObjStar::onExit(){
    CCNode::onExit();
}