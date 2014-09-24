#ifndef __MyCppGame__GameHeroObj__
#define __MyCppGame__GameHeroObj__
#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "extensions/cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class GameHeroObj : public Node
{
private:
    Sprite * bodysp;
    int m_state;
public:
    bool init();
    static GameHeroObj *create();
    void setPosition(Point p);
    const Point & getPosition();
    void setState(int state);
    void actionEnd(cocos2d::Ref* pSender);
    void update(float time);
    void jump();
    void kick();
};

#endif
