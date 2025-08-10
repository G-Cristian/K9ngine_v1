#include <format>

#include "K9Debug.h"

#include "World.h"

#include "CommonHandleTypes.h"
#include "Common/Hasher.h"

#include "GameObject.h"

namespace K9ngineCore {
  World::~World()
  {
    clear();
  }

  GameObjectPtr World::createGameObject(const Common::Hash& uid, const K9Math::Transform& transform /*= K9Math::Transform::identity()*/) {
    K9ASSERT(!mGameObjectsIdIndexMap.contains(uid), std::format("World::createGameObject, a game object with id {} already exists", uid).c_str());
    if (mGameObjectsIdIndexMap.contains(uid)) {
      mGameObjects.deleteHandle(mGameObjectsIdIndexMap.find(uid)->second);
    }

    auto index = mGameObjects.createHandle(Common::hashToUInt64(uid), uid, transform);
    mGameObjectsIdIndexMap[uid] = index;

    return mGameObjects.getHandle(index);
  }

  bool World::deleteGameObject(const Common::Hash& uid) {
    K9ASSERT(mGameObjectsIdIndexMap.contains(uid), std::format("World::deleteGameObject, a game object with id {} doesn't exist", uid).c_str());
    auto it = mGameObjectsIdIndexMap.find(uid);
    if (it != mGameObjectsIdIndexMap.end()) {
      mGameObjects.deleteHandle(it->second);
      mGameObjectsIdIndexMap.erase(uid);

      return true;
    }

    return false;
  }

  GameObjectPtr World::getGameObject(const Common::Hash& uid) {
    auto it = mGameObjectsIdIndexMap.find(uid);
    if (it != mGameObjectsIdIndexMap.end()) {
      return mGameObjects.getHandle(it->second);
    }
    else {
      return mGameObjects.NullHandle;
    }
  }

  const GameObjectPtr World::getGameObject(const Common::Hash& uid) const {
    auto it = mGameObjectsIdIndexMap.find(uid);
    if (it != mGameObjectsIdIndexMap.end()) {
      return mGameObjects.getHandle(it->second);
    }
    else {
      return mGameObjects.NullHandle;
    }
  }

  void World::clear()
  {
    mGameObjects.clear();
    mGameObjectsIdIndexMap.clear();
  }
}