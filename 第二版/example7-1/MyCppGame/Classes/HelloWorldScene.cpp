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


bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);
    
    auto label = LabelTTF::create("Hello World", "Arial", 24);
    label->setPosition(Point(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));
    this->addChild(label, 1);
    auto sprite = Sprite::create("HelloWorld.png");
    sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(sprite, 0);
    
    
    hero = Sprite::create("grossini.png");
    hero->setPosition( Point(visibleSize.width/2, visibleSize.height/2) );
    this->addChild(hero, 0);
    
    auto _touchListener = EventListenerTouchOneByOne::create();
    _touchListener->setSwallowTouches(false);
    
    _touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::touchBegan, this);
    _touchListener->onTouchMoved = CC_CALLBACK_2(HelloWorld::touchMoved, this);
    _touchListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::touchEnded, this);
    _touchListener->onTouchCancelled = CC_CALLBACK_2(HelloWorld::touchEnded, this);
    
    _eventDispatcher->addEventListenerWithFixedPriority(_touchListener, -129);
    return true;
}
bool HelloWorld::touchBegan(Touch* touch, Event* event)
{
    Point heropos = hero->getPosition();
    Point location = touch->getLocation();
    
    if(location.x > heropos.x - 42.5 && location.x < heropos.x + 42.5 &&
       location.y > heropos.y - 60.5 && location.y < heropos.y + 60.5){
        isControl = true;
        deltax = location.x - heropos.x;
        deltay = location.y - heropos.y;
    }
    return true;
}

void HelloWorld::touchMoved(Touch* touch, Event* event)
{
    if(isControl){
        Point location = touch->getLocation();
        
        float x = location.x - deltax;
        float y = location.y - deltay;
        
        hero->setPosition(Point(x,y));
    }
}

void HelloWorld::touchEnded(Touch* touch, Event* event)
{
    isControl = false;
}

void HelloWorld::touchCancelled(Touch* touch,Event* event)
{
    isControl = false;
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
