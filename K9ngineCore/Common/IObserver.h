#pragma once

#include <memory>

namespace K9ngineCore
{
  namespace Common {
    template <typename T, typename S>
    class IObserver {
    public:
      using Subject = T;
      using Args = S;

      virtual ~IObserver() {}
      virtual void update(const Subject&, const Args&) const = 0;
    protected:

    };
  }
}