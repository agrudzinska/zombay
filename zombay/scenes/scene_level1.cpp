#include "scene_level1.h"
#include "../components/cmp_player_physics.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_ai_steering.h"
#include "system_resources.h"
#include "../game.h"
#include <LevelSystem.h>
#include <iostream>
#include <thread>

using namespace std;
using namespace sf;

static shared_ptr<Entity> player;
static 	vector<shared_ptr<Entity>> enemies;

void Level1Scene::Load() {
  cout << " Scene 1 Load" << endl;
  ls::loadLevelFile("res/arena.txt", 40.0f);

  auto ho = Engine::getWindowSize().y - (ls::getHeight() * 40.f);
  ls::setOffset(Vector2f(0, ho));

  player = create_player();
  //enemies = create_enemies();

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

	  enemy->addComponent<SteeringComponent>(player.get());
	  enemies.push_back(enemy);
  }


  // Add physics colliders to level tiles.
  {
    auto walls = ls::findTiles(ls::WALL);
    for (auto w : walls) {
      auto pos = ls::getTilePosition(w);
      pos += Vector2f(20.f, 20.f); //offset to center
      auto e = makeEntity();
      e->setPosition(pos);
      e->addComponent<PhysicsComponent>(false, Vector2f(40.f, 40.f));
    }
  }

  //Simulate long loading times
  std::this_thread::sleep_for(std::chrono::milliseconds(3000));
  cout << " Scene 1 Load Done" << endl;

  setLoaded(true);
}

void Level1Scene::UnLoad() {
  cout << "Scene 1 Unload" << endl;
  player.reset();
  ls::unload();
  Scene::UnLoad();
}

void Level1Scene::Update(const double& dt) {

  Scene::Update(dt);
}

void Level1Scene::Render() {
  ls::render(Engine::GetWindow());
  Scene::Render();
}
