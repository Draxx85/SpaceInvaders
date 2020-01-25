#pragma once

#include <vector>
#include "SDL.h"
#include "Process.h"
#include "Component.h"
#include "Engine.h"

struct SVector2D
{
	float x = 0;
	float y = 0;

	SVector2D()
		:x(0), y(0)	{}

	SVector2D(int xPos, int yPos)
		:x((float)xPos), y((float)yPos) {}

	SVector2D(float xPos, float yPos)
		:x(xPos), y(yPos){}
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
			DestRect->x = (int)pos.x;
			DestRect->y = (int)pos.y;
		}
		Position = std::move(pos);
	}

	void SetScale(SVector2D scale)
	{
		if (DestRect != nullptr)
		{
			DestRect->w *= (int)scale.x;
			DestRect->h *= (int)scale.y;
		}
		Scale = std::move(scale);
	}

	STransform(int x, int y, int w, int h)
	{
		if (DestRect == nullptr)
		{
			SDL_Rect rect;
			rect.x = x;	rect.y = y;
			rect.w = w;	rect.h = h;
			DestRect = &rect;
			Position = SVector2D(rect.x, rect.y);
		}
	}

	STransform(SDL_Rect &rect)
	{
		DestRect = &rect;
	}

	~STransform()
	{
		if (DestRect != nullptr)
		{
			delete DestRect;
		}
		DestRect = nullptr;
	}

	void SetDestRect(SDL_Rect &ref)
	{
		DestRect = &ref;
		if (DestRect)
		{
			Position = SVector2D(DestRect->x, DestRect->y);
			Scale = SVector2D(1, 1);
		}
	}
};

class Component;

class Entity : public Process
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