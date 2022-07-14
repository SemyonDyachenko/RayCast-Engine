#ifndef APPLICATION_H
#define APPLICATION_H



#include "Window.h"
#include <stack>
#include "LayerStack.h"
#include "Input.h"

namespace RayCast {

	class Game
	{
	public:
		Game(const std::string& name = "Default App");

		virtual ~Game() = default;

		void Init(WindowProps& props);

		void PushLayer(Layer* layer);

		static Window& GetWindow() {
			return *m_Window;
		}

		LayerStack GetLayers() { return m_Layers; }

		void Shutdown();

		void Run();
	private:


	private:
		static std::unique_ptr<Window> m_Window;
		bool isRunning = true;
		bool m_IsPlayMode;
		float m_LastFrameTime = 0.0f;

		LayerStack m_Layers;

	private:
		static Game* s_Instance;
	};

	Game* CreateGame();

}

#endif