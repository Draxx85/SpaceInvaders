#include "SDL.h"
#include "stdlib.h"
#include "Engine.h"
#include "GameManager.h"

int main(int argc, char* argv[])
{
	Engine::InitEngine();
	GameManager::Init();

	Engine::StartEngineLoop();

	Engine::CleanEngine();

	return 0;
}
