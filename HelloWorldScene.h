#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"

class HelloWorld : public cocos2d::Layer
{
    b2World* world;
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    void initPhysics();
    
    void addOneSprite();
    
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
