#pragma once
#include "Stage.h"
#include "ThreadPool.h"
#include <vector>

class Player;
class Enemy;
class Map;

void simpleFunction(std::vector<Enemy*>, int);

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
	void Reset(sf::RenderWindow*);
	sf::RenderWindow* fWindow;

	sf::Clock fClock; // starts the clock
	void PopulateEnemies();
	void DrawEnemies();

	void RemoveDiedEnemies();
	void RemovePlayer();

	bool fIsGameOver;

	sf::Texture fGameOverTexture;
	sf::Sprite fGameOverSprite;

	//Input Variable
	int fHorizontalInput;
	int fVerticalInput;
	int fMouseX;
	int fMouseY;

	Player* fPlayer;
	Map* fMap;
	ThreadPool fPool;
	std::vector<Enemy*> fEnemies;
	std::future<bool> fFuture;
	void loadMedia();
};

