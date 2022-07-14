#include "../../stdafx.h"
#include "SceneSerializer.h"

namespace YAML {

	template<>
	struct convert<glm::vec3>
	{
		static Node encode(const glm::vec3& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			node.SetStyle(EmitterStyle::Flow);
			return node;
		}

		static bool decode(const Node& node, glm::vec3& rhs)
		{
			if (!node.IsSequence() || node.size() != 3)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			return true;
		}
	};

	template<>
	struct convert<glm::vec4>
	{
		static Node encode(const glm::vec4& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			node.push_back(rhs.w);
			node.SetStyle(EmitterStyle::Flow);
			return node;
		}

		static bool decode(const Node& node, glm::vec4& rhs)
		{
			if (!node.IsSequence() || node.size() != 4)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			rhs.w = node[3].as<float>();
			return true;
		}
	};

}

YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec3& v)
{
	out << YAML::Flow;
	out << YAML::BeginSeq << v.x << v.y << v.z << YAML::EndSeq;
	return out;
}

YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec4& v)
{
	out << YAML::Flow;
	out << YAML::BeginSeq << v.x << v.y << v.z << v.w << YAML::EndSeq;
	return out;
}

static void SerializeObject(YAML::Emitter& out, Entity entity)
{
	out << YAML::BeginMap;
	out << YAML::Key << "Entity" << YAML::Value << entity.GetId();
	
	if (entity.HasComponent<TagComponent>()) {

		auto& tag = entity.GetComponent<TagComponent>();

		out << YAML::Key << "TagComponent";
		out << YAML::BeginMap;

		out << YAML::Key << "Tag" << YAML::Value << tag.tag;

		out << YAML::EndMap;
	}

	if (entity.HasComponent<TransformComponent>()) {

		auto& tc = entity.GetComponent<TransformComponent>();

		out << YAML::Key << "Transform";
		out << YAML::BeginMap;

		out << YAML::Key << "Position" << YAML::Value << tc.Position;
		out << YAML::Key << "Rotation" << YAML::Value << tc.Rotation;
		out << YAML::Key << "Scale" << YAML::Value << tc.Scale;

		out << YAML::EndMap;

	}

	if (entity.HasComponent<MeshComponent>()) {
		auto& mesh = entity.GetComponent<MeshComponent>();
		out << YAML::Key << "MeshComponent";
		out << YAML::BeginMap;

		out << YAML::Key << "Filename" << YAML::Value << mesh.mesh.GetFilename();
		out << YAML::Key << "SolidColor" << YAML::Value << mesh.mesh.GetSolidColor();

		out << YAML::EndMap;

	}

	if (entity.HasComponent<MaterialComponent>()) {
		auto& material = entity.GetComponent<MaterialComponent>();
		out << YAML::Key << "MaterialComponent";
		out << YAML::BeginMap;

		out << YAML::Key << "Shininess" << YAML::Value << material.material.GetShininess();
		out << YAML::Key << "DiffuseTexture" << YAML::Value << material.material.GetDiffuseTexture().GetFilename();
		out << YAML::Key << "SpecularTexture" << YAML::Value << material.material.GetSpecularTexture().GetFilename();

		out << YAML::EndMap;
	}

	if (entity.HasComponent<BoxColliderComponent>()) {
		auto& boxCollider = entity.GetComponent<BoxColliderComponent>();

		out << YAML::Key << "BoxCollider";
		out << YAML::BeginMap;

		out << YAML::Key << "Size" << YAML::Value << boxCollider.collider.GetSize();
		out << YAML::Key << "Position" << YAML::Value << boxCollider.collider.Position;
		out << YAML::Key << "Center" << YAML::Value << boxCollider.collider.Center;
		out << YAML::Key << "Rotation" << YAML::Value << glm::eulerAngles(boxCollider.collider.Rotation);

		out << YAML::EndMap;
	}

	if (entity.HasComponent<CircleColliderComponent>()) {
		auto& shapeCollider = entity.GetComponent<CircleColliderComponent>();

		out << YAML::Key << "CircleCollider";
		out << YAML::BeginMap;

		out << YAML::Key << "Radius" << YAML::Value << shapeCollider.collider.GetRadius();
		out << YAML::Key << "Position" << YAML::Value << shapeCollider.collider.Position;
		out << YAML::Key << "Center" << YAML::Value << shapeCollider.collider.Center;
		out << YAML::Key << "Rotation" << YAML::Value << glm::eulerAngles(shapeCollider.collider.Rotation);

		out << YAML::EndMap;
	}

	if (entity.HasComponent<RigidBodyComponent>()) {
		auto& rigidbody = entity.GetComponent<RigidBodyComponent>();

		out << YAML::Key << "RigidBodyComponent";
		out << YAML::BeginMap;

		out << YAML::Key << "Mass" << YAML::Value << rigidbody.rigidbody.GetMass();
		out << YAML::Key << "Position" << YAML::Value << rigidbody.rigidbody.GetPosition();
		out << YAML::Key << "Rotation" << YAML::Value << glm::eulerAngles(rigidbody.rigidbody.GetRotation());
		out << YAML::Key << "LinearDrag" << YAML::Value << rigidbody.rigidbody.GetLinearDrag();
		out << YAML::Key << "AngularDrag" << YAML::Value << rigidbody.rigidbody.GetAngularDrag();
		out << YAML::Key << "TakesGravity" << YAML::Value << rigidbody.rigidbody.IsDynamic();

		out << YAML::EndMap;
	}

	if (entity.HasComponent<DirectionalLightComponent>()) {
		auto& light = entity.GetComponent<DirectionalLightComponent>();

		out << YAML::Key << "DirectionalLight";
		out << YAML::BeginMap;

		out << YAML::Key << "Direction" << YAML::Value << light.light.GetDirection();
		out << YAML::Key << "Ambient" << YAML::Value << light.light.GetAmbient();
		out << YAML::Key << "Diffuse" << YAML::Value << light.light.GetDiffuse();
		out << YAML::Key << "Specular" << YAML::Value << light.light.GetSpecular();

		out << YAML::EndMap;
	}

	if (entity.HasComponent<LightPointComponent>()) {
		auto& light = entity.GetComponent<LightPointComponent>();

		out << YAML::Key << "LightPoint";
		out << YAML::BeginMap;

		out << YAML::Key << "Position" << YAML::Value << light.light.GetPosition();
		out << YAML::Key << "Ambient" << YAML::Value << light.light.GetAmbient();
		out << YAML::Key << "Diffuse" << YAML::Value << light.light.GetDiffuse();
		out << YAML::Key << "Specular" << YAML::Value << light.light.GetSpecular();
		out << YAML::Key << "Constant" << YAML::Value << light.light.GetConstant();
		out << YAML::Key << "Linear" << YAML::Value << light.light.GetLinear();
		out << YAML::Key << "Quadratic" << YAML::Value << light.light.GetQuadratic();

		out << YAML::EndMap;
	}


	out << YAML::EndMap;
}


SceneSerializer::SceneSerializer(EditorScene & scene) : m_Scene(&scene)
{
}

void SceneSerializer::Serialize(std::string filepath)
{

		YAML::Emitter out;
		out << YAML::BeginMap;
		out << YAML::Key << "Scene" << YAML::Value << "Untitled";
		out << YAML::Key << "Entities" << YAML::Value << YAML::BeginSeq;

		for(auto & entity : m_Scene->GetManager().GetEntities()) {
			SerializeObject(out,*entity);
		}



		out << YAML::EndSeq;
		out << YAML::EndMap;

		std::ofstream fout(filepath);
		fout << out.c_str();
}

bool SceneSerializer::Deserialize(const std::string& filepath,EditorScene& scene)
{
	std::ifstream stream(filepath);
	std::stringstream strStream;
	strStream << stream.rdbuf();

	YAML::Node data = YAML::Load(strStream.str());

	if (!data["Scene"])
		return false;

	std::string sceneName = data["Scene"].as<std::string>();


	auto entites = data["Entities"];
	if (entites) {
			scene.GetManager().Clear();
			for (auto entity : entites) {
				unsigned int entityid = entity["Entity"].as<unsigned int>();


				std::string tag;
				auto tagComponent = entity["TagComponent"];

				if (tagComponent) {
					tag = tagComponent["Tag"].as<std::string>();
				}

				Entity deserializedEntity = scene.CreateEntity(entityid, tag);
				auto& resultEntity = scene.GetEntity(entityid);

				auto transform = entity["Transform"];

				if (transform) {
					auto& tc = deserializedEntity.GetComponent<TransformComponent>();
					tc.Position = transform["Position"].as<glm::vec3>();
					tc.Rotation = transform["Rotation"].as<glm::vec3>();
					tc.Scale = transform["Scale"].as<glm::vec3>();
				}

				auto meshComponent = entity["MeshComponent"];
				if (meshComponent) {
					auto path = meshComponent["Filename"].as<std::string>();
					auto color = meshComponent["SolidColor"].as<glm::vec3>();

					std::vector<Vertex> rawModel = OBJLoader::loadObjModel(path);
					Mesh mesh(rawModel.data(), rawModel.size(), 0, 0, path);
					resultEntity->AddComponent<MeshComponent>(mesh, color);
				}
			
					auto materialComponent = entity["MaterialComponent"];

					if (materialComponent) {
						auto shininess = materialComponent["Shininess"].as<float>();
						auto diffuseMapPath = materialComponent["DiffuseTexture"].as<std::string>();
						auto specularMapPath = materialComponent["SpecularTexture"].as<std::string>();

						Texture* diffuseTexture = new Texture(diffuseMapPath.c_str(), GL_TEXTURE_2D);
						Texture* specularTexture = new Texture(specularMapPath.c_str(), GL_TEXTURE_2D);

						Material* material = new Material(diffuseTexture,specularTexture,shininess,glm::vec3(1.0f));

						resultEntity->AddComponent<MaterialComponent>(*material);
					}

					auto boxColliderComponent = entity["BoxCollider"];

					if (boxColliderComponent) {
						auto Size = boxColliderComponent["Size"].as<glm::vec3>();
						auto Position = boxColliderComponent["Position"].as<glm::vec3>();
						auto Center = boxColliderComponent["Center"].as<glm::vec3>();
						//auto Rotation = boxColliderComponent["Rotation"].as<glm::vec3>();
						
						resultEntity->AddComponent<BoxColliderComponent>(Size,Position,glm::quat(resultEntity->GetComponent<TransformComponent>().Rotation));

					}

					auto circleColliderComponent = entity["CircleCollider"];

					if (circleColliderComponent) {
						auto Radius = circleColliderComponent["Radius"].as<float>();
						auto Position = circleColliderComponent["Position"].as<glm::vec3>();
						auto Center = circleColliderComponent["Center"].as<glm::vec3>();
						auto Rotation = circleColliderComponent["Rotation"].as<glm::vec3>();

						resultEntity->AddComponent<CircleColliderComponent>(Radius, Center, glm::quat(Rotation));
					}

					auto rigidBodyComponent = entity["RigidBodyComponent"];

					if (rigidBodyComponent) {
						auto Mass = rigidBodyComponent["Mass"].as<float>();
						auto Position = rigidBodyComponent["Position"].as<glm::vec3>();
						auto Rotation = rigidBodyComponent["Rotation"].as<glm::vec3>();
						auto LinearDrag = rigidBodyComponent["LinearDrag"].as<float>();
						auto AngularDrag = rigidBodyComponent["AngularDrag"].as<float>();
						auto TakesGravity = rigidBodyComponent["TakesGravity"].as<bool>();


						if (boxColliderComponent) {
							auto& boxCollider = resultEntity->GetComponent<BoxColliderComponent>();
							RigidBody * rigidbody = new RigidBody(&boxCollider.collider, Mass, LinearDrag, AngularDrag);

							resultEntity->AddComponent<RigidBodyComponent>(*rigidbody);
							auto& entity_rb = resultEntity->GetComponent<RigidBodyComponent>();
							scene.GetPhysicsWorld().AddRigidBody(&entity_rb.rigidbody);
						}
						else if (circleColliderComponent) {
							auto& circleCollider = resultEntity->GetComponent<CircleColliderComponent>();
							RigidBody* rigidbody = new RigidBody(&circleCollider.collider,Mass,LinearDrag,AngularDrag);

							resultEntity->AddComponent<RigidBodyComponent>(*rigidbody);
							auto& entity_rb = resultEntity->GetComponent<RigidBodyComponent>();
							scene.GetPhysicsWorld().AddRigidBody(&entity_rb.rigidbody);
						}
					}

					auto dirLight = entity["DirectionalLight"];

					if (dirLight) {
						auto Direction = dirLight["Direction"].as<glm::vec3>();
						auto Ambient = dirLight["Ambient"].as<glm::vec3>();
						auto Diffuse = dirLight["Diffuse"].as<glm::vec3>();
						auto Specular = dirLight["Specular"].as<glm::vec3>();

						DirectionalLight* light = new DirectionalLight(Direction, Ambient, Diffuse, Specular, { 1.0f,1.0f,1.0f });

						resultEntity->AddComponent<DirectionalLightComponent>(*light);
					}

					auto pointLight = entity["LightPoint"];
					
					if (pointLight) {
						auto Position = pointLight["Direction"].as<glm::vec3>();
						auto Ambient = pointLight["Ambient"].as<glm::vec3>();
						auto Diffuse = pointLight["Diffuse"].as<glm::vec3>();
						auto Specular = pointLight["Specular"].as<glm::vec3>();
						auto Constant = pointLight["Constant"].as<float>();
						auto Linear = pointLight["Linear"].as<float>();
						auto Quadratic = pointLight["Quadratic"].as<float>();

						LightPoint* light = new LightPoint(Position, Ambient, Diffuse, Specular, { 1.0f,1.0f,1.0f },Constant,Linear,Quadratic);

						resultEntity->AddComponent<LightPointComponent>(*light,Position);
					}

			}
		}
	


	/*std::ifstream stream(filepath);

	std::stringstream strStream;

	strStream << stream.rdbuf();

	YAML::Node data = YAML::Load(strStream.str());
	if (!data["Scene"])
		return false;

	std::string sceneName = data["Scene"].as<std::string>();

	auto objects = data["Objects"];

	if (objects) {
		for (auto object : objects) {
			int id = object["Object"].as<int>();

			std::string name;
			auto nameMap = object["NameMap"];
			name = nameMap["Name"].as<std::string>();
		

			EditorSceneObject* new_object = new EditorSceneObject(id,name,"static");

			auto Transform = object["Transform"];

			auto Position = Transform["Position"].as<glm::vec3>();
			auto Rotation = Transform["Rotation"].as<glm::vec3>();
			auto Scale = Transform["Scale"].as<glm::vec3>();

			// TODO: Do deserialize
		}
	}
	*/
	return true;

}

bool SceneSerializer::DeserializeRuntime(const std::string& filepath)
{
	return false;
}

