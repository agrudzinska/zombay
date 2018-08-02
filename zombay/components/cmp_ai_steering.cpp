#include "cmp_ai_steering.h"
#include "LevelSystem.h"
#include "../game.h"

using namespace sf;

void SteeringComponent::update(double dt)
{
	if (!_jump)
	{
		auto output = _seek.getSteering();
		move(output.direction * (float)dt);
	}
	else
	{
		auto output = _seek.getSteering();
		if(length(_parent->getPosition() - _player->getPosition()) < 150.0f && 
			length(_parent->getPosition() - _player->getPosition()) > 20.0f)
			move(output.direction * (float)dt * float(2));
		else
		{
			move(output.direction * (float)dt);
		}
	}
	//player dies on contact with enemy zombie
	if (length(_parent->getPosition() - _player->getPosition()) < 20.0f)
	{
		_player->setForDelete();
		Engine::GetActiveScene()->UnLoad();
		Engine::ChangeScene(&gameOver);

	}
	//zombie dies on contact with player's bullets
	for(auto b : Engine::GetActiveScene()->ents.find("bullet"))
			if (length(_parent->getPosition() - b->getPosition()) < 20.0f) {
				_parent->setForDelete();
				b->setForDelete();
			}	
}

SteeringComponent::SteeringComponent(Entity* p, Entity* player, float maxSpeed, bool jump)
	: _player(player), _seek(Seek(p, player, maxSpeed, jump)),
	   Component(p) {}

bool SteeringComponent::validMove(const sf::Vector2f& pos) const
{
	if (pos.x < 0.0f || pos.y > Engine::GetWindow().getSize().x ||
		pos.y < 0.0f || pos.y > Engine::GetWindow().getSize().y ||
		ls::getTileAt(pos) == ls::WALL)
	{
		return false;
	}
	return true;
}

void SteeringComponent::move(const sf::Vector2f& p)
{
	auto new_pos = _parent->getPosition() + p;
	if (validMove(new_pos))
	{
		_parent->setPosition(new_pos);
	}
}

void SteeringComponent::move(float x, float y)
{
	move(Vector2f(x, y));
}