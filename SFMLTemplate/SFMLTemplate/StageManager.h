#pragma once
#include "StageEnum.h"
#include <SFML\Graphics.hpp>

class Stage;

class StageManager
{
public:
	static StageManager* Instance(sf::RenderWindow*);
	StageManager(StageEnum, sf::RenderWindow*);
	~StageManager();
	bool GetIsQuit();
	void HandleInput();
	void HandleUpdate();
	void HandleDraw();
	void SetState(StageEnum);

private:
	static Stage* fStage;
	sf::RenderWindow* fWindow;
	bool isQuit;
	static StageManager* fInstance;
};

