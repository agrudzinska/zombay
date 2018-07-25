#pragma once

#include "cmp_physics.h"

class PlayerPhysicsComponent : public Component {
protected:
  float _groundspeed;
  sf::Vector2f _maxVelocity;

public:
  void update(double dt) override;
  void render() override {};
  explicit PlayerPhysicsComponent(Entity* p);

  PlayerPhysicsComponent() = delete;
};
