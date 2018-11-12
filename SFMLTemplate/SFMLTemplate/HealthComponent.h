#pragma once
#include "Component.h"
#include <SFML\Graphics.hpp>

class HealthComponent :
	public Component
{
public:
	HealthComponent(int);
	~HealthComponent();
	void Heal(int);
	void Hurt(int);
	sf::Sprite* GetSprite();
private:
	void loadMedia();
	void UpdateHealthSprite();
	int fHealthPoint;
	int fMaxHealthPoint;
	sf::Texture fHealthTexture;
	sf::Sprite fHealthSprite;
};

