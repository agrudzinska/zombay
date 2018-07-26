#include "prefabs.h"
#include "engine.h"
#include "game.h"
#include <LevelSystem.h>
#include <system_resources.h>
#include "components/cmp_text.h"
#include "components/cmp_sprite.h"
#include "components/cmp_button.h"
#include "components/cmp_player_physics.h"

using namespace std;
using namespace sf;

shared_ptr<Entity> create_player()
{
	auto player = Engine::GetActiveScene()->makeEntity();
	player->setPosition(Vector2f(game_width /2, game_heigth / 2));
	auto s = player->addComponent<SpriteComponent>();
	auto tex = Resources::get<Texture>("char.png");
	s->setTexture(tex);
	s->getSprite().setTextureRect(sf::IntRect(0, 0, 64, 64));
	s->getSprite().setOrigin(s->getSprite().getLocalBounds().width / 2, s->getSprite().getLocalBounds().height / 2);
	player->addComponent<PlayerPhysicsComponent>();

	return player;
	
}

shared_ptr<Entity> create_button(string path)
{
	auto button = Engine::GetActiveScene()->makeEntity();
	button->addTag("button");

	auto s = button->addComponent<ShapeComponent>();
	s->setShape<RectangleShape>(Vector2f(250.0f, 34.0f));
	s->getShape().setOrigin(s->getShape().getLocalBounds().width / 2, s->getShape().getLocalBounds().height / 2);

	auto sp = button->addComponent<SpriteComponent>();
	auto img = Resources::get<Texture>(path);
	sp->setTexture(img);
	sp->getSprite().setTextureRect(sf::IntRect(0, 0, 126, 43));
	sp->getSprite().setOrigin(sp->getSprite().getLocalBounds().width / 2, sp->getSprite().getLocalBounds().height / 2);
	//t->getText()->setOrigin(s->getShape().getLocalBounds().width / 2, s->getShape().getLocalBounds().height / 2);

	button->addComponent<ButtonComponent>(s, sp);

	return button;
}