#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();

    auto layer = HelloWorld::create();

    scene->addChild(layer);

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

    psprite = Sprite::create("HelloWorld.png");

    psprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(psprite, 0);
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2(HelloWorld::touchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(HelloWorld::touchesMoved, this);
    listener->onTouchesEnded = CC_CALLBACK_2(HelloWorld::touchesEnded, this);
    listener->onTouchesCancelled = CC_CALLBACK_2(HelloWorld::touchesCancelled, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    return true;
}

void HelloWorld::touchesBegan(const std::vector<Touch*>& touches, Event  *event)
{
    if(touches.size() >= 2){
        Point mPoint1 = touches.at(0)->getLocation();
        Point mPoint2 = touches.at(1)->getLocation();
        
        distance = sqrt((mPoint1.x - mPoint2.x) * (mPoint1.x - mPoint2.x) + (mPoint1.y - mPoint2.y) * (mPoint1.y - mPoint2.y));
        
        deltax = (mPoint1.x + mPoint2.x)/2 - psprite->getPositionX();
        deltay = (mPoint1.y + mPoint2.y)/2 - psprite->getPositionY();
    }
}

void HelloWorld::touchesMoved(const std::vector<Touch*>& touches, Event  *event)
{
    if(touches.size() >= 2){
        Point mPoint1 = touches.at(0)->getLocation();
        Point mPoint2 = touches.at(1)->getLocation();
        
        float mdistance = sqrt((mPoint1.x - mPoint2.x) * (mPoint1.x - mPoint2.x) + (mPoint1.y - mPoint2.y) * (mPoint1.y - mPoint2.y));
        
        mscale = mdistance / distance * mscale;
        
        distance = mdistance;
        
        psprite->setScale(mscale);
        
        float x = (mPoint1.x + mPoint2.x)/2 - deltax;
        float y = (mPoint1.y + mPoint2.y)/2 - deltax;
        psprite->setPosition(Point(x,y));
        deltax = (mPoint1.x + mPoint2.x)/2 - psprite->getPositionX();
        deltay = (mPoint1.y + mPoint2.y)/2 - psprite->getPositionY();
    }
}

void HelloWorld::touchesEnded(const std::vector<Touch*>& touches, Event  *event)
{
}
void HelloWorld::touchesCancelled(const std::vector<Touch*>& touches, Event  *event)
{
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
