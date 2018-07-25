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
	auto tex = Resources::get<Texture>("character.png");
	s->setTexture(tex);
	s->getSprite().setTextureRect(sf::IntRect(0, 0, 64, 64));
	s->getSprite().setOrigin(s->getSprite().getLocalBounds().width / 2, s->getSprite().getLocalBounds().height / 2);
	player->addComponent<PlayerPhysicsComponent>();

	return player;
	
}

shared_ptr<Entity> create_button(string text)
{
	auto button = Engine::GetActiveScene()->makeEntity();
	button->addTag("button");

	auto s = button->addComponent<ShapeComponent>();
	s->setShape<RectangleShape>(Vector2f(250.0f, 34.0f));
	s->getShape().setOrigin(s->getShape().getLocalBounds().width / 2, s->getShape().getLocalBounds().height / 2);

	auto t = button->addComponent<TextComponent>(text);
	t->getText()->setOrigin(500.0f / 2 - 13.0f, t->getText()->getLocalBounds().height / 2 + 14.0f);
	//t->getText()->setOrigin(s->getShape().getLocalBounds().width / 2, s->getShape().getLocalBounds().height / 2);
	t->getText()->setColor(Color(255, 255, 255));

	button->addComponent<ButtonComponent>(s, t);

	return button;
}