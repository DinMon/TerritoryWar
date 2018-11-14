#include "Player.h"
#include "HealthComponent.h"
#include "CanContain.h"
#include "ShootingComponent.h"
#include "Weapon.h"
#include "GameplayStage.h"
#include "Enemy.h"
#include "Map.h"
#include <math.h>

#define VELOCITY 0.1
#define PI 3.14159265

bool flag1 = true;

Player::Player(sf::RenderWindow* aWindow): Entity("Player")
{
	fWindow = aWindow;
	fStartClock = true;
	fTimeBeforeHurt = 1;
	fEntitySprite.setOrigin(sf::Vector2f(fEntitySprite.getPosition().x + 
		(fEntitySprite.getGlobalBounds().width / 2), fEntitySprite.getPosition().y + (fEntitySprite.getGlobalBounds().height / 2)));
	fToRotate = true;
	fEntitySprite.setPosition(100, 100);
	loadMedia();
	SetupComponents();
}

Player::~Player()
{
}

void Player::Draw()
{
	fWindow->draw(fEntitySprite);
	fWindow->draw(*(fComponentContainer->GetComponent<HealthComponent>()->GetSprite()));
	fComponentContainer->GetComponent<ShootingComponent>()->DrawBullets();
}

void Player::Update()
{
	fComponentContainer->GetComponent<ShootingComponent>()->UpdateReloadTime();
	fComponentContainer->GetComponent<ShootingComponent>()->UpdateBulletPos();
	if (fClock.getElapsedTime().asSeconds() > fTimeBeforeHurt && !fStartClock)
	{
		fStartClock = true;
	}
	OnEnemyCollision();
}

void Player::Move(int aHorizontal, int aVertical)
{
	RetainInWindow();
	fEntitySprite.setPosition(sf::Vector2f(fEntitySprite.getPosition().x + aHorizontal * VELOCITY, fEntitySprite.getPosition().y + aVertical * VELOCITY));
	//Setting health bar sprite
	fComponentContainer->GetComponent<HealthComponent>()->GetSprite()->setPosition(fEntitySprite.getPosition().x , fEntitySprite.getPosition().y - 2);
	fComponentContainer->GetComponent<HealthComponent>()->GetSprite()->setRotation(fEntitySprite.getRotation() + 90 );
}

void Player::LookAt(int aMouseX, int aMouseY)
{
	double angle = atan2(aMouseY - fEntitySprite.getPosition().y, aMouseX - fEntitySprite.getPosition().x) * 180 / PI;
	fEntitySprite.setRotation(angle);
}

void Player::UpdateAimDirection(int aX, int aY)
{
	sf::Vector2f fPlayerCenter = sf::Vector2f(fEntitySprite.getPosition().x, fEntitySprite.getPosition().y);
	sf::Vector2f lMousePos = sf::Vector2f(aX, aY);
	sf::Vector2f lAimDir = (sf::Vector2f)(lMousePos - fPlayerCenter);
	fAimDirNorm = lAimDir / sqrt(pow(lAimDir.x, 2) + pow(lAimDir.y, 2));
}

sf::Sprite Player::getSprite()
{
	return fEntitySprite;
}

sf::Vector2i Player::GetCoordinates()
{
	sf::Vector2i lGridIndex = Map::GetMapCoordinate(fEntitySprite.getPosition());
	//std::cout << lGridIndex.x << " " << lGridIndex.y << "\n";
	return lGridIndex;
}

void Player::SetupComponents()
{
	//Health Component
	fComponentContainer->AddComponent<HealthComponent>(new HealthComponent(100));
	fComponentContainer->GetComponent<HealthComponent>()->GetSprite()->setPosition(fEntitySprite.getPosition().x, fEntitySprite.getPosition().y - 2);
	fComponentContainer->GetComponent<HealthComponent>()->GetSprite()->setRotation(fEntitySprite.getRotation());

	//CanContain Component
	fComponentContainer->AddComponent<CanContain>(new CanContain());
	fComponentContainer->GetComponent<CanContain>()->AddItem(new Weapon("HandGun", 20, 5, 0.8));
	fCurrentWeapon = (Weapon*)fComponentContainer->GetComponent<CanContain>()->FetchCurrentItem();

	//Shooting Component
	fComponentContainer->AddComponent<ShootingComponent>(new ShootingComponent(this, fWindow));
}

Weapon* Player::GetWeapon()
{
	return fCurrentWeapon;
}

void Player::Shoot(int aX, int aY)
{
	UpdateAimDirection(aX, aY);
	fComponentContainer->GetComponent<ShootingComponent>()->FireWeapon(fAimDirNorm);
}

void Player::Reload()
{
	fComponentContainer->GetComponent<ShootingComponent>()->Reload();
}


void Player::loadMedia()
{
	if (!fHurtSoundBuffer.loadFromFile("data/sounds/hurt.wav"))
	{
		throw "Cannot load texture";
	}
	fHurtSound.setBuffer(fHurtSoundBuffer);
	if (!fEntityTexture.loadFromFile("data/images/PlayerHandGun.png"))
	{
		throw "Cannot load texture";
	}
	fEntitySprite.setTexture(fEntityTexture);
	fEntitySprite.setScale(sf::Vector2f(0.2, 0.2));
}

void Player::RetainFromObstacle()
{

}

void Player::OnEnemyCollision()
{
	for (auto &enemy : GameplayStage::Instance(fWindow)->GetEnemies())
	{
		if (fStartClock)
		{
			if (fEntitySprite.getGlobalBounds().intersects(enemy->getSprite().getGlobalBounds()))
			{
				fComponentContainer->GetComponent<HealthComponent>()->Hurt(10);
				fHurtSound.play();
			}
			fStartClock = false;
			fClock.restart();
		}
	}
	
}

void Player::RetainInWindow()
{
	fToRotate = false;
	if (fEntitySprite.getPosition().x > fWindow->getSize().x - fEntitySprite.getGlobalBounds().width)
	{
		if (fEntitySprite.getRotation() > 45 && fEntitySprite.getRotation() > 225)
		{
			fEntitySprite.setPosition(fEntitySprite.getPosition().x - VELOCITY, fEntitySprite.getPosition().y);
			return;
		}
	}
	if (fEntitySprite.getPosition().x > fWindow->getSize().x)
	{
		if (fEntitySprite.getRotation() > 45 && fEntitySprite.getRotation() < 225)
		{
			fEntitySprite.setPosition(fEntitySprite.getPosition().x - 10, fEntitySprite.getPosition().y);
			return;
		}
	}
	if (fEntitySprite.getPosition().y > fWindow->getSize().y - fEntitySprite.getGlobalBounds().height)
	{
		if (fEntitySprite.getRotation() > 0 && fEntitySprite.getRotation() < 180)
		{
			fEntitySprite.setPosition(fEntitySprite.getPosition().x, fEntitySprite.getPosition().y - 10);
			return;
		}
	}
	if (fEntitySprite.getPosition().y > fWindow->getSize().y)
	{
		if (fEntitySprite.getRotation() > 180 && fEntitySprite.getRotation() < 360)
		{
			fEntitySprite.setPosition(fEntitySprite.getPosition().x, fEntitySprite.getPosition().y - VELOCITY);
			return;
		}
	}
	if (fEntitySprite.getPosition().x < fEntitySprite.getGlobalBounds().width)
	{
		if (fEntitySprite.getRotation() > 45 && fEntitySprite.getRotation() < 225)
		{
			fEntitySprite.setPosition(fEntitySprite.getGlobalBounds().width, fEntitySprite.getPosition().y);
			return;
		}
	}
	if (fEntitySprite.getPosition().x < 0)
	{
		fEntitySprite.setPosition(0, fEntitySprite.getPosition().y);
		return;
	}
	if (fEntitySprite.getPosition().y < fEntitySprite.getGlobalBounds().height)
	{
		if (fEntitySprite.getRotation() > 180 && fEntitySprite.getRotation() < 360)
		{
			fEntitySprite.setPosition(fEntitySprite.getPosition().x, 0);
			return;
		}
	}
	if (fEntitySprite.getPosition().y < 0)
	{
		fEntitySprite.setPosition(fEntitySprite.getPosition().x, 0);
		return;
	}
	fToRotate = true;
}
