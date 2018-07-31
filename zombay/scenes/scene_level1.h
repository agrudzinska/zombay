#pragma once

#include "engine.h"
#include "SFML\Audio.hpp"
#include <array>

class Level1Scene : public Scene {
private:
	std::shared_ptr<Entity> _player;
	sf::Vector2f _view_center;
	sf::SoundBuffer _gamebuffer;
	sf::Sound _gamesound;
	std::array<std::shared_ptr<Entity>, 10> _enemies;



public:
	void Load() override;

	void UnLoad() override;

	void Update(const double& dt) override;

	void Render() override;
};
