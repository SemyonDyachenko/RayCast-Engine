#ifndef EDITOR_SCENE_2D_H
#define EDITOR_SCENE_2D_H

#include <GL/glew.h>


#include "../../Runtime/Entity/Scene.h"


class EditorScene2D : public Scene {
public:
	virtual void OnCreate() override;

	virtual void OnDestroy() override;

	virtual void OnActivate() override;

	virtual Entity& CreateEntity(unsigned int id, std::string name) override;

	virtual void DeleteEntity(unsigned int id) override;

	virtual void OnDeactivate() override;

	virtual void OnUpdate(float DeltaTime) override;

	virtual void OnRender() override;
private:

};


#endif