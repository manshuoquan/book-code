#include "MapScene.h"
#include "Astar.h"
#include "AstarItem.h"
#include <math.h>

using namespace cocos2d;

enum 
{
	kTagTileMap = 1,
};
Scene* MapScene::scene()
{
    Scene *scene = Scene::create();
    MapScene *layer = MapScene::create();
    scene->addChild(layer);
    return scene;
}

// on "init" you need to initialize your instance
bool MapScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
	TMXTiledMap *map = TMXTiledMap::create("iso-test-zorder.tmx");
	addChild(map, 0, kTagTileMap);
	Size s = map->getContentSize();
	Size winSize = Director::getInstance()->getVisibleSize();
	map->setPosition(Point(-s.width/2 + winSize.width/2,0));
	m_tamara = CCSprite::create("grossinis_sister1.png");
	map->addChild(m_tamara, map->getChildrenCount() );
	m_tamara->retain();
	int mapWidth = map->getMapSize().width * map->getTileSize().width;
	m_tamara->setPosition(Point( mapWidth/2,112));
	m_tamara->setAnchorPoint(Point(0.5f,0));
	scheduleUpdate();
	vmove = -1;
	hmove = -1;
	stepindex = -1;
	myastar = new Astar();
    auto _touchListener = EventListenerTouchOneByOne::create();
    _touchListener->setSwallowTouches(false);
    
    _touchListener->onTouchBegan = CC_CALLBACK_2(MapScene::touchBegan, this);
    
    _eventDispatcher->addEventListenerWithFixedPriority(_touchListener, -129);
    return true;
}
Point MapScene::convertto2d(float x,float y){
	TMXTiledMap* map = (TMXTiledMap*) getChildByTag(kTagTileMap);
	int mapWidth = map->getMapSize().width * map->getTileSize().width;
	int mapHeight = map->getMapSize().height * map->getTileSize().height;
	double distanse;
	double sin1;
	double sin11;
	double sin22;
	double cos11;
	double cos1;
	int d2x;
	int d2y;
	double mystatic5 = sqrt(5.0);//«Û∏˘∫≈5
	double mystatic = 16 * mystatic5;//–°ÕºøÈ¿‚≥§
	//char mch[256];
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
void MapScene::update(float dt)
{
	Point herop = m_tamara->getPosition();
	if(stepindex >= 1){
	   if(smallstepindex == 0){
		   int ncol = ((AstarItem *)path->getObjectAtIndex(stepindex))->getcol();
		   int nrow = ((AstarItem *)path->getObjectAtIndex(stepindex))->getrow();
		   int pcol = ((AstarItem *)path->getObjectAtIndex(stepindex - 1))->getcol();
		   int prow = ((AstarItem *)path->getObjectAtIndex(stepindex - 1))->getrow();
		   if(pcol == ncol){
			   if(prow > nrow){
			      vmove = 2;
			   }else if(prow < nrow){
                  vmove = 3;
			   }else{
			      vmove = -1;
			   }
		   }else if(prow == nrow){
			   if(pcol > ncol){
			      vmove = 1;
			   }else if(pcol < ncol){
                  vmove = 0;
			   }else{
			      vmove = -1;
			   }
		   }else{
               if(prow < nrow){
                   if(pcol < ncol){
                       vmove = 6;
                   }else if(pcol > ncol){
                       vmove = 5;
                   }else{
                       vmove = -1;
                   }
			   }else if(prow > nrow){
                   if(pcol < ncol){
                       vmove = 4;
                   }else if(pcol > ncol){
                       vmove = 7;
                   }else{
                       vmove = -1;
                   }
			   }else{
                   vmove = -1;
			   }
		   }
	   }
	   if(vmove == 0){
	      herop.x += 1;
	      herop.y -= 0.5;
	   }else if(vmove == 1){
	      herop.x -= 1;
	      herop.y += 0.5;
	   }else if(vmove == 2){
	      herop.x += 1;
	      herop.y += 0.5;
	   }else if(vmove == 3){
	      herop.x -= 1;
	      herop.y -= 0.5;
	   }else if(vmove == 4){
	      herop.x += 2;
	   }else if(vmove == 5){
	      herop.x -= 2;
	   }else if(vmove == 6){
	      herop.y -= 1;
	   }else if(vmove == 7){
	      herop.y += 1;
	   }
	   smallstepindex ++;
	   if(smallstepindex >= 32){
	      smallstepindex = 0;
		  if(stepindex >= stepcount - 1){
		     stepindex = -1;
			 vmove = -1;
             path->release();
		  }else{
		     stepindex ++;
			 vmove = -1;
		  }
	   }
	}
	m_tamara->setPosition(herop);
	TMXTiledMap* map = (TMXTiledMap*) getChildByTag(kTagTileMap);
	Size s = map->getContentSize();
	int mapWidth = map->getMapSize().width * map->getTileSize().width;
	float deltax = herop.x - mapWidth/2;
	float deltay = herop.y - 112;
	Size winSize = Director::getInstance()->getVisibleSize();
    map->setPosition(Point(-s.width/2 + winSize.width/2 - deltax,-deltay));
}
bool MapScene::touchBegan(Touch  *touch, Event  *event)
{
	Point m_tBeginPos = touch->getLocation();    
	TMXTiledMap* map = (TMXTiledMap*) getChildByTag(kTagTileMap);
	Point mapp = map->getPosition();
	Point aimmapindex = convertto2d(m_tBeginPos.x - mapp.x,m_tBeginPos.y - mapp.y);
	if(aimmapindex.x < 0 || aimmapindex.y < 0 || aimmapindex.x >= map->getMapSize().width || aimmapindex.y >= map->getMapSize().height)
	{
		return true;
	}
	Point herop = m_tamara->getPosition();
	Point mapindex = convertto2d(herop.x,herop.y);
	TMXLayer* layer = map->getLayer("grass");
	int tilegid = layer->getTileGIDAt(Point(aimmapindex.x,aimmapindex.y));
	auto tiledic = map->getPropertiesForGID(tilegid);
    int mv = tiledic.asValueMap()["collion"].asInt();
	if(mv == 1){
	   return true;
	}
	path = myastar->findPath(mapindex.x,mapindex.y,aimmapindex.x,aimmapindex.y,map);
    path->retain();
    stepcount = path->count();
	stepindex = 1;
	smallstepindex = 0;
    return true;
}

