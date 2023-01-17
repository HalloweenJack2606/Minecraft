#pragma once
#define GLEW_STATIC
#include <gl/glew.h>
#include <GLFW/glfw3.h>

namespace Minecraft
{
	struct WindowProps
	{
		const char* title = "Minecraft";
		int width = 1280, height = 720;
	};

	class Window {
	public:
		void OnCreate();
		void OnDestroy();

		void Clear();
		void SwapBuffers();
		void PollEvents();

		void Close() const { glfwSetWindowShouldClose(m_pGLFWWindow, true); }
		void ToggleWireframe();

		void* GetNativeWindow() const { return m_pGLFWWindow; }

		const bool ShouldClose() const { return glfwWindowShouldClose(m_pGLFWWindow); }
	private:
		bool m_bWireframe = false;

		GLFWwindow* m_pGLFWWindow = nullptr;
		WindowProps m_WindowProps = WindowProps();
	};
}
