#include "Weapon.h"
#include "DamageComponent.h"

Weapon::Weapon(std::string aName, int aDamage, int aCartridgeNum, float aReloadSpeed):Entity(aName)
{
	fComponentContainer->AddComponent<DamageComponent>(new DamageComponent(aDamage));
}

Weapon::~Weapon()
{
}

void Weapon::loadMedia()
{
	if (!fEntityTexture.loadFromFile("data/images/HandGun.png"))
	{
		throw "Cannot load texture";
	}
	fEntitySprite.setTexture(fEntityTexture);
}
