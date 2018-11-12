#pragma once
#include "Entity.h"

class Weapon;

class Player: Entity
{
public:
	Player(sf::RenderWindow*);
	~Player();
	void Draw();
	void Move(int, int);
	void LookAt(int, int);
	sf::Sprite getSprite();
	void SetupComponents();
	void UpdateBullets();
	Weapon* GetWeapon();
	void Shoot(int, int);
private:
	void UpdateAimDirection(int, int);
	void loadMedia();
	void RetainInWindow();
	bool fToRotate;
	sf::RenderWindow* fWindow;
	Weapon* fCurrentWeapon;

	//Aiming
	sf::Vector2f fAimDirNorm;

};

