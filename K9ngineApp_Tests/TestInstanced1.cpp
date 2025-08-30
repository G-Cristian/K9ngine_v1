#include "TestInstanced1.h"

#include <format>
#include <memory>

#include "../K9ngineCore/K9Debug.h"

#include "../K9ngineCore/Common/Hasher.h"
#include "../K9ngineCore/FileSystem/FileReader.h"
#include "../K9ngineCore/FileSystem/Path.h"
#include "../K9ngineCore/Graphics/BufferDataType.h"
#include "../K9ngineCore/Graphics/Camera.h"
#include "../K9ngineCore/Graphics/FloatMaterialProperty.h"
#include "../K9ngineCore/Graphics/Mat4MaterialProperty.h"
#include "../K9ngineCore/Graphics/Material.h"
#include "../K9ngineCore/Graphics/Mesh.h"
#include "../K9ngineCore/Graphics/MeshFactory.h"
#include "../K9ngineCore/Graphics/PerspectiveCamera.h"
#include "../K9ngineCore/Graphics/RenderingComponent.h"
#include "../K9ngineCore/Graphics/Shader.h"
#include "../K9ngineCore/Graphics/ShaderProgram.h"

namespace K9ngineAppTest
{
  using namespace K9ngineCore;
  using namespace K9ngineCore::K9Graphics;
  bool TestInstanced1::init()
  {
    using namespace Common;
    using namespace FileSystem;
    LOG_ADD_TAB();
    LOG_MESSAGE("TestInstanced1.Init");

    auto ok = K9ngine::K9ngineApp::init();
    auto windowSize = mWindowsManager.currentWindow().getFramebufferSize();
    float aspect = static_cast<float>(windowSize.width) / windowSize.height;
    auto camera = mRenderer.setCurrentCamera(std::make_shared<PerspectiveCamera>(aspect));
    camera->moveTo(0.0f, 0.0f, 420.0f);

    auto cube1 = mWorld.createGameObject(hashString("Cube1"));
    cube1->moveTo(0.0f, -2.0f, 0.0f);

    std::string vertexShaderSource = FileReader{ Path::combine(Path::getCurrentPath(), R"(../Resources/Shaders/vertexShaderInstancing1.glsl)") }.getTextContent();
    std::string fragmentShaderSource = FileReader{ Path::combine(Path::getCurrentPath(), R"(../Resources/Shaders/fragmentShaderInstancing1.glsl)") }.getTextContent();
    auto program = std::make_shared<ShaderProgram>(Shader{ ShaderType::K9_VERTEX_SHADER, vertexShaderSource.c_str() }
      , Shader{ ShaderType::K9_FRAGMENT_SHADER, fragmentShaderSource.c_str() }
    );

    Material material{ program };
    material.addOrAssignAttributeLocation("cube1", 0);
    material.addModelMatrixProperty(Mat4MaterialProperty("m_matrix"));
    material.addViewMatrixProperty(Mat4MaterialProperty("v_matrix"));
    material.addProjectionMatrixProperty(Mat4MaterialProperty("proj_matrix"));

    material.addOrSetProperty(std::make_shared<FloatMaterialProperty>("tf", 0.0f));

    auto mesh = MeshFactory::createCube();
    auto bufferDataType = std::make_shared<BufferDataType>( "cube1", mesh.getFlattenedCoordinates(), 3
                                                          , TargetBuffer::K9_ARRAY_BUFFER, BufferDataUsage::K9_STATIC_DRAW
                                                          , TypeEnum::K9_FLOAT, BoolValues::K9_FALSE, 0);
    mRenderer.emplaceRenderingComponent(hashString("Cube1RC"), cube1, material, {bufferDataType}, mesh.getVertexCount(), 100000);

    LOG_REMOVE_TAB();

    return ok;
  }

  void TestInstanced1::update(double elapsed)
  {
    K9ngine::K9ngineApp::update(elapsed);
    auto renderingComponent = mRenderer.getRenderingComponent(hashString("Cube1RC"));
    renderingComponent->getMaterial().addOrSetProperty(std::make_shared<FloatMaterialProperty>("tf", renderingComponent->getMaterial().getProperty("tf")->getValue<float>() + elapsed));
  }
}