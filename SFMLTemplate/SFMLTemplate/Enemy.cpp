#include "Enemy.h"
#include "HealthComponent.h"
#include "Bullet.h"
#include "DamageComponent.h"

Enemy::Enemy(sf::RenderWindow* aWindow):Entity("Monster")
{
	fWindow = aWindow;
	loadMedia();
	SetupComponents();
}

Enemy::~Enemy()
{
}

void Enemy::Draw()
{
	fWindow->draw(fEntitySprite);
	fWindow->draw(*(fComponentContainer->GetComponent<HealthComponent>()->GetSprite()));
}

void Enemy::loadMedia()
{
	if (!fEntityTexture.loadFromFile("data/images/zombie.png"))
	{
		throw "Cannot load texture";
	}
	fEntitySprite.setTexture(fEntityTexture);
	fEntitySprite.setPosition(200, 200);
	fEntitySprite.setScale(sf::Vector2f(0.4, 0.4));
}

void Enemy::SetupComponents()
{
	//Health Component
	fComponentContainer->AddComponent<HealthComponent>(new HealthComponent(50));
	fComponentContainer->GetComponent<HealthComponent>()->GetSprite()->setPosition(fEntitySprite.getPosition().x, fEntitySprite.getPosition().y - 2);
	fComponentContainer->GetComponent<HealthComponent>()->GetSprite()->setRotation(fEntitySprite.getRotation());
}

void Enemy::OnBulletCollision(Bullet* aBullet)
{
	fComponentContainer->GetComponent<HealthComponent>()->Hurt(aBullet->GetComponentContainer()->GetComponent<DamageComponent>()->GetDamage());
}
