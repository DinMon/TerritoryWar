#include "PlanningStage.h"
#include <iostream>

#define PADDINGRIGHT 10
#define PADDINGBOTTOM 120

PlanningStage::PlanningStage()
{
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
}

PlanningStage* PlanningStage::fInstance = nullptr;

PlanningStage* PlanningStage::Instance()
{
	if (!fInstance)
	{
		fInstance = new PlanningStage();
	}
	return fInstance;
}

void PlanningStage::Draw(sf::RenderWindow* aWindow)
{
	fPlaySprite.setPosition(sf::Vector2f( aWindow->getSize().x - (fPlaySprite.getGlobalBounds().width + PADDINGRIGHT), aWindow->getSize().y - PADDINGBOTTOM));
	aWindow->draw(fPlaySprite);
}

void PlanningStage::GetInput(sf::RenderWindow* aWindow)
{
	        // Process events
        sf::Event event;
        while (aWindow->pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                aWindow->close();
        }
}

void PlanningStage::Update()
{
}
