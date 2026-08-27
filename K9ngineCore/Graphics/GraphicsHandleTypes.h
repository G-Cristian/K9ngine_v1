#pragma once

#ifndef RENDERINGCOMPONENTS_COUNT
#define RENDERINGCOMPONENTS_COUNT 0
#endif // !RENDERINGCOMPONENTS_COUNT

#ifndef TEXTURES_COUNT
#define TEXTURES_COUNT 0
#endif // !TEXTURES_COUNT

#include "../Handle.h"
#include "RenderingComponent.h"
#include "Texture.h"

#include <memory>

namespace K9ngineCore {
  namespace K9Graphics {
    using RenderingComponentTable = Memory::HandleTable<RenderingComponent, RENDERINGCOMPONENTS_COUNT>;
    using RenderingComponentPtr = RenderingComponentTable::handle_type;
    using ConstRenderingComponentPtr = RenderingComponentTable::const_handle_type;
    //using RenderingComponentConstPtr = const RenderingComponentPtr;

    using TextureTable = Memory::HandleTable<Texture, TEXTURES_COUNT>;
    using TexturePtr = TextureTable::handle_type;
    using ConstTexturePtr = TextureTable::const_handle_type;
  }
}