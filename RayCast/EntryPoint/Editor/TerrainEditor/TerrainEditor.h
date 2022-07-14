#ifndef TERRAIN_EDITOR_H
#define TERRAIN_EDITOR_H

#include "../SceneHierarchy/SceneHierarchy.h"

class TerrainEditor
{
public:
	TerrainEditor();
	virtual ~TerrainEditor();

	void Update(float DeltaTime);

	void Render(EditorScene & scene,SceneHierarchy & sceneHierarchy);

	void Open() { m_Opened = true; }
	void Close() { m_Opened = false; }

private:
	bool m_Opened = false;

	Entity* m_Entity;
};


#endif