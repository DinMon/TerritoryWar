#pragma once
#include "Stage.h"
class GameplayStage :
	public Stage
{
public:
	static GameplayStage* Instance(sf::RenderWindow* aWindow);
	void Draw();
	void GetInput();
	void Update();
	GameplayStage(sf::RenderWindow* aWindow);
	~GameplayStage();
private:
	static GameplayStage* fInstance;
	sf::RenderWindow* fWindow;
	void loadMedia();
};

