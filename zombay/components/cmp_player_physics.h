#pragma once

#include "ecm.h"

class PlayerPhysicsComponent : public Component {
protected:
  float _groundspeed;
  sf::Vector2f _shootDirection;
  float _shootCooldown;
  Entity* _playerShootCooldownTimerUI;
  std::vector<std::shared_ptr<Entity>> _bullets;


public:
  bool isValidMove(sf::Vector2f pos);
  void update(double dt) override;
  void render() override {};
  explicit PlayerPhysicsComponent(Entity* p);
  //bool isValidMove(const sf::Vector2f&);
  void move(const sf::Vector2f&);
  PlayerPhysicsComponent() = delete;
  std::vector<std::shared_ptr<Entity>> getBullets();
};
