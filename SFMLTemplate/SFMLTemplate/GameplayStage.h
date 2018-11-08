#pragma once
#include "Stage.h"
class GameplayStage :
	public Stage
{
public:
	static GameplayStage* Instance();
	void Draw(sf::RenderWindow*);
	void GetInput(sf::RenderWindow*);
	void Update();
	GameplayStage();
	~GameplayStage();
private:
	static GameplayStage* fInstance;
	void loadMedia();
};

