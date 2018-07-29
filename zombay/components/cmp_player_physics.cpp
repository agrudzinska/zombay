#include "cmp_player_physics.h"
#include "system_physics.h"
#include <LevelSystem.h>
#include <SFML/Window/Keyboard.hpp>
#include "cmp_physics.h"
#include "engine.h"
#include "../prefabs.h"
#include <iostream>
#include "system_resources.h"

using namespace std;
using namespace sf;
using namespace Physics;

bool PlayerPhysicsComponent::isValidMove(Vector2f pos) {
	return (ls::getTileAt(pos) != ls::WALL);
}

void PlayerPhysicsComponent::update(double dt) {

  const auto pos = _parent->getPosition();

  auto speed = _groundspeed;

  Vector2f direction = { 0.0f, 0.0f };
  //handle controls
  if (Keyboard::isKeyPressed(Keyboard::Left)) {
	  direction.x -= 1.0f;
  }
  if (Keyboard::isKeyPressed(Keyboard::Right)) {
	  direction.x += 1.0f;
  }
  if (Keyboard::isKeyPressed(Keyboard::Up)) {
	  direction.y -= 1.0f;
  }
  if (Keyboard::isKeyPressed(Keyboard::Down)) {
	  direction.y += 1.0f;
  }

  if (isValidMove(pos+direction))
  {
	  move(normalize(direction) * _groundspeed * (float)dt);
  }

}

PlayerPhysicsComponent::PlayerPhysicsComponent(Entity* p)
    : Component(p) {
  _maxVelocity = Vector2f(200.f, 400.f);
  _groundspeed = 160.f;

}

void PlayerPhysicsComponent::move(const Vector2f &p)
{
	auto new_pos = _parent->getPosition() + p;
	_parent->setPosition(new_pos);
}