#pragma once
#include "Entity.h"

#define VELOCITY

class DamageComponent;

class Bullet :
	public Entity
{
public:
	Bullet(DamageComponent*, sf::Vector2f aDirectionAngle);
	~Bullet();
	void Move();
	void Draw(sf::RenderWindow* aWindow);
	sf::Sprite* getSprite();
	// Inherited via Entity
	void loadMedia();
private:
	sf::Vector2f fDirectionAngle;
	float fSpeed;
	sf::Vector2f fCurrentVelocity;
};

