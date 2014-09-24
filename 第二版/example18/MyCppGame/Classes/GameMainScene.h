//
//  GameMainScene.h
//  example12-1
//
//  Created by shuoquan man on 12-10-21.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef example16_1_GameMainScene_h
#define example16_1_GameMainScene_h
#include "cocos2d.h"
#include "GameObjHero.h"
#include "GameObjMap.h"
#include "GameMark.h"
using namespace cocos2d;
class GameMain : public cocos2d::Layer
{
public:
    
    GameObjHero* hero;
    
    virtual bool init();
    bool isover;
    virtual void onEnter();
    
    virtual void onExit();
    
    void isherodrop();
    void setover();
    GameObjMap * map;
    GameMark *gamemark;
    Sprite *gameover;
    static cocos2d::Scene* scene();
    
    void menuBackCallback(cocos2d::Ref* pSender);
    
    CREATE_FUNC(GameMain);
    
    void update(float time);
    
    void onEnterTransitionDidFinish();
    void onExitTransitionDidStart();
    
    bool isCollion(Point p1,Point p2,int w1,int h1,int w2,int h2);
};


#endif
