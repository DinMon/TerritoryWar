#pragma once
#include "Entity.h"

class Weapon :
	public Entity
{
public:
	Weapon(std::string, int, int aCartridgeNum, float aReloadSpeed);
	~Weapon();

	// Inherited via Entity
	void loadMedia();
};

