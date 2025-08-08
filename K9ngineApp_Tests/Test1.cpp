#include "Test1.h"

#include <format>
#include <memory>

#include "../K9ngineCore/K9Debug.h"

#include "../K9ngineCore/Common/Hasher.h"
#include "../K9ngineCore/FileReader.h"
#include "../K9ngineCore/Graphics/BufferDataType.h"
#include "../K9ngineCore/Graphics/Camera.h"
#include "../K9ngineCore/Graphics/Material.h"
#include "../K9ngineCore/Graphics/Mesh.h"
#include "../K9ngineCore/Graphics/MeshFactory.h"
#include "../K9ngineCore/Graphics/PerspectiveCamera.h"
#include "../K9ngineCore/Graphics/Shader.h"
#include "../K9ngineCore/Graphics/ShaderProgram.h"

namespace K9ngineAppTest
{
  using namespace K9ngineCore;
  using namespace K9ngineCore::K9Graphics;
  bool Test1::init()
  {
    using namespace Common;
    LOG_ADD_TAB();
    LOG_MESSAGE("Test1.Init");

    auto ok = K9ngine::K9ngineApp::init();
    auto windowSize = mWindowsManager.currentWindow().getFramebufferSize();
    float aspect = static_cast<float>(windowSize.width) / windowSize.height;
    auto camera = mRenderer.setCurrentCamera(std::make_shared<PerspectiveCamera>(aspect));
    
    mRenderer.setCurrentCamera(camera);

    camera->moveTo(0.0f, 0.0f, 8.0f);
    
    auto cube1 = mWorld.createGameObject(hashString("Cube1"));
    cube1->moveTo(0.0f, -2.0f, 0.0f);

    std::string vertexShaderSource = IO::FileReader{"C:\\Users\\lococ\\source\\repos\\K9ngine_v1\\x64\\Debug\\vertexShader1.glsl"}.getTextContent();
    std::string fragmentShaderSource = IO::FileReader{ "C:\\Users\\lococ\\source\\repos\\K9ngine_v1\\x64\\Debug\\fragmentShader1.glsl" }.getTextContent();
    auto program = std::make_shared<ShaderProgram>( Shader{ShaderType::K9_VERTEX_SHADER, vertexShaderSource.c_str()}
                                                  , Shader{ShaderType::K9_FRAGMENT_SHADER, fragmentShaderSource.c_str()}
                                                  );

    Material material{ program };
    material.addOrAssignAttributeLocation("cube1", 0);
    material.addModelViewMatrixProperty(std::make_shared<Mat4MaterialProperty>("mv_matrix"));
    material.addProjectionMatrixProperty(std::make_shared<Mat4MaterialProperty>("proj_matrix"));
    auto mesh = MeshFactory::createCube();
    auto bufferDataType = std::make_shared<BufferDataType>( "cube1", mesh.getFlattenedCoordinates(), 3
                                                          , TargetBuffer::K9_ARRAY_BUFFER, BufferDataUsage::K9_STATIC_DRAW
                                                          , TypeEnum::K9_FLOAT, BoolValues::K9_FALSE, 0);
    mRenderer.emplaceRenderingComponent(cube1, material, { bufferDataType }, mesh.getVertexCount());
    
    LOG_REMOVE_TAB();

    return ok;
  }

  void Test1::processInput()
  {
    K9ngine::K9ngineApp::processInput();
  }
  void Test1::fixedUpdate()
  {
    K9ngine::K9ngineApp::fixedUpdate();
  }

  void Test1::fixedPhysics()
  {
    K9ngine::K9ngineApp::fixedPhysics();
  }

  void Test1::update(float elapsed)
  {
    K9ngine::K9ngineApp::update(elapsed);
  }

  void Test1::render(float elapsed)
  {
    K9ngine::K9ngineApp::render(elapsed);
  }
}