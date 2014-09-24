#ifndef __MyCppGame__GameMainMenu__
#define __MyCppGame__GameMainMenu__
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;
using namespace CocosDenshion;
class GameMainMenu : public cocos2d::Layer
{
private:
    Sprite* m_soundflag;
public:
    bool issound;
    
    virtual bool init();
    
    virtual void onEnter();
    
    virtual void onExit();
    
    static cocos2d::Scene* scene();
    
    void menuNewGameCallback(Ref *pSender, TouchEventType type);
    
    void menuContinueCallback(Ref *pSender, TouchEventType type);
    
    void menuAboutCallback(Ref *pSender, TouchEventType type);
    
    void menuSoundCallback(Ref *pSender, TouchEventType type);
    
    CREATE_FUNC(GameMainMenu);
    
    void onEnterTransitionDidFinish();
    
    void onExitTransitionDidStart();
};

#endif