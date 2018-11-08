#include "GameplayStage.h"

GameplayStage::GameplayStage(sf::RenderWindow* aWindow)
{
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
		default:
			break;
		}

	}
}

void GameplayStage::Update()
{
}
