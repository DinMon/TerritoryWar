#pragma once
#include "Entity.h"

class Weapon;

class Player: Entity
{
public:
	Player(sf::RenderWindow*);
	~Player();
	void Draw();
	void Update();
	void Move(int, int);
	void LookAt(int, int);
	sf::Sprite getSprite();
	void UpdateBullets();
	Weapon* GetWeapon();
	void Shoot(int, int);
	void Reload();
private:
	void SetupComponents();
	void UpdateAimDirection(int, int);
	void loadMedia();
	void RetainInWindow();
	bool fToRotate;
	sf::RenderWindow* fWindow;
	Weapon* fCurrentWeapon;

	//Aiming
	sf::Vector2f fAimDirNorm;
};

