#pragma once

#include "engine.h"

class Level1Scene : public Scene {
private:
	std::shared_ptr<Entity> _player;
	sf::Vector2f _view_center;

public:
	void Load() override;

	void UnLoad() override;

	void Update(const double& dt) override;

	void Render() override;
};
