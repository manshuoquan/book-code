#ifndef __MyCppGame__GameResult__
#define __MyCppGame__GameResult__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;
using namespace CocosDenshion;
class GameResult : public cocos2d::Layer
{
public:
    virtual bool init();
    
    virtual void onEnter();
    
    virtual void onExit();
    
    static cocos2d::Scene* scene(int result);
    
    void setResult(int result);
    
    void menuNextCallback(Ref *pSender, TouchEventType type);
    
    void menuContinueCallback(Ref *pSender, TouchEventType type);
    
    void menuQuitCallback(Ref *pSender, TouchEventType type);
    
    CREATE_FUNC(GameResult);
    
    void onEnterTransitionDidFinish();
    
    void onExitTransitionDidStart();
};

#endif
