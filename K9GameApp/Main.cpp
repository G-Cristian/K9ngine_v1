#include "K9Game.h"

int main(int argc, char** argv) {
  const char* settingsFullPath = argc > 1 ? argv[1] : "K9ngineSettings.txt";
  K9ngineGame::K9Game game(settingsFullPath);
  game.run();
}