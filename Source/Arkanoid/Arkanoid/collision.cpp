#include "collision.h"
#include "cPhysics.h"

namespace global
{
	extern const float ballVelocity;
}

// Define a function that deals with paddle/ball collisions
void testCollisionPB(Entity &paddle, Entity &ball)
{
	auto &cpPaddle(paddle.getComponent<CPhysics>());
	auto &cpBall(ball.getComponent<CPhysics>());

	// If there's no intersection, exit the function
	if (!isIntersecting(cpPaddle, cpBall))
	{
		return;
	}

	// Otherwise redirect the ball upwards
	cpBall.mVelocity.y = -global::ballVelocity;

	// Direct he ball dependently on the position where he paddle was struck
	if (cpBall.getX() < cpPaddle.getX())
	{
		// paddle struck on left side
		cpBall.mVelocity.x = -global::ballVelocity;
	}
	else
	{
		// paddle struck on right side
		cpBall.mVelocity.x = global::ballVelocity;
	}
}

// Define a function that deals with brick/ball collisions
void testCollisionBB(Entity &brick, Entity &ball)
{
	auto &cpBrick(brick.getComponent<CPhysics>());
	auto &cpBall(ball.getComponent<CPhysics>());

	// If there's no intersection, exit the function
	if (!isIntersecting(cpBrick, cpBall))
	{
		return;
	}

	// Otherwise the brick has been struck!
	brick.destroy();

	// Calculate how much the ball intersects the brick in every direction
	float overlapLeft{cpBall.getRight() - cpBrick.getLeft()};
	float overlapRight{cpBrick.getRight() - cpBall.getLeft()};
	float overlapTop{cpBall.getBottom() - cpBrick.getTop()};
	float overlapBottom{cpBrick.getBottom() - cpBall.getTop()};

	// If the magnitude of the left overlap is smaller than the right
	// overlap we can assume the ball hit the brick from the left.
	bool ballFromLeft(abs(overlapLeft) < abs(overlapRight));

	// If the magnitude of the top overlap is smaller than the bottom
	// overlap we can assume the ball hit the brick from the top.
	bool ballFromTop(abs(overlapTop) < abs(overlapBottom));

	// Store the minimum overlaps for the X and Y axis
	float minOverlapX{ ballFromLeft ? overlapLeft : overlapRight };
	float minOverlapY{ ballFromTop ? overlapTop : overlapBottom };

	// If the magnitude of the X overlap is less than the magnitude of the Y
	// overlap, we can assume the ball struck the brick horizontally - otherwise,
	// the ball hit the brick vertically

	// The based on our results we change either the X or Y velocity
	// of the ball, creating a "realistic" response for the collision
	if (abs(minOverlapX) < abs(minOverlapY))
	{
		cpBall.mVelocity.x = ballFromLeft ? -global::ballVelocity : global::ballVelocity;
	}
	else
	{
		cpBall.mVelocity.y = ballFromTop ? -global::ballVelocity : global::ballVelocity;
	}
}
