#include "cmp_player_physics.h"
#include "system_physics.h"
#include <LevelSystem.h>
#include <SFML/Window/Keyboard.hpp>
#include "cmp_physics.h"
#include "engine.h"
#include "../prefabs.h"
#include "system_resources.h"

using namespace std;
using namespace sf;
using namespace Physics;

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
  move((float)dt*direction*_groundspeed);
  //if(_parent->get_components<PhysicsComponent>()[0]->getVelocity().x < _maxVelocity.x)
  //_parent->get_components<PhysicsComponent>()[0]->setVelocity(Vector2f(normalize(direction) * speed));

}

PlayerPhysicsComponent::PlayerPhysicsComponent(Entity* p)
    : Component(p) {
  _maxVelocity = Vector2f(200.f, 400.f);
  _groundspeed = 30.f;

}