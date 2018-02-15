#include "DemoScene.h"
#include "MaterialWireframe.h"
#include "MaterialPBR.h"
#include "MaterialPhong.h"
#include "MaterialFractal.h"

//-----------------------------------------------------------------------------------------------------
void DemoScene::loadMesh()
{
  static constexpr std::array<const char*, 3> shaderAttribs = {{"inVert", "inNormal", "inUV"}};
  const auto& mesh = m_meshes[m_meshIndex];
  auto prog = m_shaderLib->getCurrentShader();

  using namespace MeshAttributes;
  for (const auto buff : {VERTEX, NORMAL, UV})
  {
    m_meshVBO.append(mesh.getAttribData(buff), buff);
    prog->enableAttributeArray(shaderAttribs[buff]);
    prog->setAttributeBuffer(shaderAttribs[buff], GL_FLOAT, m_meshVBO.offset(buff), 3);
  }

}
//-----------------------------------------------------------------------------------------------------
void DemoScene::init()
{
  Scene::init();

  initMaterials();
  initGeo();

  // Scope the using declaration
  {
    using namespace SceneMatrices;
    m_matrices[MODEL_VIEW] = glm::translate(m_matrices[MODEL_VIEW], glm::vec3(0.0f, 0.0f, -2.0f));
  }
}
//-----------------------------------------------------------------------------------------------------
void DemoScene::initGeo()
{
  m_meshes[0].load("models/cube.obj");
  m_meshes[1].load("models/plane.obj");
  m_meshes[2].load("models/Face.obj");
  m_meshes[3].load("models/Suzanne.obj");
  m_meshes[4].load("models/test2.obj");
  m_meshes[5].load("models/Asteroid.obj");
  // Create and bind our Vertex Array Object
  m_vao->create();
  m_vao->bind();
  // Create and bind our Vertex Buffer Object
  m_meshVBO.init();
  generateNewGeometry();
}
//-----------------------------------------------------------------------------------------------------
void DemoScene::initMaterials()
{
  m_materials.reserve(5);

  m_materials.emplace_back(new MaterialPhong(m_camera, m_shaderLib, &m_matrices));
  m_materials.emplace_back(new MaterialPBR(m_camera, m_shaderLib, &m_matrices, {0.5f, 0.0f, 0.0f}, 1.0f, 1.0f, 0.5f, 1.0f));
  m_materials.emplace_back(new MaterialPBR(m_camera, m_shaderLib, &m_matrices, {0.1f, 0.2f, 0.5f}, 0.5f, 1.0f, 0.4f, 0.2f));
  m_materials.emplace_back(new MaterialWireframe(m_camera, m_shaderLib, &m_matrices));
  m_materials.emplace_back(new MaterialFractal(m_camera, m_shaderLib, &m_matrices));
  for (size_t i = 0; i < m_materials.size(); ++i)
  {
    auto& mat = m_materials[i];
    auto name = m_shaderLib->loadShaderProg(mat->shaderFileName());
    mat->setShaderName(name);
    mat->apply();
  }
  m_materials[m_currentMaterial]->apply();
}
//-----------------------------------------------------------------------------------------------------
void DemoScene::rotating( const bool _rotating )
{
  m_rotating = _rotating;
}
//-----------------------------------------------------------------------------------------------------
void DemoScene::generateNewGeometry()
{
  makeCurrent();
  m_meshIndex = (m_meshIndex + 1) % m_meshes.size();
  m_meshVBO.reset(
        sizeof(GLfloat),
        m_meshes[m_meshIndex].getNVertData(),
        m_meshes[m_meshIndex].getNNormData(),
        m_meshes[m_meshIndex].getNUVData()
        );
  loadMesh();
  auto uvdata = m_meshes[m_meshIndex].getAttribData(MeshAttributes::UV);
  for (int i = 0; i < 4; ++i)
    std::cout<<uvdata[i]<<'\t';
  std::cout<<'\n';
}
//-----------------------------------------------------------------------------------------------------
void DemoScene::nextMaterial()
{
  makeCurrent();
  m_currentMaterial = (m_currentMaterial + 1) % m_materials.size();
  m_materials[m_currentMaterial]->apply();
//  loadMesh();

}
//-----------------------------------------------------------------------------------------------------

void DemoScene::renderScene()
{
  Scene::renderScene();

  // Scope the using declaration
  {
    using namespace SceneMatrices;
    m_matrices[MODEL_VIEW] = glm::rotate(m_matrices[MODEL_VIEW], glm::radians(-1.0f * m_rotating), glm::vec3(0.0f, 1.0f, 0.0f));
  }

  m_materials[m_currentMaterial]->update();

  glDrawArrays(GL_TRIANGLES, 0, m_meshes[m_meshIndex].getNVertData()/3);
}
//-----------------------------------------------------------------------------------------------------
