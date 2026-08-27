#pragma once

#include <memory>
#include <string>
#include <string_view>

#include "../K9ngineApp/K9ngineApp.h"

#include "../K9ngineCore/Common/Hasher.h"
#include "../K9ngineCore/FileSystem/FileReader.h"
#include "../K9ngineCore/FileSystem/Path.h"
#include "../K9ngineCore/Graphics/BufferDataType.h"
#include "../K9ngineCore/Graphics/Camera.h"
#include "../K9ngineCore/Graphics/Material.h"
#include "../K9ngineCore/Graphics/MaterialProperty.h"
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
  class TestTexture : public K9ngine::K9ngineApp
  {
  public:
    //const char* settingsFullpath = "K9ngineSettings.txt"
    explicit TestTexture(const char* settingsFullpath) :
      K9ngine::K9ngineApp{ settingsFullpath }
    {
    }

    explicit TestTexture(int contextVersionMajor = 4, int contextVersionMinor = 3, float msPerFrame = 16.0) :
      K9ngine::K9ngineApp{ contextVersionMajor, contextVersionMinor, msPerFrame }
    {
    }

    ~TestTexture() override = default;
  private:
    bool init() override;
    void update(double elapsed) override;

    std::shared_ptr<K9Graphics::ShaderProgram> createShaderProgram(std::string_view vs, std::string_view fs) const;
    K9Graphics::Material createMaterial(std::shared_ptr<K9Graphics::ShaderProgram> program, const std::vector<std::string>& attrLocationName, std::string_view mvMatrixName, std::string_view projMatrixName, const std::vector<std::shared_ptr<K9Graphics::MaterialProperty>>& properties) const;
    RenderingComponentPtr emplaceRenderingComponent(std::string_view name, GameObjectPtr gameObject, Mesh mesh, const Material& material);
  };
}
