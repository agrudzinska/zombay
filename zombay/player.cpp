#include "player.h"
using namespace sf;
using namespace std;

const Keyboard::Key controls[4] = {
	Keyboard::A,	//Player left
	Keyboard::S,	//Player down
	Keyboard::W,	//Player up
	Keyboard::D		//Player right
};

void Player::update(double dt) {
	Vector2f direction = { 0, 0 };

	if (Keyboard::isKeyPressed(controls[3]))
	{
		direction.x += 1.0f;
	}
	if (Keyboard::isKeyPressed(controls[0]))
	{
		direction.x -= 1.0f;
	}
	if (Keyboard::isKeyPressed(controls[1]))
	{
		direction.y += 1.0f;
	}
	if (Keyboard::isKeyPressed(controls[2]))
	{
		direction.y -= 1.0f;
	}
	Entity::move((float)dt*direction*_speed);

	Entity::update(dt);
}

Player::Player()
	: _speed(200.0f), Entity(make_unique<CircleShape>(25.f)){
	_shape->setFillColor(Color::Magenta);
	_shape->setOrigin(Vector2f(25.f, 25.f));
}

void Player::render(RenderWindow &window) const {
	window.draw(*_shape);
}