#pragma once
#include "Stage.h"

class PlanningStage :
	public Stage
{
public:
	static PlanningStage* Instance();
	void Draw(sf::RenderWindow*);
	void GetInput(sf::RenderWindow*);
	void Update();
	PlanningStage();
	~PlanningStage();
private:
	static PlanningStage* fInstance;
	void loadMedia();
	void setSprite(sf::RenderWindow*);
	//Textures
	sf::Texture fPlayTexture;

	//Sprites
	sf::Sprite fPlaySprite;
};

