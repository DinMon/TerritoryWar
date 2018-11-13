#pragma once
#include "Entity.h"

class Bullet;

class Enemy :
	public Entity
{
public:
	Enemy(sf::RenderWindow*);
	~Enemy();
	void Draw();

	// Inherited via Entity
	virtual void loadMedia() override;
	void OnBulletCollision(Bullet*);
private:
	void SetupComponents();
	sf::RenderWindow* fWindow;
};

