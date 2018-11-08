#include "PlanningStage.h"
#include "StageManager.h"
#include <iostream>

#define PADDINGRIGHT 10
#define PADDINGBOTTOM 100

PlanningStage::PlanningStage(sf::RenderWindow* aWindow)
{
	fWindow = aWindow;
	loadMedia();
}

PlanningStage::~PlanningStage()
{
}

void PlanningStage::loadMedia()
{
	if (!fPlayTexture.loadFromFile("data/images/PlayButton.png"))
	{
		throw "Cannot load texture";
	}
	fPlaySprite.setTexture(fPlayTexture);
	fPlaySprite.setScale(sf::Vector2f(0.15, 0.15));
	setSprite();
}

void PlanningStage::setSprite()
{
	fPlaySprite.setPosition(sf::Vector2f( fWindow->getSize().x - (fPlaySprite.getGlobalBounds().width + PADDINGRIGHT), fWindow->getSize().y - PADDINGBOTTOM));
}

void PlanningStage::NextStage()
{
	StageManager::Instance()->SetState(StageEnum::Gameplay);
}

PlanningStage* PlanningStage::fInstance = nullptr;

PlanningStage* PlanningStage::Instance(sf::RenderWindow* aWindow)
{
	if (!fInstance)
	{
		fInstance = new PlanningStage(aWindow);
	}
	return fInstance;
}

void PlanningStage::Draw()
{
	fWindow->draw(fPlaySprite);
}

void PlanningStage::GetInput()
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
				if (fPlaySprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
				{
					NextStage();
				}
			}
		default:
			break;
		}

	}
}

void PlanningStage::Update()
{
}
