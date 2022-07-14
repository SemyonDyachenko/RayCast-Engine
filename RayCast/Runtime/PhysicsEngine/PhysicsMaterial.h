#pragma once


#include <filesystem>

#include <yaml-cpp/yaml.h>
#include <sstream>
#include <fstream>


class PhysicsMaterial {
private:
	std::string m_Name;
public:
	float m_Friction;
	float m_Bounciness;

	

	PhysicsMaterial() { m_Friction = 1.0f; m_Bounciness = 1.0f; }
	PhysicsMaterial(float friction, float bounciness)
		: m_Friction(friction),
		m_Bounciness(bounciness)
	{

	}
	
	void SetName(std::string name) {
		m_Name = name;
	}

	std::string GetName() {
		return m_Name;
	}
};

class PhysicsMaterialController {
public:
	PhysicsMaterialController() {}

	~PhysicsMaterialController() {}

	static bool Serialize(std::string path,PhysicsMaterial material) {
		std::filesystem::path fsPath = path;
		std::string filename = fsPath.stem().string();

		YAML::Emitter out;
		out << YAML::BeginMap;
		out << YAML::Key << "PhysicsMaterial" << YAML::Value << filename;

		out << YAML::Key << "Friction" << YAML::Value << material.m_Friction;
		out << YAML::Key << "Bounciness" << YAML::Value << material.m_Bounciness;

		out << YAML::EndMap;

		std::ofstream fout(path);
		fout << out.c_str();

		return true;
	}

	static PhysicsMaterial Deserialize(std::string path) {
		PhysicsMaterial material;
		std::ifstream stream(path);
		std::stringstream strStream;

		std::filesystem::path fsPath = path;

		strStream << stream.rdbuf();

		YAML::Node data = YAML::Load(strStream.str());

		if (!data["PhysicsMaterial"])
			return {};

		std::string sceneName = data["PhysicsMaterial"].as<std::string>();


		auto friction = data["Friction"];
		auto bounciness = data["Bounciness"];
		

		if (friction && bounciness) {
			material.m_Friction = friction.as<float>();
			material.m_Bounciness = bounciness.as<float>();

			std::cout << fsPath.stem().string();
			material.SetName(fsPath.stem().string());
		}

		return material;
	}
};