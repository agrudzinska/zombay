#include "scene_howTo.h"
#include "../components/cmp_text.h"
#include "../components/cmp_button.h"
#include "../game.h"
#include "../prefabs.h"
#include <SFML/Window/Keyboard.hpp>
#include "system_resources.h"
#include <iostream>

using namespace std;
using namespace sf;

void HowToScene::Load() {
	cout << "HowTo Load \n";

	auto txt = makeEntity();
	auto t = txt->addComponent<TextComponent>("How to play the game");
	t->getText()->setFillColor(Color::White);
	//t->getText()->setOrigin(t->getText()->getLocalBounds().width / 2, t->getText()->getLocalBounds().height / 2);
	txt->setPosition({(float)Engine::GetWindow().getSize().x / 2, (float)Engine::GetWindow().getSize().y / 2 });

	_btn_back.reset();
	_btn_back = create_button("quit.png");
	
	_btn_back->setPosition({
		(float)Engine::GetWindow().getSize().x / 2,
		(float)Engine::GetWindow().getSize().y * float(0.75) });


	Engine::GetWindow().setView(Engine::GetWindow().getDefaultView());

	setLoaded(true);
}

void HowToScene::Update(const double& dt) {

	View view(FloatRect(0, 0, Engine::GetWindow().getSize().x, Engine::GetWindow().getSize().y));
	Engine::GetWindow().setView(view);

	if (_clickCooldown >= 0.0f) _clickCooldown -= dt;

	if (_clickCooldown < 0.0f)
	{
		if (_btn_back->get_components<ButtonComponent>()[0]->isSelected())
		{
			Engine::ChangeScene(&menu);
		}

	}

	Scene::Update(dt);
}

