#include <unittest++/UnitTest++.h>
#include <SDL2/SDL.h>

int main(int argc, char** argv)
{
	SDL_version linked;
	SDL_version complied;

	SDL_GetVersion(&linked);
	SDL_VERSION(&complied);

	SDL_Log("Linked with SDL2 %i.%i.%i",
	        linked.major, linked.minor, linked.patch);
	SDL_Log("Complied with SDL2 %i.%i.%i",
	        complied.major , complied.minor, complied.patch);

	return UnitTest::RunAllTests();
}
