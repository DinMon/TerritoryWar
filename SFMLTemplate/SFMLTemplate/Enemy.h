#pragma once
#include "Entity.h"
#include "AStar.hpp"

class Bullet;
class Player;

class Enemy :
	public Entity
{
public:
	Enemy(sf::RenderWindow*, Player*);
	void SetupPosition();
	~Enemy();
	void Draw();
	void Move();
	bool HasArrived();
	bool OnTheWay();

	// Inherited via Entity
	virtual void loadMedia() override;
	void OnBulletCollision(Bullet*);
private:
	bool fIsArrived;
	bool fIsOnTheWay;
	void SetupComponents();
	sf::RenderWindow* fWindow;
	sf::ConvexShape fPolygon;
	Player* fPlayer;
	AStar::Generator fGenerator;
	float fSpeed;
	int fCurrentIndex;
};

