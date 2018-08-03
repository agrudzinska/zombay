#include "scene_level1.h"
#include "../components/cmp_player_physics.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_ai_steering.h"
#include "../components/cmp_physics.h"
#include "system_resources.h"
#include "../game.h"
#include <array>
#include <LevelSystem.h>
#include <iostream>
#include <thread>

using namespace std;
using namespace sf;

void Level1Scene::Load() {
  cout << " Scene 1 Load" << endl;
  ls::loadLevelFile("res/arena.txt", 40.0f);

  auto ho = Engine::getWindowSize().y - (ls::getHeight() * 40.f);
  ls::setOffset(Vector2f(0, ho));
  
  _player = create_player();
  _view_center = _player->getPosition();

  //Simulate long loading times
  std::this_thread::sleep_for(std::chrono::milliseconds(3000));
  cout << " Scene 1 Load Done" << endl;

  _gamebuffer = *(Resources::get<SoundBuffer>("gameplay2.wav"));
  _gamesound.setBuffer(_gamebuffer);
  _gamesound.setLoop(true);
  _gamesound.play();

  //create timers for spawning enemies
  clock1.restart();
  clock2.restart();
  clock3.restart();

  setLoaded(true);
}

void Level1Scene::UnLoad() {
  cout << "Scene 1 Unload" << endl;
  _player.reset();
  _gamesound.stop();
  ls::unload();
  Scene::UnLoad();
}

void Level1Scene::Update(const double& dt) {
	//Spawn multiple enemies 
	if (clock1.getElapsedTime().asSeconds()>4)
	{
		create_enemies1(_player);
		clock1.restart();
	}
	if (clock2.getElapsedTime().asSeconds()>7)
	{
		create_enemies2(_player);
		clock2.restart();
	}
	if (clock3.getElapsedTime().asSeconds()>10.3)
	{
		create_enemies3(_player);
		clock3.restart();
	}
	//set the camera following the player
	View view(FloatRect(0, 0, Engine::GetWindow().getSize().x / 2, Engine::GetWindow().getSize().y / 2));

	float view_player_distance = sqrt(((_player->getPosition().x - _view_center.x) * (_player->getPosition().x - _view_center.x)) + ((_player->getPosition().y - _view_center.y) * (_player->getPosition().y - _view_center.y)));
	if (view_player_distance > 80.0f)
		_view_center += (_player->getPosition() - _view_center) * (float)dt * 2.3f;
	view.setCenter(_view_center);

	Engine::GetWindow().setView(view);

  Scene::Update(dt);
}

void Level1Scene::Render() {
  ls::render(Engine::GetWindow());
  Scene::Render();
}
