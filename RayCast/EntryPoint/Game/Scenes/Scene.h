#pragma once
#ifndef SCEME_H
#define SCENE_H

class Scene {
public:
	virtual void OnCreate() = 0;
	virtual void OnDestroy() = 0;

	virtual void OnActivate() = 0;

	virtual void OnDeactivate() = 0;

	virtual void OnUpdate(float DeltaTime) = 0;
	virtual void OnRender() = 0;
};



#endif