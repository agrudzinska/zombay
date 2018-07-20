#include <SFML/Graphics.hpp>
#include <iostream>
#include "entity.h"
#include "player.h"
#include "game.h"
#include "levelsystem.h"

using namespace std;
using namespace sf;

vector<Entity *> entities;
Player* player;

void Reset() {

}

void Load() {
	player = new Player();
	entities.push_back(player);
	
	ls::loadLevelFile("res/maze.txt");

	// Print level to the console
	cout << "// Printing level ///" << endl;
	for (size_t y = 0; y < ls::getHeight(); ++y) {
		for (size_t x = 0; x < ls::getWidth(); ++x) {
			cout << ls::getTile({ x, y });
		}
		cout << endl;
	}
	cout << "/////////////////////" << endl;
	
	Reset();
}

void Update(RenderWindow &window){
	static Clock clock;
	float dt = clock.restart().asSeconds();
	Event event;
	while(window.pollEvent(event)){
		if(event.type == sf::Event::Closed){
			window.close();
		}
	}

	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		window.close();
	}

	for (auto &e : entities) {
		e->update(dt);
	}
}

void Render(RenderWindow &window){
	ls::render(window);
	for (auto &e : entities) {
		e->render(window);
	}
}

int main(){
	RenderWindow window(VideoMode(gameWidth, gameHeight),"zombay");
	Load();
	while(window.isOpen()){
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}

	return 0;
}