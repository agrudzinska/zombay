#pragma once

#include <ecm.h>
#include "../steering.h"

class SteeringComponent : public Component
{
protected:
	Seek _seek;
	Entity* _player;
	std::vector<std::shared_ptr<Entity>> _bullets;
	float _maxSpeed;
	bool validMove(const sf::Vector2f&) const;
	bool _jump;

public:
	void update(double) override;
	void move(const sf::Vector2f&);
	void move(float x, float y);
	void render() override {}
	explicit SteeringComponent(Entity* p, Entity* player, float maxSpeed, bool jump);
	SteeringComponent() = delete;
};