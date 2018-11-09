#include "GameplayStage.h"
#include "Player.h"

GameplayStage::GameplayStage(sf::RenderWindow* aWindow)
{
	fPlayer = new Player();
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
	fWindow->draw(fPlayer->getSprite());
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

void GameplayStage::Update()
{
	fPlayer->Move(fHorizontalInput, fVerticalInput, fWindow);
}

void GameplayStage::setSprite()
{
}
