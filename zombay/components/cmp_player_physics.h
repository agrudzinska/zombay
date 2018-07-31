#pragma once

#include "ecm.h"

class PlayerPhysicsComponent : public Component {
protected:
  float _groundspeed;

public:
  bool isValidMove(sf::Vector2f pos);
  void update(double dt) override;
  void render() override {};
  explicit PlayerPhysicsComponent(Entity* p);
  //bool isValidMove(const sf::Vector2f&);
  void move(const sf::Vector2f&);
  PlayerPhysicsComponent() = delete;
};
