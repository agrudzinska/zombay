#include "cmp_bullet.h"
#include "cmp_sprite.h"
#include "maths.h"
#include "LevelSystem.h"
#include "system_physics.h"
using namespace std;
using namespace sf;

void BulletComponent::update(double dt) {
	_parent->get_components<PhysicsComponent>()[0]->setVelocity(_direction * _maxSpeed);
	
	/*auto touching = _parent->get_components<PhysicsComponent>()[0]->getTouching();
	if (touching.size() > 0)
	{
		for (auto t : touching)
		{
			if (t->GetFixtureA() != _owner->get_components<PhysicsComponent>()[0]->getFixture())
			{
				_parent->setForDelete();
			}
		}
	}*/

	if (_owner->is_fordeletion()) _parent->setForDelete();
	auto pos = _parent->getPosition();
	if (!validMove(pos))
	{
		_parent->setForDelete();
	}
	
}

bool BulletComponent::validMove(const sf::Vector2f& pos) const
{
	if (pos.x < 0.0f || pos.y > Engine::GetWindow().getSize().x ||
		pos.y < 0.0f || pos.y > Engine::GetWindow().getSize().y ||
		ls::getTileAt(pos) == ls::WALL)
	{
		return false;
	}
	return true;
}


BulletComponent::BulletComponent(Entity* p, Entity* owner, sf::Vector2f direction, float maxSpeed)
	: Component(p), _owner(owner), _direction(direction), _maxSpeed(maxSpeed) {}
