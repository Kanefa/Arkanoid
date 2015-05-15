#include "collision.h"

// Define a function that deals with paddle/ball collisions
void testCollision(Paddle &paddle, Ball &ball)
{
	// If there's no intersection, exit the function
	if (!isIntersecting(paddle, ball))
	{
		return;
	}

	// Otherwise redirect the ball upwards
	ball.mVelocity.y = -ball.getMaxVelocity();

	// Direct he ball dependently on the position where he paddle was struck
	if (ball.getX() < paddle.getX())
	{
		// paddle struck on left side
		ball.mVelocity.x = -ball.getMaxVelocity();
	}
	else
	{
		// paddle struck on right side
		ball.mVelocity.x = ball.getMaxVelocity();
	}
}

// Define a function that deals with brick/ball collisions
void testCollision(Brick &brick, Ball &ball)
{
	// If there's no intersection, exit the function
	if (!isIntersecting(brick, ball))
	{
		return;
	}

	// Otherwise the brick has been struck!
	brick.mDestroyed = true;

	// Calculate how much the ball intersects the brick in every direction
	float overlapLeft{ ball.getRight() - brick.getLeft() };
	float overlapRight{ brick.getRight() - ball.getLeft() };
	float overlapTop{ ball.getBottom() - brick.getTop() };
	float overlapBottom{ brick.getBottom() - ball.getTop() };

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
		ball.mVelocity.x = ballFromLeft ? -ball.getMaxVelocity() : ball.getMaxVelocity();
	}
	else
	{
		ball.mVelocity.y = ballFromTop ? -ball.getMaxVelocity() : ball.getMaxVelocity();
	}
}
