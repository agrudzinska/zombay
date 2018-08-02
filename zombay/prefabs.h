#pragma once

#include "ecm.h"
#include "engine.h"
#include <string>

std::shared_ptr<Entity> create_player();
std::vector<std::shared_ptr<Entity>> create_enemies1(std::shared_ptr<Entity> p);
std::vector<std::shared_ptr<Entity>> create_enemies2(std::shared_ptr<Entity> p);
std::vector<std::shared_ptr<Entity>> create_enemies3(std::shared_ptr<Entity> p);
std::shared_ptr<Entity> create_button(std::string);
//std::shared_ptr<Entity> create_player_bullet(sf::Vector2f pos, sf::Vector2f direction, sf::Vector2f shootDirection, double dt, Entity* parent);
