#include "MaterialScene.h"

MaterialScene::MaterialScene()
{
    std::vector<Vertex> raw = OBJLoader::loadObjModel("resources/vanilla/obj/globe-sphere.obj");
    m_Sphere = new Mesh(raw.data(), raw.size(), 0, 0, "resources/vanilla/obj/globe-sphere.obj");


    m_Shader = new Shader("resources/shaders/materials/rbp_vertex_shader.glsl", "resources/shaders/materials/rbp_fragment_shader.glsl");

    m_Camera = new Camera();
    m_Camera->SetAspectRatio(400,300);
    m_Camera->SetFov(60);

    m_Camera->SetPosition({ 0,0,1 });

    m_DirectionalLight = new Light(0, LightMode::DIRECTIONAL_LIGHT);
    m_DirectionalLight->SetPosition({ 5, 5, 5 });
    m_DirectionalLight->SetAmbientColor({ 150,150,150 });

    m_Material = nullptr;

    FrameBufferProps props;
    props.Width = 400;
    props.Height = 300;
    props.Attachments = { FrameBufferTextureFormat::RGBA8,FrameBufferTextureFormat::RED_INTEGER,FrameBufferTextureFormat::Depth };
    m_FrameBuffer = FrameBuffer::Create(props);

    m_Material = new PBRMaterial();
}


MaterialScene::~MaterialScene()
{
    delete m_Sphere;
    delete m_Material;
}

void MaterialScene::ApplyMaterial(MaterialStructure& material)
{
	m_CurrentMaterial = material;
}


void MaterialScene::LoadMaterial()
{
  
    m_Material->ApplyAlbedoMap(new Texture(m_CurrentMaterial.AlbedoColor.c_str()));
    m_Material->ApplyNormalMap(new Texture(m_CurrentMaterial.NormalMap.c_str()));
    m_Material->ApplyMetallicMap(new Texture(m_CurrentMaterial.MetallicMap.c_str()));
    m_Material->ApplyRoughnessMap(new Texture(m_CurrentMaterial.RoughnessMap.c_str()));
    m_Material->ApplyAoMap(new Texture(m_CurrentMaterial.AoMap.c_str()));

}

void MaterialScene::Update(float DeltaTime)
{
    m_Camera->Update(true);

    m_Shader->use();
    m_Shader->SetMat4("ProjectionMatrix", m_Camera->GetProjectionMatrix());
    m_Shader->SetMat4("ViewMatrix", m_Camera->GetViewMatrix());
    m_Shader->SetVec3("camPos", m_Camera->GetPosition());
}

void MaterialScene::Render()
{
    glm::mat4 transformMatrix = glm::translate(glm::mat4(1.0f), {0.0f,0.0f,0.0f}) * glm::scale(glm::mat4(1.0f), {1.0f,1.0f,1.0f});

    m_FrameBuffer->Bind();
    Renderer::SetClearColor({ 0.25,0.25,0.25 });
    Renderer::Clear();
    Renderer::SetViewport({ 0, 0, m_FrameBuffer->GetFrameBufferProps().Width, m_FrameBuffer->GetFrameBufferProps().Height });
	
    m_Shader->use();
    m_Shader->SetMat4("ModelMatrix", transformMatrix);
    m_Shader->setInt("lightCount", 1);

    m_DirectionalLight->SetUniforms(*m_Shader);
	
    if (m_Material)
        if (m_Material->IsActive()) {
            m_Shader->use();
            m_Material->SetUniforms(*m_Shader);
        }

    if (m_Material) {
        if (m_Material->IsActive()) {
            m_Shader->use();
            m_Sphere->UseSolidColor(false);
            m_Sphere->OnRender(*m_Shader);
        }
    }
    
	
    m_Sphere->UseSolidColor(true);
    glm::vec3 color = { 0.8,0.8,0.8 };
    m_Sphere->SetSolidColor(color);
    m_Sphere->OnRender(*m_Shader);
	
    m_FrameBuffer->Unbind();
}
