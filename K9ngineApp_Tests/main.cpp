#include "K9ngineApp.h"
#include "Test1.h"

#include <memory>

int main(int argc, char** argv) {
  using namespace K9ngineAppTest;

  auto game{ std::make_unique<Test1>() };
  game->run();

  return 0;
}