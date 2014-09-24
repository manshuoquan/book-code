//
//  GameObjMap.h
//  example12-1
//
//  Created by shuoquan man on 12-10-21.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef example16_1_GameObjMap_h
#define example16_1_GameObjMap_h
#include "cocos2d.h"
using namespace cocos2d;

class GameObjMap : public Node
{
public:
    GameObjMap(void);
    short state;
    virtual ~GameObjMap(void);
    virtual void onEnter();
    virtual void onExit();
    void bg1change(cocos2d::Ref* pSender);
    void bg2change(cocos2d::Ref* pSender);
    Array * stars1;
    Array * stars2;
};

#endif
