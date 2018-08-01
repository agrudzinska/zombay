#include "cmp_player_physics.h"
#include "system_physics.h"
#include <LevelSystem.h>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include "engine.h"
#include "../prefabs.h"
#include "cmp_bullet.h"
#include "maths.h"
#include <iostream>
#include "system_resources.h"

using namespace std;
using namespace sf;
using namespace Physics;

bool PlayerPhysicsComponent::isValidMove(Vector2f pos) {
	return (ls::getTileAt(pos) != ls::WALL && ls::getTileAt(pos) != ls::START);
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

  if (direction != Vector2f(0.0, 0.0f))
  {
	  _shootDirection = direction;
	  _shootDirection.y *= -1;
  }
  
  //_shootDirection = Vector2f(Mouse::getPosition());

  if (Keyboard::isKeyPressed(Keyboard::Space)) {
	  auto bullet = Engine::GetActiveScene()->makeEntity();
	  bullet->setPosition(pos+(33.0f * direction));
	  auto s = bullet->addComponent<SpriteComponent>();
	  auto tex = Resources::get<Texture>("bullet.png");
	  s->setTexture(tex);
	  s->getSprite().setTextureRect(sf::IntRect(0, 0, 32, 32));
	  s->getSprite().setOrigin(s->getSprite().getLocalBounds().width / 2 , s->getSprite().getLocalBounds().height / 2 );

	  auto b = bullet->addComponent<BulletComponent>(_parent, _shootDirection, 300.f);
	  b->update(dt);
	  
	  //create_player_bullet(normalize(_shootDirection));
  }


}

PlayerPhysicsComponent::PlayerPhysicsComponent(Entity* p)
    : Component(p) {
  _groundspeed = 160.f;

}

void PlayerPhysicsComponent::move(const Vector2f &p)
{
	auto new_pos = _parent->getPosition() + p;
	_parent->setPosition(new_pos);
}