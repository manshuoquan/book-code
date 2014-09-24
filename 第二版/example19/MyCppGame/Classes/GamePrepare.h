#ifndef __MyCppGame__GamePrepare__
#define __MyCppGame__GamePrepare__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;
using namespace CocosDenshion;
class GamePrepare : public Layer
{
public:
    
    virtual bool init();
    
    virtual void onEnter();
    
    virtual void onExit();
    
    void menuBackCallback(Ref *pSender, TouchEventType type);
    
    CREATE_FUNC(GamePrepare);
    
    void onEnterTransitionDidFinish();
    void onExitTransitionDidStart();
};

#endif
