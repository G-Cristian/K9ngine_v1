#if (defined(_DEBUG) && defined(K9_DEBUG_MEMORY))

#include "vld.h"

//#define _CRTDBG_MAP_ALLOC
//#define _CRTDBG_MAP_ALLOC_NEW

//#include <crtdbg.h>
//#include <stdlib.h>

#endif // K9_DEBUG_MEMORY

#include <memory>

#include "../K9ngineCore/K9Debug.h"
#include "Test1.h"
#include "TestInstanced1.h"
#include "TestAttachedObjects.h"
#include "TestTexture.h"

int main(int argc, char** argv) {
#ifdef K9_DEBUG_MEMORY
  //_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
  ////_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
  //_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
  //_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
#endif

  using namespace K9ngineAppTest;

  {
    //Test1 game;
    //TestInstanced1 game;
    //TestAttachedObjects game;
    TestTexture game;

    game.run();
  }

  //K9ngine::K9ngineApp* game = new Test1{};
  /*auto game = new Test1{};
  game->run();
  delete game;
  game = nullptr;*/

#ifdef K9_DEBUG_MEMORY
  //_CrtDumpMemoryLeaks();
#endif

  return 0;
}