#include "prefabs.h"
#include "engine.h"
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
	player->setPosition(Vector2f(32.0f,32.0f));
	auto s = player->addComponent<ShapeComponent>();
	s->setShape<sf::RectangleShape>(Vector2f(20.f, 30.f));
	s->getShape().setFillColor(Color(0, 255, 0));
	s->getShape().setOrigin(20.f, 15.f);
	player->addComponent<PlayerPhysicsComponent>(Vector2f(20.f, 30.f));

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
	//t->getText()->setOrigin(s->getShape().getLocalBounds().width / 2, s->getShape().getLocalBounds().height / 2);
	t->getText()->setColor(Color(255, 255, 255));

	button->addComponent<ButtonComponent>(s, t);

	return button;
}