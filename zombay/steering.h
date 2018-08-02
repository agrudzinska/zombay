#pragma once

#include <engine.h>

// Output from a steering behaviour
struct SteeringOutput
{
	// Direction of travel
	sf::Vector2f direction;
	// Rotation of travel
	float rotation;
};

// Base class for steering behaviour
class StreeringBehaviour
{
public:
	virtual ~StreeringBehaviour() = default;

	// Gets the output from steering behaviour
	virtual SteeringOutput getSteering() const noexcept = 0;
};

// Seek steering behaviour
class Seek : public StreeringBehaviour
{
private:
	Entity* _character;
	Entity* _target;
	float _maxSpeed;
	bool _jump;
	
public:
	Seek() = delete;
	Seek(Entity* character, Entity* target, float maxSpeed, bool jump)
		: _character(character), _target(target), _maxSpeed(maxSpeed), _jump(jump) {}
	SteeringOutput getSteering() const noexcept;
};
