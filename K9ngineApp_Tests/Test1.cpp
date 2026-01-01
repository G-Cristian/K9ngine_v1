#include "Test1.h"

#include <format>
#include <memory>

#include "../K9ngineCore/K9Debug.h"

#include "../K9ngineCore/Common/Hasher.h"
#include "../K9ngineCore/FileSystem/FileReader.h"
#include "../K9ngineCore/FileSystem/Path.h"
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
    using namespace FileSystem;
    LOG_ADD_TAB();

    auto ok = K9ngine::K9ngineApp::init();
    auto windowSize = mWindowsManager.currentWindow().getFramebufferSize();
    float aspect = static_cast<float>(windowSize.width) / windowSize.height;
    auto camera = mRenderer.setCurrentCamera(std::make_shared<PerspectiveCamera>(aspect));
    camera->moveTo(0.0f, 0.0f, 8.0f);
    
    auto cube1 = mWorld.createGameObject(hashString("Cube1"));
    cube1->moveTo(0.0f, -2.0f, 0.0f);

    auto pyramid1 = mWorld.createGameObject(hashString("Pyramid1"));
    pyramid1->moveTo(2.0f, 0.0f, 0.0f);

    std::string vertexShaderSource = FileReader{Path::combine(Path::getCurrentPath(), R"(../Resources/Shaders/vertexShader1.glsl)")}.getTextContent();
    std::string fragmentShaderSource = FileReader{ Path::combine(Path::getCurrentPath(), R"(../Resources/Shaders/fragmentShader1.glsl)") }.getTextContent();
    auto program = std::make_shared<ShaderProgram>( Shader{ShaderType::K9_VERTEX_SHADER, vertexShaderSource.c_str()}
                                                  , Shader{ShaderType::K9_FRAGMENT_SHADER, fragmentShaderSource.c_str()}
                                                  );

    Material cubeMaterial{ program };
    cubeMaterial.addOrAssignAttributeLocation("cube1", 0);
    cubeMaterial.addModelViewMatrixProperty(Mat4MaterialProperty("mv_matrix"));
    cubeMaterial.addProjectionMatrixProperty(Mat4MaterialProperty("proj_matrix"));
    auto mesh = MeshFactory::createCube();
    auto bufferDataType = std::make_shared<BufferDataType>( "cube1", mesh.getFlattenedCoordinates(), 3
                                                          , TargetBuffer::K9_ARRAY_BUFFER, BufferDataUsage::K9_STATIC_DRAW
                                                          , TypeEnum::K9_FLOAT, BoolValues::K9_FALSE, 0);
    auto cubeComponent = mRenderer.emplaceRenderingComponent(cube1, cubeMaterial, { bufferDataType }, mesh.getVertexCount());
    cubeComponent->setFrontFaceMode(mesh.isCCW() ? FrontFaceMode::K9_CCW : FrontFaceMode::K9_CW);

    Material pyramidMaterial{ program };
    pyramidMaterial.addOrAssignAttributeLocation("pyramid1", 0);
    pyramidMaterial.addModelViewMatrixProperty(Mat4MaterialProperty("mv_matrix"));
    pyramidMaterial.addProjectionMatrixProperty(Mat4MaterialProperty("proj_matrix"));
    auto pyramidMesh = MeshFactory::createPyramid();
    auto bufferDataTypePyramid = std::make_shared<BufferDataType>( "pyramid1", pyramidMesh.getFlattenedCoordinates(), 3
                                                                , TargetBuffer::K9_ARRAY_BUFFER, BufferDataUsage::K9_STATIC_DRAW
                                                                , TypeEnum::K9_FLOAT, BoolValues::K9_FALSE, 0);
    auto pyramidComponent = mRenderer.emplaceRenderingComponent(pyramid1, pyramidMaterial, { bufferDataTypePyramid }, pyramidMesh.getVertexCount());
    pyramidComponent->setFrontFaceMode(pyramidMesh.isCCW() ? FrontFaceMode::K9_CCW : FrontFaceMode::K9_CW);
    
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

  void Test1::update(double elapsed)
  {
    K9ngine::K9ngineApp::update(elapsed);
  }

  void Test1::render(double elapsed)
  {
    K9ngine::K9ngineApp::render(elapsed);
  }
}