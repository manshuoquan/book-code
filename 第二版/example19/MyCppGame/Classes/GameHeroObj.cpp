#include "GameHeroObj.h"

GameHeroObj *GameHeroObj::create(){
    GameHeroObj *ret = new GameHeroObj();
    if (ret && ret->init())
    {
        ret->autorelease();
        return ret;
    }
    else
    {
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
}
bool GameHeroObj::init(){
    bodysp = Sprite::create("person/p1stand1.png");
    bodysp->setScale(2);
    auto bodysize = bodysp->getContentSize();
    auto body = PhysicsBody::createBox(Size(bodysize.width * 2,bodysize.height * 2),PhysicsMaterial(200,0.8,0.01));
    bodysp->setPhysicsBody(body);
    bodysp->setPosition(Point(0,2));
    this->addChild(bodysp);
    setState(0);
    scheduleUpdate();
    return true;
}
void GameHeroObj::update(float time)
{
    auto p = bodysp->getPosition();
    if(m_state == 1)
        setPosition(Point(p.x + 2,p.y));
    else if(m_state == 2)//
        setPosition(Point(p.x - 2,p.y));
}
void GameHeroObj::jump()
{
    if(m_state < 0)
        return;
    setState(-1);
    bodysp->runAction(Sequence::create(JumpBy::create(1,Point(0,0),100,1),
                                       CallFuncN::create(CC_CALLBACK_1(GameHeroObj::actionEnd,this)),
                                       NULL));
}
void GameHeroObj::kick()
{
    setState(-1);
    auto p = bodysp->getPosition();
    bodysp->runAction(Sequence::create(MoveTo::create(0.1,Point(p.x + 20,p.y)),
                                       CallFuncN::create(CC_CALLBACK_1(GameHeroObj::actionEnd,this)),
                                       NULL));
}
void GameHeroObj::setState(int state)
{
    if(m_state != state){
        m_state = state;
        Animation * animation = Animation::create();
        if(m_state >= 1){
            animation->addSpriteFrameWithFile("person/p1move1.png");
            animation->addSpriteFrameWithFile("person/p1move2.png");
            animation->addSpriteFrameWithFile("person/p1move3.png");
            animation->addSpriteFrameWithFile("person/p1move4.png");
            animation->addSpriteFrameWithFile("person/p1move5.png");
            animation->addSpriteFrameWithFile("person/p1move6.png");
        }else{
            animation->addSpriteFrameWithFile("person/p1stand1.png");
            animation->addSpriteFrameWithFile("person/p1stand2.png");
            animation->addSpriteFrameWithFile("person/p1stand3.png");
            animation->addSpriteFrameWithFile("person/p1stand4.png");
        }
        if (m_state > -2){
            //初始化动画
            animation->setDelayPerUnit(0.1f);
            animation->setRestoreOriginalFrame(true);
            //运行动画
            bodysp->runAction(CCRepeatForever::create(CCAnimate::create(animation)));
        }
    }
}
void GameHeroObj::setPosition(Point p)
{
    bodysp->setPosition(Point(p.x,p.y));
}
const Point & GameHeroObj::getPosition()
{
    return bodysp->getPosition();
}
void GameHeroObj::actionEnd(cocos2d::Ref* pSender)
{
    setState(0);
}