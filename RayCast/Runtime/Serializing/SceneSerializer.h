#ifndef SCENE_SERIALIZER_H
#define SCENE_SERIALIZER_H

#include <fstream>
#include "../../EntryPoint/Editor/EditorScene.h"
#include <yaml-cpp/yaml.h>
#include <sstream>



class SceneSerializer {
public:
	SceneSerializer(EditorScene& scene);

	void Serialize(std::string filepath);
	
	bool Deserialize(const std::string& filepath,EditorScene& scene);
	bool DeserializeRuntime(const std::string& filepath);

	~SceneSerializer() {}

private:
	EditorScene* m_Scene;
};


#endif