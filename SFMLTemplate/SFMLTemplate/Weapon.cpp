#include "Weapon.h"
#include "DamageComponent.h"

Weapon::Weapon(std::string aName, int aDamage, int aCartridgeNum, float aReloadSpeed):Entity(aName)
{
	fComponentContainer->AddComponent<DamageComponent>(new DamageComponent(aDamage));
	fCartridgeNum = aCartridgeNum;
	fReloadSpeed = aReloadSpeed;
	fCurrentBullets = fCartridgeNum;
	loadMedia();
}

Weapon::~Weapon()
{
}

int Weapon::GetCurrentBullets()
{
	return fCurrentBullets;
}

void Weapon::ResetCartridge()
{
	fCurrentBullets = fCartridgeNum;
}

void Weapon::ShootBullet()
{
	fCurrentBullets--;
}

float Weapon::GetReloadSpeed()
{
	return fReloadSpeed;
}

sf::Sound* Weapon::GetReloadSound()
{
	return &fReloadSound;
}

sf::Sound* Weapon::GetShot1Sound()
{
	return &fShot1Sound;
}

void Weapon::loadMedia()
{
	//if (!fEntityTexture.loadFromFile("data/images/HandGun.png"))
	//{
	//	throw "Cannot load texture";
	//}
	if (!fReloadSoundBuffer.loadFromFile("data/sounds/reload.wav"))
	{
		throw "Cannot load texture";
	}
	fReloadSound.setBuffer(fReloadSoundBuffer);
	if (!fShot1SoundBuffer.loadFromFile("data/sounds/shot1.wav"))
	{
		throw "Cannot load texture";
	}
	fShot1Sound.setBuffer(fShot1SoundBuffer);
}
