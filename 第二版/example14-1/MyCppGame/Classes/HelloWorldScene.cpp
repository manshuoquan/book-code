#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    auto sprite = Sprite::create("scene.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    
    auto particleSystem1 = ParticleSystemQuad::create("rainpoint.plist");
    particleSystem1->setPosition(visibleSize.width/2 + origin.x,origin.y + 150);
    this->addChild(particleSystem1);
    
    auto particleSystem = ParticleSystemQuad::create("rain.plist");
    particleSystem->setPosition(visibleSize.width/2 + origin.x,origin.y + visibleSize.height);
    this->addChild(particleSystem);
    
    return true;
}
