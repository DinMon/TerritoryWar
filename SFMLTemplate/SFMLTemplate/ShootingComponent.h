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
	ShootingComponent(Entity*, sf::RenderWindow*);
	~ShootingComponent();
	void FireWeapon(sf::Vector2f aAimDir);
	void Fire();
	void Reload();
	void UpdateReloadTime();
	void UpdateBulletPos();
	void DrawBullets();
private:
	sf::Clock fClock;
	bool fStartClock;
	sf::RenderWindow* fWindow;
	void OnCollision(int);
	void OnOutsideScreen(int);
	Entity* fEntity;
	std::vector<Bullet*> fBullets;
};

