#pragma once

#include <filesystem>

#include <yaml-cpp/yaml.h>
#include <sstream>
#include <fstream>

struct MaterialStructure
{
	std::string AlbedoColor;
	std::string NormalMap;
	std::string MetallicMap;
	std::string RoughnessMap;
	std::string AoMap;

	float specular;
	float metallic;
};


class MaterialController {
public:
	MaterialController() = default;
	~MaterialController() = default;

	static bool Serialize(std::string path,MaterialStructure & structure) {
		std::filesystem::path fsPath = path;
		std::string filename = fsPath.filename().string();

		YAML::Emitter out;
		out << YAML::BeginMap;
		out << YAML::Key << "Material" << YAML::Value << filename;

		out << YAML::Key << "Albedo Map" << YAML::Value << structure.AlbedoColor;
		out << YAML::Key << "Normal Map" << YAML::Value << structure.NormalMap;
		out << YAML::Key << "Metallic Map" << YAML::Value << structure.MetallicMap;
		out << YAML::Key << "Roughness Map" << YAML::Value << structure.RoughnessMap;
		out << YAML::Key << "Ao Map" << YAML::Value << structure.AoMap;

		out << YAML::EndMap;

		std::ofstream fout(path);
		fout << out.c_str();

		return true;
	}

	static MaterialStructure Deserailize(std::string path) {
		MaterialStructure structure;

		std::ifstream stream(path);
		std::stringstream strStream;
		strStream << stream.rdbuf();

		YAML::Node data = YAML::Load(strStream.str());

		if (!data["Material"])
			return {};
		
		std::string sceneName = data["Material"].as<std::string>();

		auto albedoMap = data["Albedo Map"];
		auto normalMap = data["Normal Map"];
		auto metallicMap = data["Metallic Map"];
		auto roughnessMap = data["Roughness Map"];
		auto aoMap = data["Ao Map"];

		if (albedoMap && normalMap && metallicMap && roughnessMap && aoMap) {
			structure.AlbedoColor = albedoMap.as<std::string>();
			structure.NormalMap = normalMap.as<std::string>();
			structure.MetallicMap = metallicMap.as<std::string>();
			structure.RoughnessMap = roughnessMap.as<std::string>();
			structure.AoMap = aoMap.as<std::string>();
		}

		return structure;
	}
};