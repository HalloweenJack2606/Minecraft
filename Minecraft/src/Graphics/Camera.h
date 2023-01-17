#pragma once
#include "Core/Base.h"

namespace Minecraft
{
	class Camera
	{
	public:
		Camera();

		void OnUpdate(float dt);
	private:
		mat4 CalculateView();
		void CalculateProjection();
	public:
		vec3 position = vec3(0.0f, 0.0f, 10.0f);
		float speed = 30.0f;
	private:
		float m_Near = 0.1f;
		float m_Far = 1000.0f;
		float m_FOV = 100.0f;

		vec2 m_Viewport = vec2(1280, 720); //@note: magic number!

		vec3 m_Front = vec3(0.0f, 0.0f, -1.0f);
		vec3 m_WorldUp = vec3(0.0f, 1.0f, 0.0f);
		vec3 m_Up = vec3(0.0f, 1.0f, 0.0f);
		vec3 m_Right = vec3(0.0f);

		mat4 m_ProjectionMatrix = mat4(1.0f);
		mat4 m_ViewMatrix = mat4(1.0f);
	};
}