#include "cmp_sprite.h"
#include "system_renderer.h"
#include "system_resources.h"

using namespace std;

SpriteComponent::SpriteComponent(Entity* p)
	: Component(p), _sprite(make_shared<sf::Sprite>()) {}

/*SpriteComponent::SpriteComponent(Entity* p, const std::string& str)
	: Component(p), _string(str), _sprite(make_shared<sf::Sprite>()) {
		_sprite->getTexture
}
*/

void SpriteComponent::update(double dt) {
	_sprite->setPosition(_parent->getPosition());
	_sprite->setRotation(_parent->getRotation());
}

void SpriteComponent::render() { Renderer::queue(_sprite.get()); }

void ShapeComponent::update(double dt) {
	_shape->setPosition(_parent->getPosition());
	_shape->setRotation(_parent->getRotation());
}

void ShapeComponent::render() { Renderer::queue(_shape.get()); }

sf::Shape& ShapeComponent::getShape() const { return *_shape; }

ShapeComponent::ShapeComponent(Entity* p)
	: Component(p), _shape(make_shared<sf::CircleShape>()) {}

sf::Sprite& SpriteComponent::getSprite() const { return *_sprite; }

sf::Texture& SpriteComponent::getTexure() const { return *_tex; }