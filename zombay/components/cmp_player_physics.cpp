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
  if (Keyboard::isKeyPressed(Keyboard::A)) {
	  direction.x -= 1.0f;
  }
  if (Keyboard::isKeyPressed(Keyboard::D)) {
	  direction.x += 1.0f;
  }
  if (Keyboard::isKeyPressed(Keyboard::W)) {
	  direction.y -= 1.0f;
  }
  if (Keyboard::isKeyPressed(Keyboard::S)) {
	  direction.y += 1.0f;
  }

  if (isValidMove(pos+direction))
  {
	  move(normalize(direction) * _groundspeed * (float)dt);
  }

  _shootBuffer = *(Resources::get<SoundBuffer>("shot.wav"));
  _shootSound.setBuffer(_shootBuffer);
  _shootSound.setVolume(100);

  /*if (direction != Vector2f(0.0, 0.0f))
  {
	  _shootDirection = direction;
	  _shootDirection.y *= -1;
  }*/
	Vector2f mousePos = Vector2f(Mouse::getPosition(Engine::GetWindow()));
	//Vector2f currPos = pos + (33.0f * direction);
	_shootDirection = mousePos - pos;
  if (Keyboard::isKeyPressed(Keyboard::Space) && _shootCooldown <= 0.0f) {
	  
	  auto bullet = Engine::GetActiveScene()->makeEntity();
	  bullet->addTag("bullet");
	  bullet->setPosition(pos);
	  //bullet->setPosition(pos+(33.0f * direction));
	  auto s = bullet->addComponent<SpriteComponent>();
	  auto tex = Resources::get<Texture>("bullet.png");
	  s->setTexture(tex);
	  s->getSprite().setTextureRect(sf::IntRect(0, 0, 32, 32));
	  s->getSprite().setOrigin(s->getSprite().getLocalBounds().width / 2 , s->getSprite().getLocalBounds().height / 2 );

	  auto p = bullet->addComponent<PhysicsComponent>(true, Vector2f(1.0f, 1.0f));
	  p->getBody()->SetBullet(true);
	  
	  
	  _shootDirection.y *= -1;


	  auto b = bullet->addComponent<BulletComponent>(_parent, normalize(_shootDirection), 600.f);
	  _bullets.push_back(bullet);
	  b->update(dt);
	  _shootSound.play();
	  _shootCooldown = 0.4f;
  }
  if (_shootCooldown > 0.0f) _shootCooldown -= dt;


}


PlayerPhysicsComponent::PlayerPhysicsComponent(Entity* p)
    : Component(p) {
  _groundspeed = 160.f;
  _shootCooldown = 0.0f;
  _shootDirection = { 1.0f, 0.0f };

}

void PlayerPhysicsComponent::move(const Vector2f &p)
{
	auto new_pos = _parent->getPosition() + p;
	_parent->setPosition(new_pos);
}