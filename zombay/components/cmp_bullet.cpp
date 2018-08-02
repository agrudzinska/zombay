#include "cmp_bullet.h"
#include "cmp_sprite.h"
#include "maths.h"
#include "LevelSystem.h"
using namespace std;
using namespace sf;

void BulletComponent::update(double dt) {
	_parent->get_components<PhysicsComponent>()[0]->setVelocity(_direction * _maxSpeed);
	auto pos = _owner->getPosition();
	auto new_pos = pos + _direction;
	//if (validMove(new_pos))
		//_parent->get_components<PhysicsComponent>()[0]->setVelocity(_direction * _maxSpeed);
		//move(new_pos*_direction*_maxSpeed);
		//_parent->setPosition(new_pos);
	
	//move(normalize(_direction) * _maxSpeed * (float)dt);

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
