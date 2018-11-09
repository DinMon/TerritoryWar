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
		case sf::Event::MouseMoved:
			if (!fPlayer->getSprite().getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y))
			{
				fMouseX = event.mouseMove.x;
				fMouseY = event.mouseMove.y;
			}
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				break;
			}
			break;
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::W)
			{
				fVerticalInput = -1;
				break;
			}
			if (event.key.code == sf::Keyboard::S)
			{
				fVerticalInput = 1;
				break;
			}
			if (event.key.code == sf::Keyboard::A)
			{
				fHorizontalInput = -1;
				break;
			}
			if (event.key.code == sf::Keyboard::D)
			{
				fHorizontalInput = 1;
				break;
			}
		case sf::Event::KeyReleased:
			if (event.key.code == sf::Keyboard::W)
			{
				fVerticalInput = 0;
				break;
			}
			if (event.key.code == sf::Keyboard::S)
			{
				fVerticalInput = 0;
				break;
			}
			if (event.key.code == sf::Keyboard::A)
			{
				fHorizontalInput = 0;
				break;
			}
			if (event.key.code == sf::Keyboard::D)
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
	fPlayer->LookAt(fMouseX, fMouseY);
}

void GameplayStage::setSprite()
{
}
