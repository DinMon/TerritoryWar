#include "Bullet.h"
#include "DamageComponent.h"

Bullet::Bullet(DamageComponent* aDamageComponent, sf::Vector2f aDirectionAngle):Entity("Bullet")
{
	fSpeed = 1;
	fDirectionAngle = aDirectionAngle;
	fComponentContainer->AddComponent<DamageComponent>(aDamageComponent);
	loadMedia();
}

Bullet::~Bullet()
{
}

void Bullet::Move()
{
	fEntitySprite.move(fDirectionAngle * fSpeed);
}

void Bullet::Draw(sf::RenderWindow * aWindow)
{
	aWindow->draw(fEntitySprite);
}

sf::Sprite* Bullet::getSprite()
{
	return &fEntitySprite;
}

void Bullet::loadMedia()
{
	if (!fEntityTexture.loadFromFile("data/images/bullet4.png"))
	{
		throw "Cannot load texture";
	}
	fEntitySprite.setTexture(fEntityTexture);
	fEntitySprite.setScale(0.03, 0.03);
}

