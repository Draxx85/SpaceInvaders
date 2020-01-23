#include "SDL.h"
#include "stdlib.h"
#include "Engine.h"
#include "GameManager.h"

int main(int argc, char* argv[])
{
	Engine::InitEngine();
	GameManager::Init();

	Engine::StartEngineLoop();

	GameManager::CleanGame();
	Engine::CleanEngine();

	return 0;
}
