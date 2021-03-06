#pragma once
#include "stdafx.h"

class Render;
class Sprite;
class SpriteManager;
class Entity;
class EntityManager;
class Game;

class Character
{
public:
	Character(EntityManager* em, SpriteManager* sm, Sprite* sprite, POINT position, double angle);
	~Character();

	void update();
	void draw(Render* render);
	Entity* getEntity();

	void fireWeapon();

	void setSprite(Sprite* sprite);
	Sprite* getSprite();
	void setPos(POINT position);
	void getPos(POINT& position);
	void setAngle(double angle);
	double getAngle();
	void setVelocity(double x, double y);
	void getVelocity(double& x, double& y);

private:
	Entity* entity_;
	EntityManager* entityManager_;
	SpriteManager* spriteManager_;
};
