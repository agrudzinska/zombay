#pragma once

#include "engine.h"
#include "SFML\Audio.hpp"

class MenuScene : public Scene {
public:
  MenuScene() = default;
  ~MenuScene() override = default;

  void Load() override;

  void Update(const double& dt) override;

  void UnLoad() override;

private:
	std::shared_ptr<Entity> _btn_Start;
	std::shared_ptr<Entity> _btn_HowTo;
	std::shared_ptr<Entity> _btn_Options;
	std::shared_ptr<Entity> _btn_Quit;
	// All buttons
	std::vector<std::shared_ptr<Entity>> _btns;

	sf::Sound _sound;
	sf::Music _music;
	sf::SoundBuffer _buffer;
	sf::Sound _menusound;
	sf::SoundBuffer _menubuffer;


	float _clickCooldown;
};
