#include "SDL.h"
#include "stdlib.h"
#include "Engine.h"
#include "GameManager.h"
#include <ctime>

int main(int argc, char* argv[])
{
	std::srand(std::time(0));
	Engine::InitEngine();
	GameManager::Init();

	Engine::StartEngineLoop();

	GameManager::CleanGame();
	Engine::CleanEngine();

	return 0;
}
