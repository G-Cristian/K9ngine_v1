#pragma once

#ifndef GAMEOBJECTS_COUNT
#define GAMEOBJECTS_COUNT 0
#endif // !GAMEOBJECTS_COUNT

//#include "GameObject.h"
#include "Handle.h"

namespace K9ngineCore {
  class GameObject;

  using GameObjectsTable = Memory::HandleTable<GameObject, GAMEOBJECTS_COUNT>;
  using GameObjectPtr = GameObjectsTable::handle_type;
  using ConstGameObjectPtr = GameObjectsTable::const_handle_type;
  //using GameObjectConstPtr = const GameObjectPtr;
}
