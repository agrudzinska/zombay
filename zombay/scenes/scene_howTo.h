#pragma once

#include "engine.h"

class HowToScene : public Scene {
public:
	HowToScene() = default;
	~HowToScene() override = default;

	void Load() override;

	void Update(const double& dt) override;

private:
	std::shared_ptr<Entity> _btn_back;

	float _clickCooldown;
};
