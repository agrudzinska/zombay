#include "scene_menu.h"
#include "../components/cmp_text.h"
#include "../components/cmp_button.h"
#include "../game.h"
#include "../prefabs.h"
#include <SFML/Window/Keyboard.hpp>
#include "system_resources.h"
#include <iostream>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

void MenuScene::Load() {
  cout << "Menu Load \n";
  {
	// Logo
	auto logo = makeEntity();
	auto s = logo->addComponent<SpriteComponent>();
	auto t = Resources::get<Texture>("logo.png");
	s->setTexture(t);
	s->getSprite().setOrigin(s->getSprite().getLocalBounds().width / 2, s->getSprite().getLocalBounds().height / 2);
	logo->setPosition({ (float)Engine::GetWindow().getSize().x / 2, (float)Engine::GetWindow().getSize().y / 4 });

  }

  _btns.clear();

  _btn_Start.reset();
  _btn_Start = create_button("start.png");
  _btns.push_back(_btn_Start);

  _btn_HowTo.reset();
  _btn_HowTo = create_button("how.png");
  _btns.push_back(_btn_HowTo);

  _btn_Options.reset();
  _btn_Options = create_button("options.png");
  _btns.push_back(_btn_Options);

  _btn_Quit.reset();
  _btn_Quit = create_button("quit.png");
  _btns.push_back(_btn_Quit);

  // Set buttons position
  for (int i = 0; i < _btns.size(); i++)
  {
	  if (i == 0)
	  {
		  _btns[i]->setPosition({
			  (float)Engine::GetWindow().getSize().x / 2,
			  (float)Engine::GetWindow().getSize().y / 2 - ((38.0f * (_btns.size() - 1)) / 2)
			  });
	  }
	  else
	  {
		  _btns[i]->setPosition({ _btns[i - 1]->getPosition().x, _btns[i - 1]->getPosition().y + 38.0f });
	  }
  }

  _menubuffer = *(Resources::get<SoundBuffer>("menu_ambience.wav"));
  _menusound.setBuffer(_menubuffer);
  _menusound.setLoop(true);
  _menusound.play();
  Engine::GetWindow().setView(Engine::GetWindow().getDefaultView());

  setLoaded(true);
}

void MenuScene::Update(const double& dt) {

	cout << dt;

	View view(FloatRect(0, 0, Engine::GetWindow().getSize().x, Engine::GetWindow().getSize().y));
	Engine::GetWindow().setView(view);

	_buffer = *(Resources::get<SoundBuffer>("button.wav"));
	_sound.setBuffer(_buffer);

	if (_clickCooldown >= 0.0f) _clickCooldown -= dt;
	
	if (_clickCooldown < 0.0f)
	{
		if (_btn_Start->get_components<ButtonComponent>()[0]->isSelected())
		{
			Engine::ChangeScene(&level1);
			_sound.play();

		}

		if (_btn_HowTo->get_components<ButtonComponent>()[0]->isSelected())
		{
			Engine::ChangeScene(&howTo);
			_sound.play();

		}

		if (_btn_Options->get_components<ButtonComponent>()[0]->isSelected())
		{
			Engine::ChangeScene(&level1);
			_sound.play();

		}

		if (_btn_Quit->get_components<ButtonComponent>()[0]->isSelected())
		{
			Engine::GetWindow().close();
			_sound.play();

		}
	}

	Scene::Update(dt);
}

void MenuScene::UnLoad() {
	cout << "Menu Unload" << endl;
	_menusound.stop();
	Scene::UnLoad();
}
