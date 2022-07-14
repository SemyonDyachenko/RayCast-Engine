#pragma once
#ifndef LAYER_STACK_H
#define LAYER_STACK_H


#include <vector>
#include "Layer.h"

class Layer;

class LayerStack {
public:
	LayerStack() = default;
	~LayerStack();

	void PushLayer(Layer* layer);
	void PushOverlay(Layer* overlay);
	void PopLayer(Layer* layer);
	void PopOverlay(Layer* overlay);

	std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
	std::vector<Layer*>::iterator end() { return m_Layers.end(); }

private:
	std::vector<Layer*> m_Layers;
	int m_layerIndex = 0;
};



#endif