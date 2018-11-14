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

Enemy::Enemy(sf::RenderWindow* aWindow, Player* aPlayer):Entity("Monster")
{
	fSpeed = 0.01;
	fIsArrived = false;
	fIsOnTheWay = false;
	fWindow = aWindow;
	fPlayer = aPlayer;
	loadMedia();
	SetupComponents();
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

Enemy::~Enemy()
{
}

void Enemy::Draw()
{
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

    for(auto& coordinate : path) {
        std::cout << coordinate.x << " " << coordinate.y << "\n";
		Sleep(100);
		fEntitySprite.setPosition((coordinate.x * 32) - 16, (coordinate.y * 32) - 16);
    }

	//for (int i = 0; i < path.size();)
	//{
	//	sf::Vector2f lEnemyCenter = sf::Vector2f(fEntitySprite.getPosition().x, fEntitySprite.getPosition().y);
	//	sf::Vector2f lTargetTile = sf::Vector2f((path[i].x * 32), (path[i].y * 32) - 16);
	//	//Cal distance
	//	float xDist = abs(lTargetTile.x - lEnemyCenter.x);
	//	float yDist = abs(lTargetTile.y - lEnemyCenter.y);
	//	float distance = sqrt(xDist*xDist + yDist * yDist);

	//	if (distance > 1)
	//	{
	//		sf::Vector2f lAimDir = (sf::Vector2f)(lTargetTile - lEnemyCenter);
	//		sf::Vector2f lAimDirNorm = lAimDir / sqrt(pow(lAimDir.x, 2) + pow(lAimDir.y, 2));
	//		fEntitySprite.move(lAimDirNorm * fSpeed);
	//	}
	//	else
	//	{
	//		i++;
	//	}
	//}
	//fEntitySprite.setPosition((path[path.size()-1].x * 32)-16, (path[path.size()-1].y * 32) - 16);
	
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
	fEntitySprite.setPosition(200, 200);
	fEntitySprite.setScale(sf::Vector2f(0.4, 0.4));
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
