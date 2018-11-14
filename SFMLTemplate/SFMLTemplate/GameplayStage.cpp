#include "GameplayStage.h"
#include "ShootingComponent.h"
#include "HealthComponent.h"
#include "Player.h"
#include "Map.h"
#include "Enemy.h"
#include <iostream>
#include <stdlib.h>

bool flag = false;

GameplayStage::GameplayStage(sf::RenderWindow* aWindow): fPool(10)
{
	Reset(aWindow);
}

void GameplayStage::Reset(sf::RenderWindow* aWindow)
{
	fPlayer = new Player(aWindow);
	fMap = new Map(aWindow);
	fIsGameOver = false;
	fHorizontalInput = 0;
	fVerticalInput = 0;
	fWindow = aWindow;
	PopulateEnemies();
	loadMedia();
	fPool.init();
}

GameplayStage::~GameplayStage()
{
}

void GameplayStage::PopulateEnemies()
{
	for (int i = 0; i < 4; i++)
	{
		fEnemies.push_back(new Enemy(fWindow, fPlayer));
	}
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
			if (rand() % 10 > 3)
				fEnemies.push_back(new Enemy(fWindow, fPlayer));
			if (fEnemies.size() == 0)
			{
				PopulateEnemies();
			}
		}
	}
}

void GameplayStage::RemovePlayer()
{
	if (((Entity*)fPlayer)->GetComponentContainer()->GetComponent<HealthComponent>()->GetDied() && !fIsGameOver)
	{
		fIsGameOver = true;
		//Display GameOver
		fClock.restart();
	}
}

void GameplayStage::loadMedia()
{
	if (!fGameOverTexture.loadFromFile("data/images/gameover.png"))
	{
		throw "Cannot load texture";
	}
	fGameOverSprite.setTexture(fGameOverTexture);
	fGameOverSprite.setPosition(0, 0);
	fGameOverSprite.setScale(0.5, 0.5);
	fGameOverSprite.setScale(
    fWindow->getSize().x / fGameOverSprite.getLocalBounds().width, 
    fWindow->getSize().y / fGameOverSprite.getLocalBounds().height);
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
	if (!fIsGameOver)
	{
		fMap->DrawMap();
		DrawEnemies();
		fPlayer->Draw();
	}
	else
	{
		fWindow->draw(fGameOverSprite);
	}
}

void GameplayStage::GetInput()
{
	// Process events
	sf::Event event;
	if (!fIsGameOver)
	{
		while (fWindow->pollEvent(event))
		{
			// Close window: exit
			switch (event.type)
			{
			case sf::Event::Closed:
				fPool.shutdown();
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
}

void GameplayStage::Update()
{
	//sf::Vector2i lGridIndex = Map::GetMapCoordinate(fPlayer->getSprite().getPosition());
	//std::cout << lGridIndex.x << " " << lGridIndex.y << "\n";

	fPlayer->Move(fHorizontalInput, fVerticalInput);
	fPlayer->LookAt(fMouseX, fMouseY);
	fPlayer->Update();
	for (int i = 0; i < fEnemies.size(); i++)
	{

		if (!fEnemies[i]->OnTheWay())
		{
			auto future = fPool.submit(simpleFunction, std::ref(fEnemies), i);
		}
	}
	RemoveDiedEnemies();
	RemovePlayer();

	sf::Time elapsed1 = fClock.getElapsedTime();

	if (elapsed1.asSeconds() > 1 && fIsGameOver)
	{
		fWindow->close();
	}
}

void simpleFunction(std::vector<Enemy*> aEnemies, int aIndex)
{
	aEnemies[aIndex]->Move();
}

void GameplayStage::setSprite()
{
}

std::vector<Enemy*> GameplayStage::GetEnemies()
{
	return fEnemies;
}
