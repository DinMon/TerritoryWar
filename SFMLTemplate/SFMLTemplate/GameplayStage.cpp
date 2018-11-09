#include "GameplayStage.h"

#define VELOCITY 0.1

GameplayStage::GameplayStage(sf::RenderWindow* aWindow)
{
	fHorizontalInput = 0;
	fVerticalInput = 0;
	fWindow = aWindow;
	loadMedia();
}


GameplayStage::~GameplayStage()
{
}

void GameplayStage::loadMedia()
{
	if (!fPlayerTexture.loadFromFile("data/images/PlayerHandGun.png"))
	{
		throw "Cannot load texture";
	}
	fPlayerSprite.setTexture(fPlayerTexture);
	fPlayerSprite.setScale(sf::Vector2f(0.2, 0.2));
	//setSprite();
}

GameplayStage* GameplayStage::fInstance = nullptr;

GameplayStage* GameplayStage::Instance(sf::RenderWindow* aWindow)
{
	if (!fInstance)
	{
		fInstance = new GameplayStage(aWindow);
	}
	return fInstance;
}

void GameplayStage::Draw()
{
	fWindow->draw(fPlayerSprite);
}

void GameplayStage::GetInput()
{
	// Process events
	sf::Event event;
	while (fWindow->pollEvent(event))
	{
		// Close window: exit
		switch (event.type)
		{
		case sf::Event::Closed:
			fWindow->close();
			break;
		case sf::Event::MouseButtonPressed:
			if (event.mouseButton.button == sf::Mouse::Left)
			{
			}
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Up)
			{
				fVerticalInput = -1;
				break;
			}
			if (event.key.code == sf::Keyboard::Down)
			{
				fVerticalInput = 1;
				break;
			}
			if (event.key.code == sf::Keyboard::Left)
			{
				fHorizontalInput = -1;
				break;
			}
			if (event.key.code == sf::Keyboard::Right)
			{
				fHorizontalInput = 1;
				break;
			}
		case sf::Event::KeyReleased:
			if (event.key.code == sf::Keyboard::Up)
			{
				fVerticalInput = 0;
				break;
			}
			if (event.key.code == sf::Keyboard::Down)
			{
				fVerticalInput = 0;
				break;
			}
			if (event.key.code == sf::Keyboard::Left)
			{
				fHorizontalInput = 0;
				break;
			}
			if (event.key.code == sf::Keyboard::Right)
			{
				fHorizontalInput = 0;
				break;
			}
		default:
			break;
		}

	}
}

void GameplayStage::Move()
{
	RetainInWindow();
	fPlayerSprite.setPosition(sf::Vector2f(fPlayerSprite.getPosition().x + fHorizontalInput * VELOCITY, fPlayerSprite.getPosition().y + fVerticalInput * VELOCITY));
}

void GameplayStage::RetainInWindow()
{
	if (fPlayerSprite.getPosition().x > fWindow->getSize().x - fPlayerSprite.getGlobalBounds().width)
	{
		fPlayerSprite.setPosition(fPlayerSprite.getPosition().x - VELOCITY, fPlayerSprite.getPosition().y);
	}
	if (fPlayerSprite.getPosition().y > fWindow->getSize().y - fPlayerSprite.getGlobalBounds().height)
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

void GameplayStage::Update()
{
	Move();
}

void GameplayStage::setSprite()
{
}
