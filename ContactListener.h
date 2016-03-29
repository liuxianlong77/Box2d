#include "Box2D/Box2D.h"
#ifndef HelloBox2d_ContactListener_h
#define HelloBox2d_ContactListener_h
class ContactListener : public b2ContactListener
{
     std::vector<b2Body*> bodys;
public:
    //碰撞开始
    void BeginContact(b2Contact* contact);
    //碰撞结束
    void EndContact(b2Contact* contact);
};

