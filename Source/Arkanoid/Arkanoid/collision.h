#ifndef COLLISION_H
#define COLLISION_H

#include "entity.h"

template<class T1, class T2> bool isIntersecting(T1 &obj1, T2 &obj2);
void testCollisionPB(Entity &paddle, Entity &ball);
void testCollisionBB(Entity &brick, Entity &ball);

#include "collision.inl"

#endif
