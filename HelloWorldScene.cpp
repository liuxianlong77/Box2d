#include "HelloWorldScene.h"
#include "cocos2d.h"
#include "ContactListener.h"
USING_NS_CC;
#define PTM_RATIO 32
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
    
    initPhysics();
   
    this->schedule([this](float){
        for (b2Body* b = world->GetBodyList(); b; b = b->GetNext())
        {
            float timeStep = 0.03f;
            int32 velocityIterations = 8;
            int32 positionIterations = 1;
            
            world->Step(timeStep, velocityIterations, positionIterations);
            if (b->GetUserData() != nullptr) {
                Sprite* sprite = (Sprite*)b->GetUserData();
                sprite->setPosition( Vec2( b->GetPosition().x *
                                          PTM_RATIO, b->GetPosition().y * PTM_RATIO) );
                sprite->setRotation( -1 * CC_RADIANS_TO_DEGREES(b->GetAngle()) );
            }  
        }
        
    },0.0f,"Update");
    
    this->schedule([this](float){
        addOneSprite();
    },1.0f,"addSprite");
    return true;
}

void HelloWorld::initPhysics()
{
    ContactListener* conListener=new ContactListener();
    Size s = Director::getInstance()->getVisibleSize();

    //重力参数
    b2Vec2 gravity;
    gravity.Set(0.0f,-10.0f);
    //创建世界
    world=new b2World(gravity);
    world->SetAllowSleeping(true);
    world->SetContinuousPhysics(true);
    world->SetContactListener(conListener);
    //地面物体定义
    b2BodyDef groundBodyDef;
    //左下角
    groundBodyDef.position.Set(0,0);
    
    //创建地面物体
    b2Body* groundBody=world->CreateBody(&groundBodyDef);
    
    //定义一个有边的形状
    b2EdgeShape groundBox;
    
    //底部
    groundBox.Set(b2Vec2(0,0),b2Vec2(s.width/PTM_RATIO,0));
    
    //设置物体形状
    groundBody->CreateFixture(&groundBox,0);
    
    // 顶部
    groundBox.Set(b2Vec2(0,s.height/PTM_RATIO),
                  b2Vec2(s.width/PTM_RATIO,s.height/PTM_RATIO));
    groundBody->CreateFixture(&groundBox,0);
    
    // 左边
    groundBox.Set(b2Vec2(0,s.height/PTM_RATIO), b2Vec2(0,0));
    groundBody->CreateFixture(&groundBox,0);
    
    // 右边
    groundBox.Set(b2Vec2(s.width/PTM_RATIO,s.height/PTM_RATIO),
                  b2Vec2(s.width/PTM_RATIO,0));
    groundBody->CreateFixture(&groundBox,0);
    
    
}

void HelloWorld::addOneSprite()
{
    
    cocos2d::Vec2 p=cocos2d::Vec2(500,500);
        //创建物理引擎精灵对象
        auto sprite = Sprite::create("BoxA2.png");
        sprite->setPosition( Vec2( p.x, p.y) );
        this->addChild(sprite);
    
        //物体定义
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(sprite->getPositionX()/PTM_RATIO, sprite->getPositionY()/PTM_RATIO);
        b2Body *body = world->CreateBody(&bodyDef);
        body->SetUserData(sprite);
    
        // 定义2米见方的盒子形状
        b2PolygonShape dynamicBox;
        dynamicBox.SetAsBox(1,1);
    
        // 夹具定义
        b2FixtureDef fixtureDef;
        //设置夹具的形状
        fixtureDef.shape = &dynamicBox;
        //设置密度
        fixtureDef.density = 1.0f;
        //设置摩擦系数
        fixtureDef.friction = 0.3f;
        //使用夹具固定形状到物体上    
        body->CreateFixture(&fixtureDef);
    
}

