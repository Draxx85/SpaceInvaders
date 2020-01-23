#include "GameManager.h"

void GameManager::Init()
{
	////////////////TEST CODE//////////////////////////
	Entity *ent = new Entity();
	//m_Components = new std::vector<Component*>();
	//	Entity* obj = new Entity();

	SpriteComponent *comp = new SpriteComponent();
	ent->AddComponent((Component*)comp);
	comp = nullptr;
	if (Entity::TryGetComponent<SpriteComponent>(*ent, comp))
	{
		SDL_Log("This should of worked maybe");
	}
}

void GameManager::StartGame()
{

}
