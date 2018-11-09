#include "Player.h"

#define VELOCITY 0.1

Player::Player()
{
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
	if (fPlayerSprite.getPosition().x > aWindow->getSize().x - fPlayerSprite.getGlobalBounds().width)
	{
		fPlayerSprite.setPosition(fPlayerSprite.getPosition().x - VELOCITY, fPlayerSprite.getPosition().y);
	}
	if (fPlayerSprite.getPosition().y > aWindow->getSize().y - fPlayerSprite.getGlobalBounds().height)
	{
		fPlayerSprite.setPosition(fPlayerSprite.getPosition().x, fPlayerSprite.getPosition().y - VELOCITY);
	}
	if (fPlayerSprite.getPosition().x < 0)
	{
		fPlayerSprite.setPosition(0, fPlayerSprite.getPosition().y);
	}
	if (fPlayerSprite.getPosition().y < 0)
	{
		fPlayerSprite.setPosition(fPlayerSprite.getPosition().x, 0);
	}
}
