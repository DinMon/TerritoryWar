#include "GameplayStage.h"

GameplayStage::GameplayStage()
{
	loadMedia();
}


GameplayStage::~GameplayStage()
{
}

void GameplayStage::loadMedia()
{
}

GameplayStage* GameplayStage::fInstance = nullptr;

GameplayStage* GameplayStage::Instance()
{
	if (!fInstance)
	{
		fInstance = new GameplayStage();
	}
	return fInstance;
}

void GameplayStage::Draw(sf::RenderWindow* aWindow)
{
}

void GameplayStage::GetInput(sf::RenderWindow* aWindow)
{
}

void GameplayStage::Update()
{
}
