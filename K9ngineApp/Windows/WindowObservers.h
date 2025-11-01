#pragma once

namespace K9ngine {
  namespace K9Windows {
    class IWindowSizeChangeObserber
    {
    public:
      virtual ~IWindowSizeChangeObserber() = default;
      virtual void update(int, int) = 0;
    };

    class IFramebufferSizeChangeObserber
    {
    public:
      virtual ~IFramebufferSizeChangeObserber() = default;
      virtual void update(int, int) = 0;
    };
  }
}