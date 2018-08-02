#pragma once

#include "ecm.h"
#include <SFML\Audio.hpp>

class PlayerPhysicsComponent : public Component {
protected:
  float _groundspeed;
  sf::Vector2f _shootDirection;
  float _shootCooldown;
  Entity* _playerShootCooldownTimerUI;
  std::vector<std::shared_ptr<Entity>> _bullets;
  sf::SoundBuffer _shootBuffer;
  sf::Sound _shootSound;

public:
  bool isValidMove(sf::Vector2f pos);
  void update(double dt) override;
  void render() override {};
  explicit PlayerPhysicsComponent(Entity* p);
  void move(const sf::Vector2f&);
  PlayerPhysicsComponent() = delete;
};
