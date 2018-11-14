#pragma once
#include "Stage.h"
#include <vector>

class Player;
class Enemy;
class Map;

class GameplayStage :
	public Stage
{
public:
	static GameplayStage* Instance(sf::RenderWindow* aWindow);
	void Draw();
	void GetInput();
	void Update();
	void setSprite();
	std::vector<Enemy*> GetEnemies();
	GameplayStage(sf::RenderWindow* aWindow);
	~GameplayStage();
private:
	static GameplayStage* fInstance;
	sf::RenderWindow* fWindow;

	void PopulateEnemies();
	void DrawEnemies();

	void RemoveDiedEnemies();

	//Input Variable
	int fHorizontalInput;
	int fVerticalInput;
	int fMouseX;
	int fMouseY;

	Player* fPlayer;
	Map* fMap;
	std::vector<Enemy*> fEnemies;

	void loadMedia();
};

