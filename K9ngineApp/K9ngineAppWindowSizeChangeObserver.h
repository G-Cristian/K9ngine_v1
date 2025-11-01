#pragma once

#include "Windows/WindowObservers.h"

namespace K9ngine
{
  class K9ngineApp;
  class K9ngineAppWindowSizeChangeObserver : public K9Windows::IWindowSizeChangeObserber
  {
  public:
    K9ngineAppWindowSizeChangeObserver(K9ngineApp*);
    ~K9ngineAppWindowSizeChangeObserver() = default;
    void update(int, int) override final;
  private:
    K9ngineApp* mApp;
  };
}