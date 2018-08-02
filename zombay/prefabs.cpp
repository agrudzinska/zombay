#include "prefabs.h"
#include "engine.h"
#include "game.h"
#include <LevelSystem.h>
#include <system_resources.h>
#include "components/cmp_text.h"
#include "components/cmp_sprite.h"
#include "components/cmp_button.h"
#include "components/cmp_player_physics.h"
#include "components\cmp_actor_movement.h"
#include "components\cmp_physics.h"
#include "components\cmp_ai_steering.h"
#include "components\cmp_bullet.h"

using namespace std;
using namespace sf;

shared_ptr<Entity> create_player()
{
	auto player = Engine::GetActiveScene()->makeEntity();
	player->setPosition(Vector2f(game_width /2, game_heigth / 2));
	auto s = player->addComponent<SpriteComponent>();
	auto tex = Resources::get<Texture>("char2.png");
	s->setTexture(tex);
	s->getSprite().setTextureRect(sf::IntRect(0, 0, 32, 32));
	s->getSprite().setOrigin(s->getSprite().getLocalBounds().width / 2, s->getSprite().getLocalBounds().height / 2);
	//player->addComponent<PhysicsComponent>(true, Vector2f(s->getSprite().getLocalBounds().width - 8, s->getSprite().getLocalBounds().height));
	player->addComponent<PlayerPhysicsComponent>();

	return player;
	
}

vector<std::shared_ptr<Entity>> create_enemies1(shared_ptr<Entity> p)
{
	vector<std::shared_ptr<Entity>> enemies;
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

		enemy->addComponent<SteeringComponent>(p.get(), 100.f, false);
		enemies.push_back(enemy);
	}
	return enemies;
}

vector<std::shared_ptr<Entity>> create_enemies2(shared_ptr<Entity> p)
{
	vector<std::shared_ptr<Entity>> enemies;
	auto spawn_tiles = ls::findTiles(ls::START);
	for (auto t : spawn_tiles)
	{

		auto enemy = Engine::GetActiveScene()->makeEntity();
		enemy->setPosition(ls::getTilePosition(t) + Vector2f(ls::getTileSize() / 2, ls::getTileSize() / 2));

		auto s = enemy->addComponent<SpriteComponent>();
		auto tex = Resources::get<Texture>("zombay2.png");
		s->setTexture(tex);
		s->getSprite().setTextureRect(sf::IntRect(0, 0, 32, 32));
		s->getSprite().setOrigin(s->getSprite().getLocalBounds().width / 2, s->getSprite().getLocalBounds().height / 2);

		enemy->addComponent<SteeringComponent>(p.get(), 80.f, true);
		enemies.push_back(enemy);
	}
	return enemies;
}

vector<std::shared_ptr<Entity>> create_enemies3(shared_ptr<Entity> p)
{
	vector<std::shared_ptr<Entity>> enemies;
	auto spawn_tiles = ls::findTiles(ls::START);
	for (auto t : spawn_tiles)
	{

		auto enemy = Engine::GetActiveScene()->makeEntity();
		enemy->setPosition(ls::getTilePosition(t) + Vector2f(ls::getTileSize() / 2, ls::getTileSize() / 2));

		auto s = enemy->addComponent<SpriteComponent>();
		auto tex = Resources::get<Texture>("zombay3.png");
		s->setTexture(tex);
		s->getSprite().setTextureRect(sf::IntRect(0, 0, 32, 32));
		s->getSprite().setOrigin(s->getSprite().getLocalBounds().width / 2, s->getSprite().getLocalBounds().height / 2);

		enemy->addComponent<SteeringComponent>(p.get(), 60.f, true);
		enemies.push_back(enemy);
	}
	return enemies;
}

shared_ptr<Entity> create_button(string path)
{
	auto button = Engine::GetActiveScene()->makeEntity();

	auto s = button->addComponent<ShapeComponent>();
	s->setShape<RectangleShape>(Vector2f(300.0f, 34.0f));
	s->getShape().setOrigin(s->getShape().getLocalBounds().width / 2, s->getShape().getLocalBounds().height / 2);

	auto sp = button->addComponent<SpriteComponent>();
	auto img = Resources::get<Texture>(path);
	sp->setTexture(img);
	sp->getSprite().setTextureRect(sf::IntRect(0, 0, 300, 102));
	sp->getSprite().setOrigin(sp->getSprite().getLocalBounds().width / 2, sp->getSprite().getLocalBounds().height / 2);
	//t->getText()->setOrigin(s->getShape().getLocalBounds().width / 2, s->getShape().getLocalBounds().height / 2);

	button->addComponent<ButtonComponent>(s, sp);

	return button;
}
