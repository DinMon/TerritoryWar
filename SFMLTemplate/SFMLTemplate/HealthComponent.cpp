#include "HealthComponent.h"

HealthComponent::HealthComponent(int aMaxHealth): Component()
{
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
	fHealthSprite.setScale((fHealthPoint/fMaxHealthPoint)*0.1, 0.1);
}


