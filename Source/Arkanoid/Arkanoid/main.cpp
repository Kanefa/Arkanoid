#include "game.h"

namespace global
{
	extern const unsigned int windowWidth{800}, windowHeight{600};
	extern const float ballVelocity{0.5f};
}

int main()
{
	Game{}.run();

	return 0;
}
