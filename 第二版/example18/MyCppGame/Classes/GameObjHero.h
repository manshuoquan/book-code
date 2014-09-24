//
//  GameObjHero.h
//  example12-1
//
//  Created by shuoquan man on 12-10-14.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef example15_1_GameObjHero_h
#define example15_1_GameObjHero_h
#include "cocos2d.h"
using namespace cocos2d;

class GameObjHero : public Node
{
public:
    Sprite *mainsprite;
    Texture2D *hurt;
    Texture2D *jump;
    Point offset;
    short state;
    bool iscontrol;
    GameObjHero(void);
    virtual ~GameObjHero(void);
    void setState(short var);
    Rect rect();
    virtual void onEnter();
    virtual void onExit();
    void jumpend(cocos2d::Ref* pSender);
    void hurtend(cocos2d::Ref* pSender);
    virtual bool ccTouchBegan(Touch* touch,Event* event);
    virtual void ccTouchMoved(Touch* touch,Event* event);
    virtual void ccTouchEnded(Touch* touch,Event* event);
    
};


#endif
