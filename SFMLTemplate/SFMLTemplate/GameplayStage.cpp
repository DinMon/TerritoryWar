#include "GameplayStage.h"
#include "ShootingComponent.h"
#include "HealthComponent.h"
#include "Player.h"
#include "Map.h"
#include "Enemy.h"
#include <iostream>

bool flag = false;

GameplayStage::GameplayStage(sf::RenderWindow* aWindow)
{
	fPlayer = new Player(aWindow);
	fMap = new Map(aWindow);
	fHorizontalInput = 0;
	fVerticalInput = 0;
	fWindow = aWindow;
	PopulateEnemies();
	loadMedia();
}


GameplayStage::~GameplayStage()
{
}

void GameplayStage::PopulateEnemies()
{
	fEnemies.push_back(new Enemy(fWindow, fPlayer));
}

void GameplayStage::DrawEnemies()
{
	for (auto &enemy : fEnemies)
	{
		enemy->Draw();
	}
}

void GameplayStage::RemoveDiedEnemies()
{
	for (int i = 0; i < fEnemies.size(); i++)
	{
		if (fEnemies[i]->GetComponentContainer()->GetComponent<HealthComponent>()->GetDied())
		{
			fEnemies.erase(fEnemies.begin() + i);
		}
	}
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
	fMap->DrawMap();
	DrawEnemies();
	fPlayer->Draw();
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
			break;
		case sf::Event::MouseButtonPressed:
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				fPlayer->Shoot(fMouseX, fMouseY);
				break;
			}
			if (event.mouseButton.button == sf::Mouse::Right)
			{
				fPlayer->Reload();
				break;
			}
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
			if (event.key.code == sf::Keyboard::G)
			{
				flag = true;
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
	//sf::Vector2i lGridIndex = Map::GetMapCoordinate(fPlayer->getSprite().getPosition());
	//std::cout << lGridIndex.x << " " << lGridIndex.y << "\n";

	fPlayer->Move(fHorizontalInput, fVerticalInput);
	fPlayer->LookAt(fMouseX, fMouseY);
	fPlayer->Update();
	if (flag)
	{
		fEnemies[0]->Move();
	}
	RemoveDiedEnemies();
}

void GameplayStage::setSprite()
{
}

std::vector<Enemy*> GameplayStage::GetEnemies()
{
	return fEnemies;
}
