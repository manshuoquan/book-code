//
//  GamePause.h
//  MyCppGame
//
//  Created by man shuoquan on 14-4-28.
//
//

#ifndef __MyCppGame__GamePause__
#define __MyCppGame__GamePause__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;
using namespace CocosDenshion;
class GamePause : public cocos2d::Layer
{
private:
    Sprite* m_soundflag;
public:
    bool issound;
    
    virtual bool init();
    
    virtual void onEnter();
    
    virtual void onExit();
    
    void menuNewGameCallback(Ref *pSender, TouchEventType type);
    
    void menuContinueCallback(Ref *pSender, TouchEventType type);
    
    void menuQuitCallback(Ref *pSender, TouchEventType type);
    
    void menuSoundCallback(Ref *pSender, TouchEventType type);
    
    CREATE_FUNC(GamePause);
    
    void onEnterTransitionDidFinish();
    
    void onExitTransitionDidStart();
};

#endif
