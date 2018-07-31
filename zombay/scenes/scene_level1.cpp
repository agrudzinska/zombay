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
  //enemies = create_enemies();

  /*/PUT THIS IN UPDATE, KEEP THE PLAYER REFERENCE FOR AI
  vector<shared_ptr<Entity>> enemies;
  auto spawn_tiles = ls::findTiles(ls::START);
  for (auto t : spawn_tiles)
  {
	  auto enemy = Engine::GetActiveScene()->makeEntity();
	  enemy->setPosition(ls::getTilePosition(t) + Vector2f(ls::getTileSize() / 2, ls::getTileSize() / 2));

	  auto s = enemy->addComponent<SpriteComponent>();
	  auto tex = Resources::get<Texture>("zombay.png");
	  s->setTexture(tex);
	  s->getSprite().setTextureRect(sf::IntRect(0, 0, 32, 32));
	  s->getSprite().setOrigin(s->getSprite().getLocalBounds().width / 2, s->getSprite().getLocalBounds().height / 2);
	  //enemy->addComponent<PhysicsComponent>(true, Vector2f(s->getSprite().getLocalBounds().width - 8, s->getSprite().getLocalBounds().height));
	  enemy->addComponent<SteeringComponent>(_player.get());
	  enemies.push_back(enemy);
  }
  */

  _view_center = _player->getPosition();


  // Add physics colliders to level tiles.
  {
    auto walls = ls::findTiles(ls::WALL);
    for (auto w : walls) {
      auto pos = ls::getTilePosition(w);
      pos += Vector2f(20.f, 20.f); //offset to center
      auto e = makeEntity();
      e->setPosition(pos);
      e->addComponent<PhysicsComponent>(false, Vector2f(ls::getTileSize(), ls::getTileSize()));
    }
  }

  //Simulate long loading times
  std::this_thread::sleep_for(std::chrono::milliseconds(3000));
  cout << " Scene 1 Load Done" << endl;

  _gamebuffer = *(Resources::get<SoundBuffer>("gameplay2.wav"));
  _gamesound.setBuffer(_gamebuffer);
  _gamesound.setLoop(true);
  _gamesound.play();

  setLoaded(true);
}

void Level1Scene::UnLoad() {
  cout << "Scene 1 Unload" << endl;
  _player.reset();
  ls::unload();
  Scene::UnLoad();
}

void Level1Scene::Update(const double& dt) {

	//PUT THIS IN UPDATE, KEEP THE PLAYER REFERENCE FOR AI
	if (dt > 0.006)
	{
		auto spawn_tiles = ls::findTiles(ls::START);
		for (auto t : spawn_tiles)
		{
			auto enemy = Engine::GetActiveScene()->makeEntity();
			enemy->setPosition(ls::getTilePosition(t) + Vector2f(ls::getTileSize() / 2, ls::getTileSize() / 2));

			auto s = enemy->addComponent<SpriteComponent>();
			auto tex = Resources::get<Texture>("zombay.png");
			s->setTexture(tex);
			s->getSprite().setTextureRect(sf::IntRect(0, 0, 32, 32));
			s->getSprite().setOrigin(s->getSprite().getLocalBounds().width / 2, s->getSprite().getLocalBounds().height / 2);
			//enemy->addComponent<PhysicsComponent>(true, Vector2f(s->getSprite().getLocalBounds().width - 8, s->getSprite().getLocalBounds().height));
			enemy->addComponent<SteeringComponent>(_player.get());
			//enemies.push_back(enemy);
			_enemies.front() = enemy;
		}
	}
	View view(FloatRect(0, 0, Engine::GetWindow().getSize().x, Engine::GetWindow().getSize().y));

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
