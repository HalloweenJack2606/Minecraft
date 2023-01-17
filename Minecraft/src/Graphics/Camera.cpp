#include "Graphics/Camera.h"
#include "Graphics/Rendering/Renderer.h"
#include <glm/gtx/transform.hpp>
#include "Core/Input.h"

namespace Minecraft
{
	Camera::Camera()
	{
		CalculateProjection();
	}

	void Camera::OnUpdate(float dt)
	{
		auto inputData = Input::GetInputData();

		auto prevFov = m_FOV;
		m_FOV -= (float)inputData.scrollY;
		if (m_FOV < 1.0f) m_FOV = 1.0f;
		if (m_FOV > 45.0f) m_FOV = 45.0f;
		if (m_FOV != prevFov) CalculateProjection();

		m_ViewMatrix = CalculateView();
		Renderer::SetPVMatrix(m_ProjectionMatrix * m_ViewMatrix);


		vec3 direction;
		direction.x = cos(radians(inputData.yaw)) * cos(radians(inputData.pitch));
		direction.y = sin(radians(inputData.pitch));
		direction.z = sin(radians(inputData.yaw)) * cos(radians(inputData.pitch));
		m_Front = normalize(direction);
		m_Right = normalize(cross(m_Front, m_WorldUp));
		m_Up = normalize(cross(m_Right, m_Front));

		float velocity = speed * dt;

		if (Input::IsKeyPressed(Key::D)) position += m_Right * velocity;
		if (Input::IsKeyPressed(Key::A)) position -= m_Right * velocity;
		if (Input::IsKeyPressed(Key::W)) position += m_Front * velocity;
		if (Input::IsKeyPressed(Key::S)) position -= m_Front * velocity;

		if (Input::IsKeyPressed(Key::Space)) position.y += velocity;
		if (Input::IsKeyPressed(Key::LeftShift)) position.y -= velocity;
	}

	mat4 Camera::CalculateView()
	{
		return lookAt(position, position + m_Front, m_Up);
	}
	void Camera::CalculateProjection()
	{
		m_ProjectionMatrix = perspective(radians(m_FOV), (float)m_Viewport.x / (float)m_Viewport.y, m_Near, m_Far);
	}
}
