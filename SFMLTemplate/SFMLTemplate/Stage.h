#pragma once
#include <SFML\Graphics.hpp>

class Stage
{
public:
	Stage() {};
	~Stage() {};
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void GetInput() = 0;
};

