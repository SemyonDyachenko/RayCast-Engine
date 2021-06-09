#include "LayerStack.h"

LayerStack::~LayerStack()
{
}

void LayerStack::PushLayer(Layer* layer)
{
	m_Layers.emplace(m_Layers.begin() + m_layerIndex, layer);
	m_layerIndex++;
	layer->Attach();
}

void LayerStack::PushOverlay(Layer* overlay)
{
	m_Layers.emplace_back(overlay);
	overlay->Attach();
}

void LayerStack::PopLayer(Layer* layer)
{
	auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
	if (it != m_Layers.end()) {
		m_Layers.erase(it);
		layer->Detach();
		m_layerIndex--;
	}
}	

void LayerStack::PopOverlay(Layer* overlay)
{
	auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
	if (it != m_Layers.end()) {
		overlay->Detach();
		m_Layers.erase(it);
		
	}
}

