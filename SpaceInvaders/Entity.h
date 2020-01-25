#pragma once

#include <vector>
#include "SDL.h"
#include "Process.h"
#include "Component.h"
#include "Engine.h"

struct SVector2D
{
	int x = 0;
	int y = 0;

	SVector2D()
		:x(0), y(0)	{}

	SVector2D(int xPos, int yPos)
		:x(xPos), y(yPos) {}
};

struct STransform
{
	SDL_Rect *DestRect;
	SVector2D Position;
	SVector2D Scale;
	float angle = 0.0f;

	void SetPosition(SVector2D pos)
	{
		if (DestRect != nullptr)
		{
			DestRect->x = pos.x;
			DestRect->y = pos.y;
		}
	}

	void SetScale(SVector2D scale)
	{
		if (DestRect != nullptr)
		{
			DestRect->w *= scale.x;
			DestRect->h *= scale.y;
		}
	}

	STransform(int x, int y, int w, int h)
	{
		if (DestRect == nullptr)
		{
			SDL_Rect rect;
			rect.x = x;	rect.y = y;
			rect.w = w;	rect.h = h;
			DestRect = &rect;
		}
	}

	STransform(SDL_Rect &rect)
	{
		DestRect = &rect;
	}

	~STransform()
	{
		delete DestRect;
	}

	void SetDestRect(SDL_Rect &ref)
	{
		DestRect = &ref;
	}
};

class Component;

class Entity : Process
{
public:
	Entity();
	virtual ~Entity();
	STransform *GetTransform();

	virtual void Update(float deltaTime) override;
	virtual void TimedUpdate(float deltaTime) override;
	
	std::vector<Component*> *m_Components;

	virtual void AddComponent(Component *component);
	void SetPosition(SVector2D pos);

	template<typename T>
	static bool TryGetComponent(Entity &entity, T *&obj);

private:
	STransform *m_Transform;
	
};

template<typename T>
bool Entity::TryGetComponent(Entity &entity, T *&obj)
{
	T* pt = nullptr;
	for (std::vector<Component*>::iterator iter = entity.m_Components->begin();
		iter != entity.m_Components->end(); ++iter)
	{
		pt = dynamic_cast<T*>(*iter);
		if (pt != nullptr)
		{
			obj = pt;
			return true;
		}
	}
	return false;
}