#include "MapScene.h"
#include <math.h>

using namespace cocos2d;

enum 
{
	kTagTileMap = 1,
};
Scene* MapScene::scene()
{
    // 'scene' is an autorelease object
    Scene *scene = Scene::create();
    
    // 'layer' is an autorelease object
    MapScene *layer = MapScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MapScene::init()
{
	Sprite *bg = Sprite::create("background.png");
	bg->setScale(1.5f);
	addChild(bg, 0);
	TMXTiledMap *map = TMXTiledMap::create("ortho-objects.tmx");
	addChild(map, 0, kTagTileMap);
	Size s = map->getContentSize();
	Size winSize = Director::getInstance()->getVisibleSize();
	map->setPosition(Point(0,0));
	gameplayer = Sprite::create("grossini.png");
	enemy = Sprite::create("SpinningPeas.png");
	map->addChild(gameplayer, map->getChildrenCount());
	map->addChild(enemy, map->getChildrenCount());
	enemy->setPosition(Point(winSize.width/2 + 80,32));
	enemy->setAnchorPoint(Point(0.5f,0));
	gameplayer->setPosition(Point(winSize.width/2,32));
	gameplayer->setAnchorPoint(Point(0.5f,0));
	scheduleUpdate();
	hmove = 0;
	vmove = 0;
	enemymovetick = 0;
	ownsize = Size(40,100);
	othersize = Size(32,32);
	isreduce = false;
    auto _touchListener = EventListenerTouchOneByOne::create();
    _touchListener->setSwallowTouches(false);
    
    _touchListener->onTouchBegan = CC_CALLBACK_2(MapScene::touchBegan, this);
    
    _eventDispatcher->addEventListenerWithFixedPriority(_touchListener, -129);
    return true;
}
void MapScene::enemytick(){
	Point enemypoint = enemy->getPosition();
	if(enemymovetick >= 0 && enemymovetick <= 20){
	   enemymovetick ++;
       enemypoint.x += 2;
	}else if(enemymovetick > 20 && enemymovetick <= 60){
	   enemymovetick ++;
       enemypoint.x -= 2;
	}else if(enemymovetick > 60 && enemymovetick <= 80){
	   enemymovetick ++;
       enemypoint.x += 2;
	}else if(enemymovetick > 80){
	   enemymovetick = 0;
	}
	enemy->setPosition(enemypoint);
}
bool MapScene::iscollision(Sprite *mysprite,Sprite *testsprite)
{
	Point ownp = mysprite->getPosition();
	Point otherp = testsprite->getPosition();
	if(abs(ownp.x - otherp.x) <= ownsize.width/2 + othersize.width/2 
		&& ownp.y - otherp.y <= othersize.height/2
		&& ownp.y - otherp.y >= -1 * ownsize.height/2){
		return true;
	}
	return false;
}
void MapScene::resetreduce(float dt){
	isreduce = false;
}
void MapScene::update(float dt)
{
	playermaphcollision();
	playermapvcollision();
	Point playerpoint = gameplayer->getPosition();
	playerpoint.y += vmove;
    playerpoint.x += 1 * hmove;
	enemytick();
	gameplayer->setPosition(playerpoint);
	if(! isreduce && iscollision(gameplayer,enemy)){
	   ActionInterval*  action = Blink::create(5, 10);
	   gameplayer->runAction(action);
	   schedule(schedule_selector(MapScene::resetreduce), 5.0f);
	   isreduce = true;
	   hmove = 0;
	}
	TMXTiledMap* map = (TMXTiledMap*) getChildByTag(kTagTileMap);
	Size winSize = Director::getInstance()->getVisibleSize();
	int mapWidth = map->getMapSize().width * map->getTileSize().width;
	int mapHeight = map->getMapSize().height * map->getTileSize().height;
	float deltax = playerpoint.x - winSize.width/2;
	float deltay = playerpoint.y - 32;
	if(-deltax > 0){
	   deltax = 0;
	}
	if(-deltax < -mapWidth + winSize.width){
	   deltax = mapWidth - winSize.width;
	}
	if(-deltay > 0){
	   deltay = 0;
	}
	if(-deltay < -mapHeight + winSize.height){
	   deltay = mapHeight - winSize.height;
	}
    map->setPosition(Point(- deltax,-deltay));
}
void MapScene::playermaphcollision(){
	Point playerpoint = gameplayer->getPosition();
	Size palyersize = gameplayer->getContentSize();
	TMXTiledMap* map = (TMXTiledMap*) getChildByTag(kTagTileMap);
	int indexx,indexy;
	TMXLayer* layer = map->getLayer("logic");
	for(int playery = playerpoint.y - palyersize.height;playery <= playerpoint.y;playery ++){
       indexx = (playerpoint.x - palyersize.width / 2) / map->getTileSize().width;
	   indexy = (playerpoint.y) / map->getTileSize().height;
	   Point playerindex = Point(indexx,indexy);
	   int tilegid = layer->getTileGIDAt(playerindex);
	   if(tilegid > 0){
	      auto tiledic = map->getPropertiesForGID(tilegid);
          int mv = tiledic.asValueMap()["collion"].asInt();
	      if(mv == 2){
             hmove = 0;
		     playerpoint.x = (indexx + 1) * map->getTileSize().width + palyersize.width / 2;
		     gameplayer->setPosition(playerpoint);
	      }
		  return;
	   }
	   indexx = (playerpoint.x + palyersize.width / 2 - 1) / map->getTileSize().width;
	   indexy = (playerpoint.y) / map->getTileSize().height;
	   playerindex = Point(indexx,indexy);
	   tilegid = layer->getTileGIDAt(playerindex);
	   if(tilegid > 0){
          auto tiledic = map->getPropertiesForGID(tilegid);
          int mv = tiledic.asValueMap()["collion"].asInt();
	      if(mv == 2){
             hmove = 0;
		     playerpoint.x = (indexx) * map->getTileSize().width - palyersize.width / 2;
		     gameplayer->setPosition(playerpoint);
	      }
		  return;
	   }
	}
}
void MapScene::playermapvcollision(){
	Point playerpoint = gameplayer->getPosition();
	Size palyersize = gameplayer->getContentSize();
	TMXTiledMap* map = (TMXTiledMap*) getChildByTag(kTagTileMap);
	int indexx,indexy;
	TMXLayer* layer = map->getLayer("logic");
	indexx = (playerpoint.x) / map->getTileSize().width;
	indexy = map->getMapSize().height - (playerpoint.y) / map->getTileSize().height;
	Point playerindex = Point(indexx,indexy);
	int tilegid = layer->getTileGIDAt(playerindex);
	if(tilegid > 0){
       auto tiledic = map->getPropertiesForGID(tilegid);
       int mv = tiledic.asValueMap()["collion"].asInt();
	   if(mv == 1){
		  if(vmove < 0){
		     vmove = 0;
			 hmove = 0;
		     playerpoint.y = (map->getMapSize().height - indexy) * map->getTileSize().height;
		     gameplayer->setPosition(playerpoint);
		  }
		  return;
	   }
	}
	vmove -= 0.2;
}
bool MapScene::touchBegan(Touch  *touch, Event  *event)
{

    Point m_tBeginPos = touch->getLocation();
	Point playerpoint = gameplayer->getPosition();
	Size palyersize = gameplayer->getContentSize();
    TMXTiledMap* map = (TMXTiledMap*) getChildByTag(kTagTileMap);
	Point mappoint = map->getPosition();
	if(m_tBeginPos.x < playerpoint.x - palyersize.width / 2 + mappoint.x){
	   hmove = -1;
	}else if(m_tBeginPos.x > playerpoint.x + palyersize.width / 2 + mappoint.x){
		hmove = 1;
	}else{
	   hmove = 0;
	}
	if(m_tBeginPos.y > playerpoint.y + palyersize.height + mappoint.y){
	   vmove = 6;
	}else{
	   vmove = 0;
	}
    return true;
}

