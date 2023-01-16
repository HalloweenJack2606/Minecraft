#pragma once
#include "Core/Window.h"
#include "World/World.h"

namespace Minecraft
{
	class Application
	{
	public:
		Application();
		~Application();

		void Run();
	private:
		Window m_Window;
		World m_World;
	};
}
