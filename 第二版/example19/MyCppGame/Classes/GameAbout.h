#ifndef __MyCppGame__GameAbout__
#define __MyCppGame__GameAbout__
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;
using namespace CocosDenshion;
class GameAbout : public Layer
{
public:
    
    virtual bool init();
    
    virtual void onEnter();
    
    virtual void onExit();
    
    static Scene* scene();
    
    void menuBackCallback(Ref *pSender, TouchEventType type);
    
    CREATE_FUNC(GameAbout);
    
    void onEnterTransitionDidFinish();
    void onExitTransitionDidStart();
};

#endif
