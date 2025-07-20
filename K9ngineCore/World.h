#pragma once

#ifndef GAMEOBJECTS_COUNT
#define GAMEOBJECTS_COUNT 0
#endif // !GAMEOBJECTS_COUNT

#include "CommonHandleTypes.h"
#include "Common/Hasher.h"

#include "Math/Transform.h"

#include <unordered_map>

namespace K9ngineCore
{  
  class World
  {
  public:
    using GameObjectsIdsIndicesMapType = std::unordered_map<Common::Hash, size_t>;

    GameObjectPtr createGameObject(const Common::Hash&, const K9Math::Transform& = K9Math::Transform::identity());
    bool deleteGameObject(const Common::Hash&);

    GameObjectPtr getGameObject(const Common::Hash&);
    const GameObjectPtr getGameObject(const Common::Hash&) const;
  private:
    GameObjectsIdsIndicesMapType mGameObjectsIdIndexMap{};
    GameObjectsTable mGameObjects{};
  };
}