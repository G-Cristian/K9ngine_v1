#pragma once

#include <memory>
#include <string_view>

#include "../K9ngineApp/K9ngineApp.h"

#include "../K9ngineCore/Common/Hasher.h"
#include "../K9ngineCore/FileSystem/FileReader.h"
#include "../K9ngineCore/FileSystem/Path.h"
#include "../K9ngineCore/Graphics/BufferDataType.h"
#include "../K9ngineCore/Graphics/Camera.h"
#include "../K9ngineCore/Graphics/Material.h"
#include "../K9ngineCore/Graphics/Mesh.h"
#include "../K9ngineCore/Graphics/MeshFactory.h"
#include "../K9ngineCore/Graphics/PerspectiveCamera.h"
#include "../K9ngineCore/Graphics/Renderer.h"
#include "../K9ngineCore/Graphics/Shader.h"
#include "../K9ngineCore/Graphics/ShaderProgram.h"
#include "../K9ngineCore/K9Debug.h"
#include "../K9ngineCore/World.h"

namespace K9ngineAppTest
{
  using namespace K9ngineCore;
  using namespace K9ngineCore::K9Graphics;

  class TestAttachedObjects : public K9ngine::K9ngineApp
  {
  public:
    //const char* settingsFullpath = "K9ngineSettings.txt"
    explicit TestAttachedObjects(const char* settingsFullpath) :
      K9ngine::K9ngineApp{ settingsFullpath }
    {
    }

    explicit TestAttachedObjects(int contextVersionMajor = 4, int contextVersionMinor = 3, float msPerFrame = 16.0) :
      K9ngine::K9ngineApp{ contextVersionMajor, contextVersionMinor, msPerFrame }
    {
    }

    ~TestAttachedObjects() override = default;
  private:
    bool init() override;
    void processInput() override;
    void fixedUpdate() override;
    void fixedPhysics() override;
    void update(double elapsed) override;
    void render(double elapsed) override;

    std::shared_ptr<K9Graphics::ShaderProgram> createShaderProgram(std::string_view vs, std::string_view fs) const;
    Material createMaterial(std::shared_ptr<ShaderProgram> program, std::string_view attrLocationName, std::string_view mvMatrixName, std::string_view projMatrixName) const;
    RenderingComponentPtr emplaceRenderingComponent(std::string_view name, GameObjectPtr gameObject, Mesh mesh, const Material& material);
  };
}
