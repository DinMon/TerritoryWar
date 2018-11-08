#pragma once
#include "StageEnum.h"
#include <SFML\Graphics.hpp>

class Stage;

class StageManager
{
public:
	static StageManager* Instance();
	StageManager(StageEnum);
	~StageManager();
	bool GetIsQuit();
	void HandleInput(sf::RenderWindow*);
	void HandleUpdate();
	void HandleDraw(sf::RenderWindow*);
	void SetState(StageEnum);

private:
	static Stage* fStage;
	bool isQuit;
	static StageManager* fInstance;
};

