#include "Core/Window.h"
#include <iostream>

namespace Minecraft
{
	void Window::OnCreate()
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		if (!glfwInit()) std::cout << "Error initializing GLFW" << std::endl;

		m_pGLFWWindow = glfwCreateWindow(m_WindowProps.width, m_WindowProps.height, m_WindowProps.title, nullptr, nullptr);
		glfwMakeContextCurrent(m_pGLFWWindow);

		glewExperimental = true;
		if (glewInit() != GLEW_OK) std::cout << "Error initializing GLEW" << std::endl;

		glClearColor(0.53f, 0.81f, 0.92f, 1.0f);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);
	}

	void Window::OnDestroy()
	{
		glfwDestroyWindow(m_pGLFWWindow);
		glfwTerminate();
	}

	void Window::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Window::SwapBuffers()
	{
		glfwSwapBuffers(m_pGLFWWindow);
	}

	void Window::PollEvents()
	{
		glfwPollEvents();
	}
}