#include "GameEnemyObj.h"


GameEnemyObj *GameEnemyObj::create(){
    GameEnemyObj *ret = new GameEnemyObj();
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
bool GameEnemyObj::init(){
    bodysp = Sprite::create("person/p2stand1.png");
    bodysp->setScale(2);
    auto bodysize = bodysp->getContentSize();
    auto body = PhysicsBody::createBox(Size(bodysize.width * 2,bodysize.height * 2),PhysicsMaterial(200,0.8,0.01));
    bodysp->setPhysicsBody(body);
    bodysp->setPosition(Point(0,2));
    bodysp->setFlippedX(true);
    this->addChild(bodysp);
    setState(0);
    scheduleUpdate();
    return true;
}
void GameEnemyObj::update(float time)
{
    auto p = bodysp->getPosition();
    if(m_state == 1)
        setPosition(Point(p.x - 2,p.y));
    else if(m_state == 2)
        setPosition(Point(p.x + 2,p.y));
}
void GameEnemyObj::setState(int state)
{
    if(m_state != state){
        m_state = state;
        Animation * animation = Animation::create();
        if(m_state >= 1){
            animation->addSpriteFrameWithFile("person/p2move1.png");
            animation->addSpriteFrameWithFile("person/p2move2.png");
            animation->addSpriteFrameWithFile("person/p2move3.png");
            animation->addSpriteFrameWithFile("person/p2move4.png");
            animation->addSpriteFrameWithFile("person/p2move5.png");
            animation->addSpriteFrameWithFile("person/p2move6.png");
        }else{
            animation->addSpriteFrameWithFile("person/p2stand1.png");
            animation->addSpriteFrameWithFile("person/p2stand2.png");
            animation->addSpriteFrameWithFile("person/p2stand3.png");
            animation->addSpriteFrameWithFile("person/p2stand4.png");
        }
        if (m_state > -2){
           
            animation->setDelayPerUnit(0.1f);
            animation->setRestoreOriginalFrame(true);
            
            bodysp->runAction(CCRepeatForever::create(CCAnimate::create(animation)));
        }
    }
}
const Point & GameEnemyObj::getPosition()
{
    return bodysp->getPosition();
}
void GameEnemyObj::setPosition(Point p)
{
    bodysp->setPosition(Point(p.x,p.y));
}
void GameEnemyObj::actionEnd(cocos2d::Ref* pSender)
{
    setState(0);
}
void GameEnemyObj::jump()
{
    if(m_state < 0)
        return;
    setState(-1);
    bodysp->runAction(Sequence::create(JumpBy::create(1,Point(0,0),100,1),
                                       CallFuncN::create(CC_CALLBACK_1(GameEnemyObj::actionEnd,this)),
                                       NULL));
}
void GameEnemyObj::kick()
{
    setState(-1);
    auto p = bodysp->getPosition();
    bodysp->runAction(Sequence::create(MoveTo::create(0.1,Point(p.x - 20,p.y)),
                                       CallFuncN::create(CC_CALLBACK_1(GameEnemyObj::actionEnd,this)),
                                       NULL));
}