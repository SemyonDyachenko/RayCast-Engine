#ifndef SCENE_SERIALIZER_H
#define SCENE_SERIALIZER_H

#include <fstream>
#include <yaml-cpp/yaml.h>
#include <sstream>

#include "../Entity/Scene.h"



namespace RayCast {

	class SceneSerializer {
	public:
		SceneSerializer(Scene& scene);

		void Serialize(std::string filepath);

		bool Deserialize(const std::string& filepath, Scene& scene);
		bool DeserializeRuntime(const std::string& filepath);

		~SceneSerializer() {}

	private:
		Scene* m_Scene;
	};

}

#endif