#pragma once
#include "Core/Base.h"
#include "Core/KeyCodes.h"
#include "Core/MouseCodes.h"

namespace Minecraft
{
	enum class InputState
	{
		NONE = 0,
		RELEASE,
		PRESS,
		REPEAT
	};

	struct InputData
	{
		double scrollX = 0.0;
		double scrollY = 0.0;
		float cursorX = 0.0f;
		float cursorY = 0.0f;
		float pitch = 0.0f;
		float yaw = 0.0f;

		float pitchConstraint = 89.0f;
	};

	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode key);
		static bool IsKeyReleased(KeyCode key);
		static bool IsKeyUp(KeyCode key);

		static bool IsMouseButtonPressed(MouseCode button);
		static vec2 GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();

		static void SetKey(KeyCode key, InputState state);

		static InputData& GetInputData() { return s_InputData; }
	private:
		friend class Application;
		static void OnUpdate();
	private:
		static InputState s_Keys[1024];
		static InputData s_InputData;
	};
}