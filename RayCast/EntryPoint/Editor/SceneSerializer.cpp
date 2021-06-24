#include "../../stdafx.h"
#include "SceneSerializer.h"


#include <yaml-cpp/yaml.h>


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
	out << YAML::BeginMap << v.x << v.y << v.z << YAML::EndMap;
	return out;
}

YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec4& v)
{
	out << YAML::Flow;
	out << YAML::BeginMap << v.x << v.y << v.z << v.w << YAML::EndMap;
	return out;
}

static void SerializeObject(YAML::Emitter& out, EditorSceneObject* object)
{
	out << YAML::BeginMap;
	out << YAML::Key << "Object" << YAML::Value << object->GetId();
	

	out << YAML::Key << "NameMap";
	out << YAML::BeginMap;

	out << YAML::Key << "Name" << YAML::Value << object->GetName();

	out << YAML::EndMap;


	out << YAML::Key << "Transform";
	out << YAML::BeginMap;

	out << YAML::Key << "Position" << YAML::Value << object->GetPosition();
	out << YAML::Key << "Rotation" << YAML::Value << object->GetRotation();
	out << YAML::Key << "Scale" << YAML::Value << object->GetScale();

	out << YAML::EndMap;

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
		out << YAML::Key << "Objects" << YAML::Value << YAML::BeginMap;

		for (size_t i = 0; i < m_Scene->GetObjects().size(); i++) {
			SerializeObject(out, m_Scene->GetObjects()[i]);
		}



		out << YAML::EndMap;
		out << YAML::EndMap;

		std::ofstream fout(filepath);
		fout << out.c_str();
}

bool SceneSerializer::Deserialize(std::string filepath,EditorScene& scene)
{
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

