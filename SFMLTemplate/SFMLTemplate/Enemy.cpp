#include "Enemy.h"
#include "HealthComponent.h"
#include "Bullet.h"
#include "DamageComponent.h"
#include "Player.h"
#include "Map.h"
#include <iostream>
#include <cstdlib> 
#include <thread> 
#include <windows.h> 
#include <stdlib.h>

Enemy::Enemy(sf::RenderWindow* aWindow, Player* aPlayer):Entity("Monster")
{
	fSpeed = 0.0002;
	fIsArrived = false;
	fIsOnTheWay = false;
	fWindow = aWindow;
	fPlayer = aPlayer;
	loadMedia();
	SetupComponents();
	SetupPosition();
    // Set 2d map size.
    fGenerator.setWorldSize({Map::MapLength().x, Map::MapLength().y});
	//Add Collision box
	for (auto &obstacleVec : Map::GetObstructionCoord())
	{
		fGenerator.addCollision({obstacleVec.x, obstacleVec.y});
	}
    // You can use a few heuristics : manhattan, euclidean or octagonal.
    fGenerator.setHeuristic(AStar::Heuristic::euclidean);
    fGenerator.setDiagonalMovement(true);
}

void Enemy::SetupPosition()
{
	int lX, lY;
	lX = rand() % Map::MapLength().x;
	lY = rand() % Map::MapLength().y;
	for (auto &tile : Map::GetObstructionCoord())
	{
		if (tile.x != lX && tile.y != lY)
		{
			break;
		}
	}
	fEntitySprite.setPosition((lX * 32) - 16, (lY * 32) - 16);
}
Enemy::~Enemy()
{
}

void Enemy::Draw()
{
	fWindow->draw(fPolygon);
	fWindow->draw(fEntitySprite);
	fWindow->draw(*(fComponentContainer->GetComponent<HealthComponent>()->GetSprite()));
}

void Enemy::Move()
{
	fIsOnTheWay = true;
	std::cout << "Generate path ... \n";
	sf::Vector2i lGridIndex = Map::GetMapCoordinate(fEntitySprite.getPosition());
    // This method returns vector of coordinates from target to source.
	auto path = fGenerator.findPath({ fPlayer->GetCoordinates().x, fPlayer->GetCoordinates().y }, { lGridIndex.x, lGridIndex.y });

	//fPolygon.setPointCount(path.size());
	//for (int i = 0; i < path.size(); i++)
	//{
	//	fPolygon.setPoint(i,sf::Vector2f((path[i].x * 32), (path[i].y * 32) - 16));
	//	fPolygon.setOutlineColor(sf::Color::Red);
	//	fPolygon.setOutlineThickness(0.1);
	//	fPolygon.setPosition(0, 0);
	//}

    for(auto& coordinate : path) {
        std::cout << coordinate.x << " " << coordinate.y << "\n";
		//Sleep(100);
		//fEntitySprite.setPosition((coordinate.x * 32) - 16, (coordinate.y * 32) - 16);
    }

	for (int i = 0; i < path.size();)
	{
		sf::Vector2f lEnemyCenter = sf::Vector2f(fEntitySprite.getPosition().x, fEntitySprite.getPosition().y);
		sf::Vector2f lTargetTile = sf::Vector2f((path[i].x * 32), (path[i].y * 32) - 16);
		//Cal distance
		float xDist = abs(lTargetTile.x - lEnemyCenter.x);
		float yDist = abs(lTargetTile.y - lEnemyCenter.y);
		float distance = sqrt(xDist*xDist + yDist * yDist);

		if (distance > 1)
		{
			sf::Vector2f lAimDir = (sf::Vector2f)(lTargetTile - lEnemyCenter);
			sf::Vector2f lAimDirNorm = lAimDir / sqrt(pow(lAimDir.x, 2) + pow(lAimDir.y, 2));
			fEntitySprite.move(lAimDirNorm * fSpeed);
		}
		else
		{
			i++;
		}
		fComponentContainer->GetComponent<HealthComponent>()->GetSprite()->setPosition(fEntitySprite.getPosition().x, fEntitySprite.getPosition().y - 2);
	}
	//fEntitySprite.setPosition((path[path.size()-1].x * 32)-16, (path[path.size()-1].y * 32) - 16);
	fIsOnTheWay = false;
	fIsArrived = true;
}

bool Enemy::HasArrived()
{
	return fIsArrived;
}

bool Enemy::OnTheWay()
{
	return fIsOnTheWay;
}


void Enemy::loadMedia()
{
	if (!fEntityTexture.loadFromFile("data/images/zombie.png"))
	{
		throw "Cannot load texture";
	}
	fEntitySprite.setTexture(fEntityTexture);
	fEntitySprite.setScale(sf::Vector2f(0.3, 0.3));
}

void Enemy::SetupComponents()
{
	//Health Component
	fComponentContainer->AddComponent<HealthComponent>(new HealthComponent(50));
	fComponentContainer->GetComponent<HealthComponent>()->GetSprite()->setPosition(fEntitySprite.getPosition().x, fEntitySprite.getPosition().y - 2);
	fComponentContainer->GetComponent<HealthComponent>()->GetSprite()->setRotation(fEntitySprite.getRotation());
}

void Enemy::OnBulletCollision(Bullet* aBullet)
{
	fComponentContainer->GetComponent<HealthComponent>()->Hurt(aBullet->GetComponentContainer()->GetComponent<DamageComponent>()->GetDamage());
}
