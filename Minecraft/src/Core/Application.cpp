#include "Core/Application.h"
#include "Registry/Registry.h"
#include "Graphics/Rendering/Renderer.h"
#include "Core/Input.h"

namespace Minecraft
{
	Application* Application::s_pThisApp;

	Application::Application()
	{
		m_Window = new Window();
		m_Window->OnCreate();
		Registry::Init();
		Renderer::Init();
		s_pThisApp = this;
	}

	Application::~Application()
	{
		m_Window->OnDestroy();
		Renderer::Shutdown();
	}

	void Application::Run()
	{
		float deltaTime = 0.0f;
		float lastTime = 0.0f;

		while (!m_Window->ShouldClose())
		{
			if (Input::IsKeyReleased(Key::Escape)) m_Window->Close();
			if (Input::IsKeyReleased(Key::T)) m_Window->ToggleWireframe();

			float currentTime = (float)glfwGetTime();
			deltaTime = currentTime - lastTime;
			lastTime = currentTime;
			std::cout << 1.0f / deltaTime << std::endl;

			m_Window->Clear();
			Input::OnUpdate();
			m_World.OnUpdate(deltaTime);
			Renderer::Flush();
			m_Window->SwapBuffers();
			m_Window->PollEvents();
		}
	}
}