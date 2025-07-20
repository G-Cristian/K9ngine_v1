#ifdef K9_DEBUG_MEMORY
#define _CRTDBG_MAP_ALLOC
#define _CRTDBG_MAP_ALLOC_NEW

#include <stdlib.h>
#include <crtdbg.h>
#endif // K9_DEBUG_MEMORY

#include "../K9ngineApp/K9ngineApp.h"
#include "Test1.h"

#include <memory>

int main(int argc, char** argv) {
#ifdef K9_DEBUG_MEMORY
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
  //_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
  _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
  _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
#endif

  using namespace K9ngineAppTest;

  auto game = new Test1{};
  game->run();
  delete game;
  game = nullptr;

#ifdef K9_DEBUG_MEMORY
  _CrtDumpMemoryLeaks();
#endif

  return 0;
}