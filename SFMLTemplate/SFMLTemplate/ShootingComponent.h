#pragma once
#include "Component.h"
#include <vector>
#include <SFML\Graphics.hpp>

class Entity;
class Weapon;
class Bullet;

class ShootingComponent :
	public Component
{
public:
	ShootingComponent(Entity*);
	~ShootingComponent();
	void FireWeapon(sf::Vector2f aAimDir);
	void Fire();
	void Reload();
	void UpdateBulletPos();
	void DrawBullets(sf::RenderWindow*);
private:
	Entity* fEntity;
	std::vector<Bullet*> fBullets;
};

