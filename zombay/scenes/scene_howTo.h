#pragma once

#include "engine.h"
#include "SFML\Audio.hpp"

class HowToScene : public Scene {
public:
	HowToScene() = default;
	~HowToScene() override = default;

	void Load() override;

	void Update(const double& dt) override;

	void UnLoad() override;

private:
	std::shared_ptr<Entity> _btn_back;
	sf::Sound _menusound;
	sf::SoundBuffer _menubuffer;
	sf::Sound _sound;
	sf::SoundBuffer _buffer;
	float _clickCooldown;
};
