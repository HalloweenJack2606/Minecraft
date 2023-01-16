#pragma once
#include "Core/Base.h"

#define SHADER_VERTEX_POSITION 0
#define SHADER_UV_POSITION 1

#define RENDERER_MAX_SPRITES 2048
#define RENDERER_SPRITE_SIZE (sizeof(float) * 6)
#define RENDERER_BUFFER_SIZE (RENDERER_SPRITE_SIZE * 16 * RENDERER_MAX_SPRITES)
#define RENDERER_INDICES_SIZE (RENDERER_MAX_SPRITES * 36 * sizeof(unsigned int))

#include "Graphics/Resources/Shader.h"
#include "Registry/Registry.h"

namespace Minecraft
{
	struct RendererData
	{
		u32 vao;
		u32 vbo;
		u32 ibo;

		Shader shader;

		vec4 cubeVertexPositions[8] = {};
	};

	class Renderer
	{
	public:
		static void Init();
		static void Shutdown();

		static void Push(const Block& id, const vec3& pos);
		static void Flush();
	private:
		static RendererData s_RenderData;
	};
}
