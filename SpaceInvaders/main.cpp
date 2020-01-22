#include "SDL.h"
#include "stdlib.h"
#include "Engine.h"

int main(int argc, char* argv[])
{
	Engine::InitEngine();
	
	Engine::StartEngineLoop();

	Engine::CleanEngine();

	return 0;
}
