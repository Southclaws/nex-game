/*
*/

#include "stdafx.h"

#include "Entity.h"
#include "Render.h"
#include "Sprite.h"


Entity::Entity(Sprite* sprite, POINT position, double angle, double velx, double vely, int ttl)
{
	sprite_ = sprite;
	position_ = position;
	angle_ = angle;
	velX_ = velx;
	velY_ = vely;
	timeCreated_ = GetTickCount();
	timeToLive_ = ttl;
}

Entity::~Entity()
{
	//
}

void Entity::update()
{
	if (position_.x + velX_ - 8 < 0 || position_.x + velX_ + 8 > SCREEN_SIZE_X)
		velX_ = 0;

	if (position_.y + velY_ - 8 < 0 || position_.y + velY_ + 8 > SCREEN_SIZE_Y)
		velY_ = 0;

	// Additional collision checks go here

	/*

	isColliding(Entity* entity)



	// Get the tile colliding with xy
	Tile tile;
	int tilex, tiley;

	Tile tilemap[20 * 15];
	GameLevel->getTileMap(GameLevel->getActiveMap())->GetTiles(tilemap);

	// replace with loop for all entities
	// copied from the old tile collision code
	for (int i = 0; i < 20 * 15; ++i) // replace with area based loop for closest 8 tiles
	{
		tile = tilemap[i];

		COLLISION_TYPE tile_coltype = tile.getSprite()->getColType();

		if (tile_coltype == NOCOLL)
			continue;

		tile.getPos(tilex, tiley);

		if (tile_coltype == CIRCLE)
		{
			if (sqrt(pow((pos.x + offset.x) - tilex, 2) + pow((pos.y + offset.y) - tiley, 2)) < 8.0)
			{
				// todo: set velocity to the arctan from the collided to the collider
				// maybe add a bounce for non-static collided entities (vel gets set for both entities)
				velX_ = 0;
				velY_ = 0;
			}
		}
	}
	*/

	position_.x += (int)round(velX_);
	position_.y += (int)round(velY_);

	return;
}

void Entity::draw(Render* render)
{
	if (angle_ == 0.0)
		sprite_->DrawAt(render, position_.x, position_.y);

	else
		sprite_->DrawAt(render, position_.x, position_.y, angle_);
}


void Entity::setSprite(Sprite* sprite)
{
	sprite_ = sprite;
}

Sprite* Entity::getSprite()
{
	return sprite_;
}

void Entity::setPos(POINT position)
{
	position_ = position;
}

void Entity::getPos(POINT& position)
{
	position = position_;
}

void Entity::setAngle(double angle)
{
	angle_ = angle;
}

double Entity::getAngle()
{
	return angle_;
}

void Entity::setVelocity(double x, double y)
{
	velX_ = x;
	velY_ = y;
}

void Entity::getVelocity(double& x, double& y)
{
	x = velX_;
	y = velY_;
}

unsigned long Entity::getTimeCreated()
{
	return timeCreated_;
}

unsigned long Entity::getTimeToLive()
{
	return timeToLive_;
}

bool Entity::isCollidingWith(Entity* entity)
{
	if (sprite_->getColType() == NOCOLL)
		return false;

	POINT against;
	entity->getPos(against);

	if (sprite_->getColType() == SQUARE)
	{
		if (entity->getSprite()->getColType() == SQUARE)
		{
			//
		}

		if (entity->getSprite()->getColType() == CIRCLE)
		{
			//
		}
	}

	if (sprite_->getColType() == CIRCLE)
	{
		if (entity->getSprite()->getColType() == SQUARE)
		{
			//
		}

		if (entity->getSprite()->getColType() == CIRCLE)
		{
			//
		}
	}

	return false;
}