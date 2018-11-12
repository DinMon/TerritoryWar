#include "ShootingComponent.h"
#include "DamageComponent.h"
#include "Bullet.h"
#include "Player.h"
#include "Weapon.h"
#include <iostream>

ShootingComponent::ShootingComponent(Entity* aEntity)
{
	fEntity = aEntity;
}

ShootingComponent::~ShootingComponent()
{
}

void ShootingComponent::FireWeapon(sf::Vector2f aAimDir)
{
	Player* lPlayer = (Player*)fEntity;
	//error
	Bullet* lBullet = new Bullet(fEntity->GetComponentContainer()->GetComponent<DamageComponent>(), aAimDir);
	lBullet->getSprite()->setPosition(lPlayer->getSprite().getPosition().x, lPlayer->getSprite().getPosition().y);

	std::cout << lBullet->getSprite()->getPosition().x << " " << lBullet->getSprite()->getPosition().y << "\n";
	fBullets.push_back(lBullet);

	lBullet->Move();
}

void ShootingComponent::Fire()
{
}

void ShootingComponent::Reload()
{
}

void ShootingComponent::UpdateBulletPos()
{
	if (fBullets.size() > 0)
	{
		for (auto &bullet : fBullets)
		{
			bullet->Move();
		}
	}
}

void ShootingComponent::DrawBullets(sf::RenderWindow* aWindow)
{
	for (auto &bullet : fBullets)
	{
		bullet->Draw(aWindow);
	}
}

//Destroy bullet
