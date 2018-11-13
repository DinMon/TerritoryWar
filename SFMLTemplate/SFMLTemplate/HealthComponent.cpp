#include "HealthComponent.h"

HealthComponent::HealthComponent(int aMaxHealth): Component()
{
	fHasDied = false;
	fMaxHealthPoint = aMaxHealth;
	fHealthPoint = fMaxHealthPoint;
	loadMedia();
	fHealthSprite.setScale(0.1, 0.1);
}


HealthComponent::~HealthComponent()
{
}

void HealthComponent::Heal(int aValue)
{
	fHealthPoint += aValue;
	UpdateHealthSprite();
}

void HealthComponent::Hurt(int aValue)
{
	fHealthPoint -= aValue;
	UpdateHealthSprite();
}

bool HealthComponent::GetDied()
{
	return fHasDied;
}

sf::Sprite* HealthComponent::GetSprite()
{
	return &fHealthSprite;
}

void HealthComponent::loadMedia()
{
	if (!fHealthTexture.loadFromFile("data/images/HealthBar.png"))
	{
		throw "Cannot load texture";
	}
	fHealthSprite.setTexture(fHealthTexture);
}

void HealthComponent::UpdateHealthSprite()
{
	if (fHealthPoint <= 0)
	{
		fHasDied = true;
		fHealthSprite.setScale(0, 0);
	}
	else
	{
		double lVal = ((float)fHealthPoint / (float)fMaxHealthPoint)*0.1;
		fHealthSprite.setScale(lVal, 0.1);
	}
}


