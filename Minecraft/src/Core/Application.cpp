#include "Core/Application.h"
#include "Registry/Registry.h"
#include "Graphics/Rendering/Renderer.h"

namespace Minecraft
{
	Application::Application()
	{
		m_Window.OnCreate();
		Registry::Init();
		Renderer::Init();
	}

	Application::~Application()
	{
		m_Window.OnDestroy();
		Renderer::Shutdown();
	}

	void Application::Run()
	{
		float deltaTime = 0.0f;
		float lastTime = 0.0f;

		while (!m_Window.ShouldClose())
		{
			float currentTime = (float)glfwGetTime();
			deltaTime = currentTime - lastTime;
			lastTime = currentTime;

			m_World.OnUpdate(deltaTime);

			m_Window.Clear();
			Renderer::Flush();
			m_Window.SwapBuffers();
			m_Window.PollEvents();
		}
	}
}