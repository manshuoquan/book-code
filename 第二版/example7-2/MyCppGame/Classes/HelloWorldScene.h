#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    void touchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
    void touchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
    void touchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
    void touchesCancelled(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
    cocos2d::Sprite * psprite;
    float distance;
    float deltax;
    float deltay;
    float mscale = 1;
};

#endif // __HELLOWORLD_SCENE_H__
