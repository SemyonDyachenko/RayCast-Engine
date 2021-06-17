#ifndef SCENE_SERIALIZER_H
#define SCENE_SERIALIZER_H

#include <fstream>

#include "EditorScene.h"

#include "EditorSceneObject.h"


#include <yaml-cpp/yaml.h>



class SceneSerializer {
public:
	SceneSerializer(EditorScene& scene);

	void Serialize(std::string filepath);
	
	bool Deserialize(std::string filepath,EditorScene& scene);


	~SceneSerializer() {}

private:
	EditorScene* m_Scene;
};


#endif