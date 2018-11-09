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
	void setSprite();
	GameplayStage(sf::RenderWindow* aWindow);
	~GameplayStage();
private:
	static GameplayStage* fInstance;
	sf::RenderWindow* fWindow;

	//Input Variable
	int fHorizontalInput;
	int fVerticalInput;
	
	//Textures
	sf::Texture fPlayerTexture;

	//Sprites
	sf::Sprite fPlayerSprite;

	void loadMedia();
	void Move();
	void RetainInWindow();
};

