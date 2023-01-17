#include "Core/Window.h"
#include "Core/Input.h"
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

		glfwSetInputMode(m_pGLFWWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		glewExperimental = true;
		if (glewInit() != GLEW_OK) std::cout << "Error initializing GLEW" << std::endl;

		glClearColor(0.53f, 0.81f, 0.92f, 1.0f);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);

		//glfwSwapInterval(0);

		glfwSetKeyCallback(m_pGLFWWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			switch (action)
			{
			case GLFW_PRESS:
				Input::SetKey(key, InputState::PRESS);
				break;
			case GLFW_RELEASE:
				Input::SetKey(key, InputState::RELEASE);
				break;
			case GLFW_REPEAT:
				Input::SetKey(key, InputState::REPEAT);
				break;
			default:
				break;
			}
		});

		glfwSetScrollCallback(m_pGLFWWindow, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			auto& data = Input::GetInputData();
			data.scrollX = xOffset;
			data.scrollY = yOffset;
		});


		glfwSetCursorPosCallback(m_pGLFWWindow, [](GLFWwindow* window, double xPos, double yPos)
		{
			static bool firstMouse = true;
			auto& data = Input::GetInputData();
			if (firstMouse)
			{
				data.cursorX = (float)xPos;
				data.cursorY = (float)yPos;
				firstMouse = false;
			}

			float xOffset = xPos - data.cursorX;
			float yOffset = data.cursorY - yPos;

			data.cursorX = xPos;
			data.cursorY = yPos;

			const float sensitivity = 0.1f;
			xOffset *= sensitivity;
			yOffset *= sensitivity;

			data.yaw += xOffset;
			data.pitch += yOffset;

			if (data.pitch >  data.pitchConstraint) data.pitch = data.pitchConstraint;
			if (data.pitch < -data.pitchConstraint) data.pitch = -data.pitchConstraint;
		});
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

	void Window::ToggleWireframe()
	{
		if (!m_bWireframe) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		m_bWireframe = !m_bWireframe;
	}
}