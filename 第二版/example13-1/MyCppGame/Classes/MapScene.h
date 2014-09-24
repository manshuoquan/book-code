#ifndef __MAPSCENE_H__
#define __MAPSCENE_H__

#include "cocos2d.h"

#include "SimpleAudioEngine.h"

#include "Astar.h"
#include "AstarItem.h"

using namespace cocos2d;

class MapScene :public Layer
{
private:
	__Array * path;
	int stepindex;
    int stepcount;
	int smallstepindex;
public:
	int vmove;
	int hmove;
	Astar * myastar;
	Sprite*	m_tamara;
	virtual bool init(); 
	void update(float dt);
	static cocos2d::Scene* scene();
	Point convertto2d(float x,float y);
	virtual bool touchBegan(Touch* touch,Event* event);
	CREATE_FUNC(MapScene);
};

#endif
