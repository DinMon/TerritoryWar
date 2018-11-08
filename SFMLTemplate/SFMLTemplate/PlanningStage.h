#pragma once
#include "Stage.h"

class PlanningStage :
	public Stage
{
public:
	static PlanningStage* Instance(sf::RenderWindow*);
	void Draw();
	void GetInput();
	void Update();
	PlanningStage(sf::RenderWindow*);
	~PlanningStage();
private:
	static PlanningStage* fInstance;
	void loadMedia();
	void setSprite();

	sf::RenderWindow* fWindow;

	//Textures
	sf::Texture fPlayTexture;

	//Sprites
	sf::Sprite fPlaySprite;
};

