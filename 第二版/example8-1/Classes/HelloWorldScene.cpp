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
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    createObjectsLayerTest();
    
    return true;
}
void HelloWorld::createObjectsLayerTest()
{
    auto map = TMXTiledMap::create("ortho-objects.tmx");
    addChild(map, -1, 0);
    
    Size CC_UNUSED s = map->getContentSize();
    CCLOG("ContentSize: %f, %f", s.width,s.height);
    
    auto group = map->getObjectGroup("Object Group 1");
    auto& objects = group->getObjects();
    
    Value objectsVal = Value(objects);
    CCLOG("%s", objectsVal.getDescription().c_str());
}
void HelloWorld::repositionSprite(float dt)
{
    auto p = m_testSp->getPosition();
    p = CC_POINT_POINTS_TO_PIXELS(p);
    auto map = getChildByTag(1);
    
    int newZ = 4 - (p.y / 48);
    newZ = std::max(newZ,0);
    
    map->reorderChild(m_testSp, newZ);
}

void HelloWorld::createMapAndAddChild()
{
    auto map = TMXTiledMap::create("test-zorder.tmx");
    addChild(map, 0, 1);
    
    auto s = map->getContentSize();
    map->setPosition(Point(-480,0));
    
    m_testSp = Sprite::create("grossinis_sister1.png");
    map->addChild(m_testSp, map->getChildren().size() );
    m_testSp->retain();
    int mapWidth = map->getMapSize().width * map->getTileSize().width;
    m_testSp->setPosition(CC_POINT_PIXELS_TO_POINTS(Point(mapWidth/2,0)));
    m_testSp->setAnchorPoint(Point(0.5f,0));
    
    auto move = MoveBy::create(10, Point(300,250));
    auto back = move->reverse();
    auto seq = Sequence::create(move, back,NULL);
    m_testSp->runAction( RepeatForever::create(seq) );
    
    schedule( schedule_selector(HelloWorld::repositionSprite) );
}

void HelloWorld::createMapAndGetTileProperity()
{
    auto map = TMXTiledMap::create("ortho-objects.tmx");
    addChild(map, 0, 1);
    auto layer = map->getLayer("logic");
    Point playerindex = Point(0,0);
    int tilegid = layer->getTileGIDAt(playerindex);
	if(tilegid > 0){
        log("Properties:%s",map->getPropertiesForGID(tilegid).asValueMap()["collion"].asString().c_str());
    }
}

void HelloWorld::createMapAndShow()
{
    auto map = TMXTiledMap::create("orthogonal-test2.tmx");
    addChild(map, 0, 1);
    
    auto& children = map->getChildren();
    
    for(const auto &obj : children) {
        auto child = static_cast<SpriteBatchNode*>(obj);
        child->getTexture()->setAntiAliasTexParameters();
    }
}

void HelloWorld::createMapAndGetTile()
{
    auto mapnotchange = TMXTiledMap::create("orthogonal-test4.tmx");
    addChild(mapnotchange, 0, 1);
    mapnotchange->setPosition(50,240);
    
    auto map = TMXTiledMap::create("orthogonal-test4.tmx");
    addChild(map, 0, 2);
    map->setPosition(570,240);
    
    SpriteBatchNode* child = nullptr;
    
    auto& children = map->getChildren();
    
    for(const auto &node : children) {
        child = static_cast<SpriteBatchNode*>(node);
        child->getTexture()->setAntiAliasTexParameters();
    }
    
    map->setAnchorPoint(Point(0, 0));
    
    auto layer = map->getLayer("Layer 0");
    auto s = layer->getLayerSize();
    
    Sprite* sprite;
    sprite = layer->getTileAt(Point(0,0));
    sprite->setScale(2);
    sprite = layer->getTileAt(Point(s.width-1,0));
    sprite->setScale(2);
    sprite = layer->getTileAt(Point(0,s.height-1));
    sprite->setScale(2);
    sprite = layer->getTileAt(Point(s.width-1,s.height-1));
    sprite->setScale(2);
}

void HelloWorld::create45Map()
{
    auto *map = TMXTiledMap::create("iso-test-zorder.tmx");
	addChild(map, 0, 1);
}
void HelloWorld::onEnter()
{
    Layer::onEnter();
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}
bool HelloWorld::onTouchBegan(Touch* touch, Event* event)
{

    auto m_tBeginPos = Point(touch->getLocation().x,touch->getLocation().y);
    auto map = static_cast<TMXTiledMap*>( getChildByTag(1));
    Point mapp = map->getPosition();
    Point aimmapindex = convertto2d(m_tBeginPos.x - mapp.x,m_tBeginPos.y - mapp.y);
    if(aimmapindex.x < 0 || aimmapindex.y < 0 || aimmapindex.x >= map->getMapSize().width || aimmapindex.y >= map->getMapSize().height)
    {
        return false;
    }
    TMXLayer* layer = map->layerNamed("grass");
    layer->setTileGID(4,aimmapindex);
    
    return true;
}
Point HelloWorld::convertto2dSimple(float x,float y)
{
    auto map = static_cast<TMXTiledMap*>( getChildByTag(1));
	int mapWidth = map->getMapSize().width * map->getTileSize().width;
	int mapHeight = map->getMapSize().height * map->getTileSize().height;
    double mystatic5 = sqrt(5.0);
    int tileWidthratio = 2;
    int tileHeightratio = 1;
    int deltaX = x - mapWidth/2;
    int deltaY = y - mapHeight;
    int d2x = (tileWidthratio * deltaY + tileHeightratio * deltaX) / (tileWidthratio * tileHeightratio * map->getTileSize().width * mystatic5 / 2) + 13;
    int d2y = (tileWidthratio * deltaY - tileHeightratio * deltaX) / (tileWidthratio * tileHeightratio * map->getTileSize().width * mystatic5 / 2) + 13;
    return Point(d2x,d2y);
}
Point HelloWorld::convertto2d(float x,float y)
{
	auto map = static_cast<TMXTiledMap*>( getChildByTag(1));
	int mapWidth = map->getMapSize().width * map->getTileSize().width;
	int mapHeight = map->getMapSize().height * map->getTileSize().height;
	double distanse,sin1,sin11,sin22,cos11,cos1;
	int d2x,d2y;
	double mystatic5 = sqrt(5.0);
	double mystatic = 16 * mystatic5;
	if(x > mapWidth/2){
        distanse = sqrt((x - mapWidth/2) * (x - mapWidth/2) + (mapHeight - y) * (mapHeight - y));
        sin1 = (mapHeight - y)/distanse;
        cos1 = (x - mapWidth/2)/distanse;
        sin11 = (sin1 * 2 - cos1) / mystatic5;
        cos11 = (sin1 + cos1 * 2) / mystatic5;
        d2y = distanse * 5 / 4 * sin11 / mystatic;
        sin22 = (2 * sin1 + cos1) / mystatic5;
        d2x = distanse * 5 / 4 * sin22 / mystatic;
        return Point(d2x,d2y);
	}else{
        distanse = sqrt((mapWidth/2 - x) * (mapWidth/2 - x) + (mapHeight - y) * (mapHeight - y));
        sin1 = (mapHeight - y)/distanse;
        cos1 = (mapWidth/2 - x)/distanse;
        sin11 = (sin1 * 2 - cos1) / mystatic5;
        cos11 = (sin1 + cos1 * 2) / mystatic5;
        d2x = distanse * 5 / 4 * sin11 / mystatic;
        //sin22 = 4.0 * cos11 / 5 + 3.0 * sin11 / 5;
        sin22 = (2 * sin1 + cos1) / mystatic5;
        d2y = distanse * 5 / 4 * sin22 / mystatic;
        return Point(d2x,d2y);
	}
}
void HelloWorld::menuCloseCallback(Object* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
