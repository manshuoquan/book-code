//
//  GameMenuScene.h
//  example12-1
//
//  Created by shuoquan man on 12-10-13.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef example15_1_GameMenuScene_h
#define example15_1_GameMenuScene_h

#include "cocos2d.h"
using namespace cocos2d;
class GameMenu : public cocos2d::Layer
{
public:
    bool issound;
    
    MenuItemImage *soundItem;
    
    virtual bool init();
    
    virtual void onEnter();
    
    virtual void onExit();
    
    static cocos2d::Scene* scene();
    
    void menuEnter(cocos2d::Ref* pSender);
    
    void menuNewGameCallback(cocos2d::Ref* pSender);
    
    void menuContinueCallback(cocos2d::Ref* pSender);
    
    void menuAboutCallback(cocos2d::Ref* pSender);
    
    void menuSoundCallback(cocos2d::Ref* pSender);
    
    CREATE_FUNC(GameMenu);
    
    void onEnterTransitionDidFinish();
    
    void onExitTransitionDidStart();
};

#endif
