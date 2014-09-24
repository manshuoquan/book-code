#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    void createMapAndShow();    
    void createMapAndGetTile();
    void create45Map();        
    void createMapAndAddChild();
    void createObjectsLayerTest();
    Point convertto2dSimple(float x,float y);
    Point convertto2d(float x,float y);
    void onEnter();
    void repositionSprite(float dt);
    bool onTouchBegan(Touch* touch, Event* event);
    void menuCloseCallback(Object* pSender);
    void createMapAndGetTileProperity();
    CREATE_FUNC(HelloWorld);
    Sprite *m_testSp;
};

#endif // __HELLOWORLD_SCENE_H__
