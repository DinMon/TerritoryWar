#include "ShootingComponent.h"
#include "DamageComponent.h"
#include "Bullet.h"
#include "Player.h"
#include "Enemy.h"
#include "Weapon.h"
#include "GameplayStage.h"
#include <iostream>
#include <vector>

ShootingComponent::ShootingComponent(Entity* aEntity, sf::RenderWindow* aWindow)
{
	fEntity = aEntity;
	fWindow = aWindow;
	fStartClock = true;
}

ShootingComponent::~ShootingComponent()
{
}

void ShootingComponent::FireWeapon(sf::Vector2f aAimDir)
{
	Player* lPlayer = (Player*)fEntity;
	Weapon* lWeapon = lPlayer->GetWeapon();
	if (lWeapon->GetCurrentBullets() > 0)
	{
		lWeapon->ShootBullet();
		Bullet* lBullet = new Bullet(lWeapon->GetComponentContainer()->GetComponent<DamageComponent>(), aAimDir);
		lBullet->getSprite()->setPosition(lPlayer->getSprite().getPosition().x, lPlayer->getSprite().getPosition().y);

		std::cout << lBullet->getSprite()->getPosition().x << " " << lBullet->getSprite()->getPosition().y << "\n";
		fBullets.push_back(lBullet);

		lBullet->Move();
		lWeapon->GetShot1Sound()->play();
	}
	else
	{
		Reload();
	}
}

void ShootingComponent::Reload()
{
	Player* lPlayer = (Player*)fEntity;
	Weapon* lWeapon = lPlayer->GetWeapon();
	if (fStartClock)
	{
		lWeapon->GetReloadSound()->play();
		fStartClock = false;
		fClock.restart();
	}
}

void ShootingComponent::UpdateReloadTime()
{
	Player* lPlayer = (Player*)fEntity;
	Weapon* lWeapon = lPlayer->GetWeapon();
	if (fClock.getElapsedTime().asSeconds() > lWeapon->GetReloadSpeed() && !fStartClock)
	{
		fStartClock = true;
		lWeapon->ResetCartridge();
	}
}

void ShootingComponent::UpdateBulletPos()
{
	if (fBullets.size() > 0)
	{
		for (int i = 0; i < fBullets.size(); i++)
		{
			fBullets[i]->Move();
			
			OnOutsideScreen(i);
			OnCollision(i);

			//std::cout << fBullets.size() << "\n";
		}
	}
}

void ShootingComponent::DrawBullets()
{
	for (auto &bullet : fBullets)
	{
		bullet->Draw(fWindow);
	}
}

void ShootingComponent::OnCollision(int index)
{
	std::vector<Enemy*> lEnemies = GameplayStage::Instance(fWindow)->GetEnemies();
	if (lEnemies.size() > 0)
	{
		if (fBullets.size() > 0)
		{
			for (int i = 0; i < lEnemies.size(); i++)
			{
				if (fBullets[index]->getSprite()->getGlobalBounds().intersects(lEnemies[i]->getSprite().getGlobalBounds()))
				{
					lEnemies[i]->OnBulletCollision(fBullets[index]);
					fBullets.erase(fBullets.begin() + index);
					//Passing Bullet (Later on can take consideration of distance travalled to determine hitPoint)
				}
			}
		}
	}
}

void ShootingComponent::OnOutsideScreen(int i)
{
	if (fBullets[i]->getSprite()->getPosition().x < 0
		|| fBullets[i]->getSprite()->getPosition().x > fWindow->getSize().x
		|| fBullets[i]->getSprite()->getPosition().y < 0
		|| fBullets[i]->getSprite()->getPosition().y > fWindow->getSize().y)
	{
		fBullets.erase(fBullets.begin() + i);
	}
}
