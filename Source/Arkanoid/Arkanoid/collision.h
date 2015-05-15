#ifndef COLLISION_H
#define COLLISION_H

#include "ball.h"
#include "brick.h"
#include "paddle.h"

template<class T1, class T2> bool isIntersecting(T1 &obj1, T2 &obj2);
void testCollision(Paddle &paddle, Ball &ball);
void testCollision(Brick &brick, Ball &ball);

#include "collision.inl"

#endif
