
#include "ContactListener.h"
#include "cocos2d.h"
USING_NS_CC;
void ContactListener::BeginContact(b2Contact* contact)
{
    b2Body* bodyA = contact->GetFixtureA()->GetBody();
    b2Body* bodyB = contact->GetFixtureB()->GetBody();
    Sprite* spriteA = (Sprite*)bodyA->GetUserData();
    Sprite* spriteB = (Sprite*)bodyB->GetUserData();
    //更改碰撞体颜色
    if (spriteA != NULL && spriteB != NULL)
    {
        bodys.push_back(bodyA);
        bodys.push_back(bodyB);
    }
}


void ContactListener::EndContact(b2Contact* contact)
{
    b2Body* bodyA = contact->GetFixtureA()->GetBody();
    b2Body* bodyB = contact->GetFixtureB()->GetBody();
    Sprite* spriteA = (Sprite*)bodyA->GetUserData();
    Sprite* spriteB = (Sprite*)bodyB->GetUserData();
    
    //更改碰撞体颜色
    if (spriteA != NULL && spriteB != NULL)
    {
       // spriteA->setColor(Color3B(0,0,0));
       // spriteA->setColor(Color3B(0,0,0));
    }
}
