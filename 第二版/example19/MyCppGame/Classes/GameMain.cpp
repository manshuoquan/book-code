#include "GameMain.h"
#include "GamePrepare.h"
#include "GameResult.h"
#include "GamePause.h"
#include "VisibleRect.h"
#include "GameHeroObj.h"
#include "GameEnemyObj.h"
using namespace cocos2d;

Scene* GameMain::scene()
{
    auto scene = Scene::createWithPhysics();
    //scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
	auto body = PhysicsBody::createEdgeBox(Size(visibleSize.width,visibleSize.height - 50), PHYSICSBODY_MATERIAL_DEFAULT, 3);
    auto edgeNode = Node::create();
    edgeNode->setPosition(Point(visibleSize.width/2,visibleSize.height/2 + 25));
	edgeNode->setPhysicsBody(body);
	scene->addChild(edgeNode);
    
    GameMain *layer = GameMain::create();
    scene->addChild(layer);
    
    return scene;
}
bool GameMain::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    initUi();  
    initGame();
    m_ispause = false;
    return true;
}
void GameMain::initUi(){
    Size size = Director::getInstance()->getVisibleSize();
    //
    Sprite* bg = Sprite::create("BG.png");
    bg->setPosition(Point(size.width/2, size.height/2));
    this->addChild(bg, 0,1);
    GamePrepare * coverlayer = GamePrepare::create();
    this->addChild(coverlayer,7,2);
    //
    Sprite *iconLeft = Sprite::create("flag_1.png");
    iconLeft->setPosition(Point(size.width / 2 - 80,600));
    this->addChild(iconLeft,6,6);
    
    Sprite *iconRight = Sprite::create("flag_2.png");
    iconRight->setPosition(Point(size.width / 2 + 80,600));
    this->addChild(iconRight,6,7);
    //
    scoreleft = Sprite::create("0.png");
    scoreleft->setScale(0.5);
    scoreleft->setPosition(Point(size.width / 2 - 80,550));
    this->addChild(scoreleft,6,8);
    
    scoreright = Sprite::create("0.png");
    scoreright->setScale(0.5);
    scoreright->setPosition(Point(size.width / 2 + 80,550));
    this->addChild(scoreright,6,9);
    //
    Sprite * centersp = Sprite::create("maincup1.png");
    centersp->setScale(0.4);
    centersp->setPosition(Point(size.width / 2,550));
    this->addChild(centersp,6,10);
    
    Sprite * leftbar = Sprite::create("skill.png");
    leftbar->setFlippedX(true);
    leftbar->setPosition(Point(size.width / 4 - 50,600));
    this->addChild(leftbar,6,11);
    
    Sprite * rightbar = Sprite::create("skill.png");
    rightbar->setPosition(Point(size.width / 4 * 3 + 50,600));
    this->addChild(rightbar,6,12);
    //
    Button* pausebtn = Button::create();
    pausebtn->setTouchEnabled(true);
    pausebtn->loadTextures("pause1.png","pause2.png", "");
    pausebtn->setPosition(Point(size.width - 50,size.height - 50));
    pausebtn->addTouchEventListener(this, toucheventselector(GameMain::menuPauseCallback));
    this->addChild(pausebtn,6,3);
    
    Button* leftbtn = Button::create();
    leftbtn->setTouchEnabled(true);
    leftbtn->setFlippedX(true);
    leftbtn->loadTextures("contral1.png","contral2.png", "");
    leftbtn->setPosition(Point(80,50));
    leftbtn->addTouchEventListener(this, toucheventselector(GameMain::menuLeftCallback));
    this->addChild(leftbtn,6,4);
    
    Button* rightbtn = Button::create();
    rightbtn->setTouchEnabled(true);
    rightbtn->loadTextures("contral1.png","contral2.png", "");
    rightbtn->setPosition(Point(300,50));
    rightbtn->addTouchEventListener(this, toucheventselector(GameMain::menuRightCallback));
    this->addChild(rightbtn,6,5);
    
    Button* jumpbtn = Button::create();
    jumpbtn->setTouchEnabled(true);
    jumpbtn->loadTextures("jump.png","", "");
    jumpbtn->setPosition(Point(600,50));
    jumpbtn->addTouchEventListener(this, toucheventselector(GameMain::menuJumpCallback));
    this->addChild(jumpbtn,6,4);
    
    Button* kickbtn = Button::create();
    kickbtn->setTouchEnabled(true);
    kickbtn->loadTextures("kick.png","", "");
    kickbtn->setPosition(Point(800,50));
    kickbtn->addTouchEventListener(this, toucheventselector(GameMain::menuKickCallback));
    this->addChild(kickbtn,6,5);
}
void GameMain::initGame(){
    Size size = Director::getInstance()->getVisibleSize();
    //
    Sprite* rdoor = Sprite::create("dooroutside.png");
    rdoor->setPosition(Point(size.width - 50,120));
    this->addChild(rdoor,5,20);
    Sprite* ldoor = Sprite::create("dooroutside.png");
    ldoor->setFlippedX(true);
    ldoor->setPosition(Point(50,120));
    this->addChild(ldoor,5,21);
    Sprite* rdoord = Sprite::create("doorinside.png");
    rdoord->setPosition(Point(size.width - 50,120));
    this->addChild(rdoord,1,22);
    Sprite* ldoord = Sprite::create("doorinside.png");
    ldoord->setFlippedX(true);
    ldoord->setPosition(Point(50,120));
    this->addChild(ldoord,1,23);
    
    m_leftvalue = 0;
    m_rightvalue = 0;
}
void GameMain::setPause(bool ispause){
    m_ispause = ispause;
}
void GameMain::startGame(){
	unscheduleAllSelectors();
    setPause(false);
    Size size = Director::getInstance()->getVisibleSize();
    ball = Sprite::create("vs_ball.png");
	ball->setTag(1);
	auto body = PhysicsBody::createCircle(ball->getContentSize().width / 2,PhysicsMaterial(0.1,1.7,0.01));
    ball->setPhysicsBody(body);
    ball->setPosition(Point(size.width/2,400));
	this->addChild(ball);
    hero = GameHeroObj::create();
    hero->setPosition(Point(200,200));
	this->addChild(hero);
    enemy = GameEnemyObj::create();
    enemy->setPosition(Point(800,200));
	this->addChild(enemy);
	scheduleUpdate();
}
void GameMain::startBall()
{
    Size size = Director::getInstance()->getVisibleSize();
    ball->setPosition(Point(size.width/2,400));
}
void GameMain::setScore(int score,int side)
{
    char temp[256];
    sprintf(temp,"%d.png",score);
    if(side == 0)
    {
      scoreleft->setTexture(temp);
    }
    else
    {
      scoreright->setTexture(temp);
    }
}
void GameMain::update(float time)
{
    if(m_ispause)
        return;
    //
    if(m_leftvalue >= 3){
        Director::getInstance()->replaceScene(GameResult::scene(0));
        return;
    }
    if(m_rightvalue >= 3){
        Director::getInstance()->replaceScene(GameResult::scene(1));
        return;
    }
    Size size = Director::getInstance()->getVisibleSize();
    if (ball == NULL)
        return;
    auto ballpos = ball->getPosition();
	if (ballpos.x < 0 && ballpos.x > size.width &&
       ballpos.y < 0 && ballpos.y > size.height)
    {
        startBall();
        return;
    }
	if (ballpos.x < 70 && ballpos.y > 25 && ballpos.y < 200){
        setScore(++m_leftvalue,0);
        startBall();
        return;
    }
	if (ballpos.x > size.width - 70 && ballpos.y > 25 && ballpos.y < 200){
        setScore(++m_rightvalue,0);
        startBall();
        return;
    }
    auto enemypos = enemy->getPosition();
    if(ballpos.x - enemypos.x > 200){
        enemy->setState(2);
    }else if(enemypos.x - ballpos.x > 300){
        enemy->setState(1);//
    }else if(ballpos.y - enemypos.y > 200){
        enemy->jump();//
    }
}
bool GameMain::onContactBegin(EventCustom *event, const PhysicsContact& contact)
{
    return true;
}
void GameMain::menuPauseCallback(Ref *pSender, TouchEventType type)
{
    if(type == TOUCH_EVENT_ENDED){
        GamePause * pauselayer = GamePause::create();
        this->addChild(pauselayer,8);
    }
}
void GameMain::menuJumpCallback(Ref *pSender, TouchEventType type)
{
    if(m_ispause)
        return;
    hero->jump();
}
void GameMain::menuKickCallback(Ref *pSender, TouchEventType type)
{
    if(m_ispause)
        return;
    hero->kick();
}
void GameMain::menuLeftCallback(Ref *pSender, TouchEventType type)
{
    if(m_ispause)
        return;
    if(type == TOUCH_EVENT_BEGAN)
    {
        hero->setState(2);
    }else if(type == TOUCH_EVENT_ENDED)
    {
        hero->setState(0);
    }
}
void GameMain::menuRightCallback(Ref *pSender, TouchEventType type)
{
    if(m_ispause)
        return;
    if(type == TOUCH_EVENT_BEGAN)
    {
        hero->setState(1);
    }else if(type == TOUCH_EVENT_ENDED)
    {
        hero->setState(0);
    }
}
void GameMain::onEnterTransitionDidFinish()
{
    Layer::onEnterTransitionDidFinish();
    Director::getInstance()->setDepthTest(false);
}

void GameMain::onExitTransitionDidStart()
{
    Layer::onExitTransitionDidStart();
}
void GameMain::onExit(){
    Layer::onExit();
}
void GameMain::onEnter(){
    Layer::onEnter();
}