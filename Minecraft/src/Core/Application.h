#pragma once
#include "Core/Window.h"
#include "World/World.h"

int main(int argc, char** argv);

namespace Minecraft
{
	class Application
	{
	public:
		Application();
		~Application();

		inline Window& GetWindow() const { return *m_Window; }

		static Application* GetApp() { return s_pThisApp; }
	private:
		void Run();
	private:
		friend int ::main(int argc, char** agrv);

		static Application* s_pThisApp;

		Window* m_Window = nullptr;
		World m_World;
	};
}
