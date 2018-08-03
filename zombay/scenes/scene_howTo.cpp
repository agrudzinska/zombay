#include "scene_howTo.h"
#include "../components/cmp_text.h"
#include "../components/cmp_sprite.h"
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

	auto s = makeEntity();
	auto sp = s->addComponent<SpriteComponent>();
	auto img = Resources::get<Texture>("how.png");
	sp->setTexture(img);
	sp->getSprite().setTextureRect(sf::IntRect(0, 0, 300, 102));
	s->setPosition({ (float)Engine::GetWindow().getSize().x / 3, (float)Engine::GetWindow().getSize().y /6 });

	auto txt = makeEntity();
	auto t = txt->addComponent<TextComponent>("Kill as many zombies as possible before you die.\nUse WASD to move around, press space to shoot.");
	t->getText()->setFillColor(Color::White);
	t->getText()->setPosition({ (float)Engine::GetWindow().getSize().x / 4, (float)Engine::GetWindow().getSize().y / 2 });

	_btn_back.reset();
	_btn_back = create_button("back.png");
	
	_btn_back->setPosition({
		(float)Engine::GetWindow().getSize().x / 2,
		(float)Engine::GetWindow().getSize().y * float(0.75) });

	_menubuffer = *(Resources::get<SoundBuffer>("menu_ambience.wav"));
	_menusound.setBuffer(_menubuffer);
	_menusound.setLoop(true);
	_menusound.play();

	Engine::GetWindow().setView(Engine::GetWindow().getDefaultView());

	setLoaded(true);
}

void HowToScene::Update(const double& dt) {

	View view(FloatRect(0, 0, Engine::GetWindow().getSize().x, Engine::GetWindow().getSize().y));
	Engine::GetWindow().setView(view);

	_buffer = *(Resources::get<SoundBuffer>("back.wav"));
	_sound.setBuffer(_buffer);

	if (_clickCooldown >= 0.0f) _clickCooldown -= dt;

	if (_clickCooldown < 0.0f)
	{
		if (_btn_back->get_components<ButtonComponent>()[0]->isSelected())
		{
			Engine::ChangeScene(&menu);
			_sound.play();
		}

	}

	Scene::Update(dt);
}

void HowToScene::UnLoad() {
	cout << "HowTo Unload" << endl;
	_menusound.stop();
	Scene::UnLoad();
}
