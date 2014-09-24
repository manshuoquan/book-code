#ifndef __MyCppGame__GameMain__
#define __MyCppGame__GameMain__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include "Box2D/Box2D.h"
#include "GameHeroObj.h"
#include "GameEnemyObj.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;
using namespace CocosDenshion;
#define PTM_RATIO 32
class GameMain : public Layer
{
private:
    int m_leftvalue;
    int m_rightvalue;
    Sprite * ball;
    Sprite * scoreleft;
    Sprite * scoreright;
    GameHeroObj * hero;
    GameEnemyObj * enemy;
    b2World* world;
    PhysicsWorld* m_world;
    bool m_ispause;
    bool onContactBegin(EventCustom* event, const PhysicsContact& contact);
public:
    void setPause(bool ispause);//
    void setScore(int score,int side);//
    void startBall();//
    void startGame();//
    void update(float time);
    virtual bool init();
    void initUi();//
    void initGame();
    void initPhysics();
    virtual void onEnter();
    void setPhyWorld(PhysicsWorld* world){m_world = world;}
    static Scene* scene();
    virtual void onExit();
    //
    void menuPauseCallback(Ref *pSender, TouchEventType type);
    void menuLeftCallback(Ref *pSender, TouchEventType type);
    void menuRightCallback(Ref *pSender, TouchEventType type);
    void menuJumpCallback(Ref *pSender, TouchEventType type);
    void menuKickCallback(Ref *pSender, TouchEventType type);
    
    CREATE_FUNC(GameMain);
    
    void onEnterTransitionDidFinish();
    void onExitTransitionDidStart();
};

#endif
