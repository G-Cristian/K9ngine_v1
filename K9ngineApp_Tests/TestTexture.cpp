#include "TestTexture.h"

#include <format>
#include <memory>

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
#include "../K9ngineCore/Graphics/TextureProperty.h"
#include "../K9ngineCore/K9Debug.h"
#include "../K9ngineCore/World.h"

namespace K9ngineAppTest
{
  using namespace K9ngineCore;
  using namespace K9ngineCore::K9Graphics;

  bool TestTexture::init()
  {
    using namespace Common;
    using namespace FileSystem;
    LOG_ADD_TAB();
    auto ok = K9ngine::K9ngineApp::init();
    auto windowSize = mWindowsManager.currentWindow().getFramebufferSize();

    float aspect = static_cast<float>(windowSize.width) / windowSize.height;
    auto camera = mRenderer.setCurrentCamera(std::make_shared<PerspectiveCamera>(aspect));
    camera->moveTo(0.0f, 0.0f, 30.0f);

    auto program = createShaderProgram(R"(../Resources/Shaders/vertexShaderTexture1.glsl)", R"(../Resources/Shaders/fragmentShaderTexture1.glsl)");

    auto wallTexture = mTextureManager.createIfNewTexture(R"(../Resources/Textures/wall.jpg)");
    auto containerTexture = mTextureManager.createIfNewTexture(R"(../Resources/Textures/container.jpg)");
    auto faceTexture = mTextureManager.createIfNewTexture(R"(../Resources/Textures/awesomeface.png)");

    Material sunMaterial = createMaterial(program, { "sun", "sun_tex_coords" }, "mv_matrix", "proj_matrix", { std::make_shared<TextureProperty>("faceTexture", faceTexture, TargetTexture::K9_TEXTURE_2D, TextureSampler::K9_TEXTURE0)});
    auto sunMesh = MeshFactory::createPyramid();

    Material planetMaterial = createMaterial(program, { "planet", "planet_tex_coords"}, "mv_matrix", "proj_matrix", { std::make_shared<TextureProperty>("wallTexture", wallTexture, TargetTexture::K9_TEXTURE_2D, TextureSampler::K9_TEXTURE0)});
    auto planetMesh = MeshFactory::createCube();

    Material moonMaterial = createMaterial(program, { "moon", "moon_tex_coords"}, "mv_matrix", "proj_matrix", { std::make_shared<TextureProperty>("containerTexture", containerTexture, TargetTexture::K9_TEXTURE_2D, TextureSampler::K9_TEXTURE0)});
    auto moonMesh = MeshFactory::createCube();

    auto sunGO = mWorld.createGameObject(hashString("Sun"));
    sunGO->setScale(2.0f, 2.0f, 2.0f);
    sunGO->moveTo(0.0f, 0.0f, 0.0f);

    auto sunPlanetPivotGO = mWorld.createGameObject(hashString("SunPlanetPivot"));
    sunPlanetPivotGO->moveTo(0.0f, 0.0f, 0.0f);
    mWorld.attachGameObjects(sunGO, sunPlanetPivotGO, true, false, false);

    auto planetGO = mWorld.createGameObject(hashString("Planet"));
    planetGO->moveTo(5.0f, 0.0f, 0.0f);
    mWorld.attachGameObjects(sunPlanetPivotGO, planetGO, true, true, false);

    auto planetMoonPivotGO = mWorld.createGameObject(hashString("PlanetMoonPivot"));
    planetMoonPivotGO->moveTo(0.0f, 0.0f, 0.0f);
    mWorld.attachGameObjects(planetGO, planetMoonPivotGO, true, false, false);

    auto moonGO = mWorld.createGameObject(hashString("Moon"));
    moonGO->setScale(0.5f, 0.5f, 0.5f);
    moonGO->moveTo(0.0f, 3.0f, 0.0f);
    mWorld.attachGameObjects(planetMoonPivotGO, moonGO, true, true, false);

    auto sunComp = emplaceRenderingComponent("sun", sunGO, sunMesh, sunMaterial);
    sunComp->setFrontFaceMode(sunMesh.isCCW() ? FrontFaceMode::K9_CCW : FrontFaceMode::K9_CW);


    auto planetComp = emplaceRenderingComponent("planet", planetGO, planetMesh, planetMaterial);
    planetComp->setFrontFaceMode(planetMesh.isCCW() ? FrontFaceMode::K9_CCW : FrontFaceMode::K9_CW);


    auto moonComp = emplaceRenderingComponent("moon", moonGO, moonMesh, moonMaterial);
    moonComp->setFrontFaceMode(moonMesh.isCCW() ? FrontFaceMode::K9_CCW : FrontFaceMode::K9_CW);

    LOG_REMOVE_TAB();

    return ok;
  }

  void TestTexture::update(double elapsed)
  {
    static double totalTime = 0.0;
    totalTime += elapsed;
    K9ngine::K9ngineApp::update(elapsed);

    auto sunGO = mWorld.getGameObject(hashString("Sun"));
    sunGO->setRotation(0.000785f * static_cast<float>(totalTime), 0.0f, 0.0f);

    auto sunPlanetPivotGO = mWorld.getGameObject(hashString("SunPlanetPivot"));
    sunPlanetPivotGO->setRotation(0.0f, 0.00157f * static_cast<float>(totalTime), 0.0f);

    auto planetGO = mWorld.getGameObject(hashString("Planet"));
    planetGO->setRotation(0.0f, 0.0f, 0.00314f * static_cast<float>(totalTime));

    auto planetMoonPivotGO = mWorld.getGameObject(hashString("PlanetMoonPivot"));
    planetMoonPivotGO->setRotation(0.00157f * static_cast<float>(totalTime), 0.0f, 0.0f);

    auto moonGO = mWorld.getGameObject(hashString("Moon"));
    moonGO->setRotation(0.0f, 0.00628f * static_cast<float>(totalTime), 0.0f);
  }

  std::shared_ptr<K9ngineCore::K9Graphics::ShaderProgram> TestTexture::createShaderProgram(std::string_view vs, std::string_view fs) const
  {
    using namespace FileSystem;
    std::string vertexShaderSource = FileReader{ Path::combine(Path::getCurrentPath(), vs) }.getTextContent();
    std::string fragmentShaderSource = FileReader{ Path::combine(Path::getCurrentPath(), fs) }.getTextContent();
    return std::make_shared<ShaderProgram>(Shader{ ShaderType::K9_VERTEX_SHADER, vertexShaderSource.c_str() }
      , Shader{ ShaderType::K9_FRAGMENT_SHADER, fragmentShaderSource.c_str() }
    );
  }


  K9Graphics::Material TestTexture::createMaterial(std::shared_ptr<K9Graphics::ShaderProgram> program, const std::vector<std::string>& attrLocationName, std::string_view mvMatrixName, std::string_view projMatrixName, const std::vector<std::shared_ptr<K9Graphics::MaterialProperty>>& properties) const
  {
    Material material{ program };

    for (int i = 0; i < attrLocationName.size(); i++) {
      material.addOrAssignAttributeLocation(attrLocationName[i], i);
    }
    
    material.addModelViewMatrixProperty(Mat4MaterialProperty(std::string{ mvMatrixName }));
    material.addProjectionMatrixProperty(Mat4MaterialProperty(std::string{ projMatrixName }));
    for (const auto& property : properties) {
      material.addOrSetProperty(property);
    }
    

    return material;
  }

  RenderingComponentPtr TestTexture::emplaceRenderingComponent(std::string_view name, GameObjectPtr gameObject, Mesh mesh, const Material& material)
  {
    std::vector<RenderingComponent::BufferDataTypePtr> bufferDataType;
    auto vertexBufferDataType = std::make_shared<BufferDataType>(std::string{ name }, mesh.getFlattenedCoordinates(), 3
      , TargetBuffer::K9_ARRAY_BUFFER, BufferDataUsage::K9_STATIC_DRAW
      , TypeEnum::K9_FLOAT, BoolValues::K9_FALSE, 0);

    bufferDataType.push_back(vertexBufferDataType);
    
    if (mesh.getTextureCoordinatesCount() > 0) {
      auto textureBufferDataType = std::make_shared<BufferDataType>(std::format("{}_tex_coords", name), mesh.getTextureCoordinates(), 2
        , TargetBuffer::K9_ARRAY_BUFFER, BufferDataUsage::K9_STATIC_DRAW
        , TypeEnum::K9_FLOAT, BoolValues::K9_FALSE, 0);

      bufferDataType.push_back(textureBufferDataType);
    }

    return mRenderer.emplaceRenderingComponent(gameObject, material, bufferDataType, mesh.getVertexCount());
  }
}