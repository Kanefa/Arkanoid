#include "game.h"

namespace global
{
	extern const unsigned int windowWidth{800}, windowHeight{600};
}

int main()
{
	Game{}.run();
	return 0;
}
