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
}

void GameplayStage::Update()
{
}
