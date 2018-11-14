#pragma once
#include "Entity.h"
#include <SFML\Audio.hpp>

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
	sf::Vector2i GetCoordinates();
	void UpdateBullets();
	Weapon* GetWeapon();
	void Shoot(int, int);
	void Reload();
private:
	sf::Clock fClock;
	bool fStartClock;
	float fTimeBeforeHurt;
	void SetupComponents();
	void UpdateAimDirection(int, int);
	void loadMedia();
	void RetainFromObstacle();
	void OnEnemyCollision();
	void RetainInWindow();
	bool fToRotate;
	sf::RenderWindow* fWindow;
	Weapon* fCurrentWeapon;

	sf::SoundBuffer fHurtSoundBuffer;
	sf::Sound fHurtSound;

	//Aiming
	sf::Vector2f fAimDirNorm;
};

