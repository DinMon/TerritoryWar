#include "Player.h"
#include <math.h>

#define VELOCITY 0.1
#define PI 3.14159265

Player::Player()
{
	fPlayerSprite.setOrigin(sf::Vector2f(fPlayerSprite.getPosition().x + 
		(fPlayerSprite.getGlobalBounds().width / 2), fPlayerSprite.getPosition().y + (fPlayerSprite.getGlobalBounds().height / 2)));
	fToRotate = true;
	fPlayerSprite.setPosition(100, 100);
	loadMedia();
}


Player::~Player()
{
}

void Player::Move(int aHorizontal, int aVertical, sf::RenderWindow* aWindow)
{
	RetainInWindow(aWindow);
	fPlayerSprite.setPosition(sf::Vector2f(fPlayerSprite.getPosition().x + aHorizontal * VELOCITY, fPlayerSprite.getPosition().y + aVertical * VELOCITY));
}

void Player::LookAt(int aMouseX, int aMouseY)
{
	double angle = atan2(aMouseY - fPlayerSprite.getPosition().y, aMouseX - fPlayerSprite.getPosition().x) * 180 / PI;
	fPlayerSprite.setRotation(angle);
}

sf::Sprite Player::getSprite()
{
	return fPlayerSprite;
}

void Player::loadMedia()
{
	if (!fPlayerTexture.loadFromFile("data/images/PlayerHandGun.png"))
	{
		throw "Cannot load texture";
	}
	fPlayerSprite.setTexture(fPlayerTexture);
	fPlayerSprite.setScale(sf::Vector2f(0.2, 0.2));
}

void Player::RetainInWindow(sf::RenderWindow* aWindow)
{
	fToRotate = false;
	if (fPlayerSprite.getPosition().x > aWindow->getSize().x - fPlayerSprite.getGlobalBounds().width)
	{
		if (fPlayerSprite.getRotation() > 45 && fPlayerSprite.getRotation() > 225)
		{
			fPlayerSprite.setPosition(fPlayerSprite.getPosition().x - VELOCITY, fPlayerSprite.getPosition().y);
			return;
		}
	}
	if (fPlayerSprite.getPosition().x > aWindow->getSize().x)
	{
		if (fPlayerSprite.getRotation() > 45 && fPlayerSprite.getRotation() < 225)
		{
			fPlayerSprite.setPosition(fPlayerSprite.getPosition().x - 10, fPlayerSprite.getPosition().y);
			return;
		}
	}
	if (fPlayerSprite.getPosition().y > aWindow->getSize().y - fPlayerSprite.getGlobalBounds().height)
	{
		if (fPlayerSprite.getRotation() > 0 && fPlayerSprite.getRotation() < 180)
		{
			fPlayerSprite.setPosition(fPlayerSprite.getPosition().x, fPlayerSprite.getPosition().y - 10);
			return;
		}
	}
	if (fPlayerSprite.getPosition().y > aWindow->getSize().y)
	{
		if (fPlayerSprite.getRotation() > 180 && fPlayerSprite.getRotation() < 360)
		{
			fPlayerSprite.setPosition(fPlayerSprite.getPosition().x, fPlayerSprite.getPosition().y - VELOCITY);
			return;
		}
	}
	if (fPlayerSprite.getPosition().x < fPlayerSprite.getGlobalBounds().width)
	{
		if (fPlayerSprite.getRotation() > 45 && fPlayerSprite.getRotation() < 225)
		{
			fPlayerSprite.setPosition(fPlayerSprite.getGlobalBounds().width, fPlayerSprite.getPosition().y);
			return;
		}
	}
	if (fPlayerSprite.getPosition().x < 0)
	{
		fPlayerSprite.setPosition(0, fPlayerSprite.getPosition().y);
		return;
	}
	if (fPlayerSprite.getPosition().y < fPlayerSprite.getGlobalBounds().height)
	{
		if (fPlayerSprite.getRotation() > 180 && fPlayerSprite.getRotation() < 360)
		{
			fPlayerSprite.setPosition(fPlayerSprite.getPosition().x, 0);
			return;
		}
	}
	if (fPlayerSprite.getPosition().y < 0)
	{
		fPlayerSprite.setPosition(fPlayerSprite.getPosition().x, 0);
		return;
	}
	fToRotate = true;
}
