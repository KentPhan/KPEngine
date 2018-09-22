#pragma once
#include "GameObjectType.h"
#include "include/Utils/KPVector2.h"
#include "include/Utils/KPString.h"

using namespace KPEngine::Utils;

class GameObject
{
	
protected:
	KPString *name_;
	
	
public:
	char* GetName() const;
	void SetName(const char* name);
	virtual void PrintInfo() const;
	virtual char GetSymbol();
	void SetPosition(int x, int y);

	KPVector2 Position;
	GameObjectType Type;

	bool empty = true;
	GameObject();
	~GameObject();
};

