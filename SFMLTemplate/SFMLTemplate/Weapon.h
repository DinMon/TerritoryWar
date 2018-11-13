#pragma once
#include "Entity.h"
#include <SFML\Audio.hpp>

class Weapon :
	public Entity
{
public:
	Weapon(std::string, int, int aCartridgeNum, float aReloadSpeed);
	~Weapon();
	int GetCurrentBullets();
	void ResetCartridge();
	void ShootBullet();
	float GetReloadSpeed();

	sf::Sound* GetReloadSound();

	sf::Sound * GetShot1Sound();

	// Inherited via Entity
	void loadMedia();
private:
	int fCartridgeNum;
	int fCurrentBullets;
	float fReloadSpeed;
	sf::SoundBuffer fReloadSoundBuffer;
	sf::Sound fReloadSound;
	sf::SoundBuffer fShot1SoundBuffer;
	sf::Sound fShot1Sound;
};

