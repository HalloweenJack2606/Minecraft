#pragma once
#include "Core/Base.h"

#define SHADER_VERTEX_POSITION 0
#define SHADER_UV_POSITION 1

#include "Graphics/Resources/Shader.h"
#include "Registry/Registry.h"

namespace Minecraft
{
	struct QuadVertex
	{
		vec3 position;
		vec2 uv;
	};

	struct RendererData
	{
		static constexpr u32 maxQuads = 4000;
		static constexpr u32 maxVertices = maxQuads * 4;
		static constexpr u32 maxIndices = maxQuads * 6;

		u32 vao;
		u32 vbo;
		u32 ibo;

		Shader shader;

		QuadVertex* quadVertexBufferBase = nullptr;
		QuadVertex* quadVertexBufferPtr = nullptr;

		u32 quadIndexCount = 0;

		vec4 topVertexPositions[4] = {};
		vec4 bottomVertexPositions[4] = {};
		vec4 backVertexPositions[4] = {};
		vec4 frontVertexPositions[4] = {};
		vec4 rightVertexPositions[4] = {};
		vec4 leftVertexPositions[4] = {};

		mat4 pvMatrix = mat4(1.0f);

		Texture blocksTexture;
	};

	class Renderer
	{
	public:
		static void Init();
		static void Shutdown();

		inline static void SetPVMatrix(const mat4&& pv) { s_RenderData.pvMatrix = pv; }

		static void Push(const Block& id, const vec3& pos, const Direction& faces);
		static void Flush();
	private:
		static void PushFace(const mat4& transform, u8 index, const u32& texID);
	private:
		static RendererData s_RenderData;
	};
}
