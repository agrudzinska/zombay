#include "engine.h"
#include "game.h"
#include "scenes/scene_menu.h"

using namespace std;

MenuScene menu;
Level1Scene level1;
HowToScene howTo;
GameOverScene gameOver;

int main() {
  Engine::Start(1280, 720, "Zombay",&menu);
  //Engine::Start(1024, 576, "Zombay", &menu);

}