#include "Test1.h"

namespace K9ngineAppTest
{
  bool Test1::init()
  {
    return K9ngine::K9ngineApp::init();
  }

  void Test1::processInput()
  {
    K9ngine::K9ngineApp::processInput();
  }
  void Test1::fixedUpdate()
  {
    K9ngine::K9ngineApp::fixedUpdate();
  }

  void Test1::fixedPhysics()
  {
    K9ngine::K9ngineApp::fixedPhysics();
  }

  void Test1::update(float elapsed)
  {
    K9ngine::K9ngineApp::update(elapsed);
  }

  void Test1::render(float elapsed)
  {
    K9ngine::K9ngineApp::render(elapsed);
  }
}