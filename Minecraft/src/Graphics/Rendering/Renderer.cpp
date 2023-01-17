#include "Graphics/Rendering/Renderer.h"
#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/gtx/transform.hpp>

namespace Minecraft
{
	RendererData Renderer::s_RenderData;

	void Renderer::Init()
	{
		s_RenderData.shader.Create("assets/shaders/default.glsl");

		glGenVertexArrays(1, &s_RenderData.vao);
		glGenBuffers(1, &s_RenderData.vbo);
		glGenBuffers(1, &s_RenderData.ibo);

		glBindVertexArray(s_RenderData.vao);
		glBindBuffer(GL_ARRAY_BUFFER, s_RenderData.vbo);

		glBufferData(GL_ARRAY_BUFFER, s_RenderData.maxVertices * sizeof(QuadVertex), nullptr, GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(SHADER_VERTEX_POSITION);
		glEnableVertexAttribArray(SHADER_UV_POSITION);

		glVertexAttribPointer(SHADER_VERTEX_POSITION, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(0 * sizeof(float)));
		glVertexAttribPointer(SHADER_UV_POSITION, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

		//EBO
		u32* quadIndices = new u32[s_RenderData.maxIndices];
		u32 offset = 0;

		for (u32 i = 0; i < s_RenderData.maxIndices; i += 6)
		{
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;

			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;

			offset += 4;
		}

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_RenderData.ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(u32) * s_RenderData.maxIndices, quadIndices, GL_STATIC_DRAW);
		delete[] quadIndices;

		s_RenderData.quadVertexBufferBase = new QuadVertex[s_RenderData.maxVertices];
		s_RenderData.quadVertexBufferPtr = s_RenderData.quadVertexBufferBase;

		//@note: top
		s_RenderData.topVertexPositions[0] = vec4(-0.5f, 0.5f, -0.5f, 1.0f);
		s_RenderData.topVertexPositions[1] = vec4( 0.5f, 0.5f, -0.5f, 1.0f);
		s_RenderData.topVertexPositions[2] = vec4( 0.5f, 0.5f,  0.5f, 1.0f);
		s_RenderData.topVertexPositions[3] = vec4(-0.5f, 0.5f,  0.5f, 1.0f);

		//@note: bottom
		s_RenderData.bottomVertexPositions[0] = vec4(-0.5f, -0.5f,  0.5f, 1.0f);
		s_RenderData.bottomVertexPositions[1] = vec4( 0.5f, -0.5f,  0.5f, 1.0f);
		s_RenderData.bottomVertexPositions[2] = vec4( 0.5f, -0.5f, -0.5f, 1.0f);
		s_RenderData.bottomVertexPositions[3] = vec4(-0.5f, -0.5f, -0.5f, 1.0f);

		//@note: left
		s_RenderData.backVertexPositions[0] = vec4(-0.5f,  0.5f,  0.5f, 1.0f);
		s_RenderData.backVertexPositions[1] = vec4(-0.5f, -0.5f,  0.5f, 1.0f);
		s_RenderData.backVertexPositions[2] = vec4(-0.5f, -0.5f, -0.5f, 1.0f);
		s_RenderData.backVertexPositions[3] = vec4(-0.5f,  0.5f, -0.5f, 1.0f);

		//@note: right
		s_RenderData.frontVertexPositions[0] = vec4(0.5f,  0.5f, -0.5f, 1.0f);
		s_RenderData.frontVertexPositions[1] = vec4(0.5f, -0.5f, -0.5f, 1.0f);
		s_RenderData.frontVertexPositions[2] = vec4(0.5f, -0.5f,  0.5f, 1.0f);
		s_RenderData.frontVertexPositions[3] = vec4(0.5f,  0.5f,  0.5f, 1.0f);

		//@note: front
		s_RenderData.rightVertexPositions[0] = vec4(-0.5f,  0.5f,  0.5f, 1.0f);
		s_RenderData.rightVertexPositions[1] = vec4( 0.5f,  0.5f,  0.5f, 1.0f);
		s_RenderData.rightVertexPositions[2] = vec4( 0.5f, -0.5f,  0.5f, 1.0f);
		s_RenderData.rightVertexPositions[3] = vec4(-0.5f, -0.5f,  0.5f, 1.0f);

		//@note: back
		s_RenderData.leftVertexPositions[0] = vec4(-0.5f, -0.5f, -0.5f, 1.0f);
		s_RenderData.leftVertexPositions[1] = vec4( 0.5f, -0.5f, -0.5f, 1.0f);
		s_RenderData.leftVertexPositions[2] = vec4( 0.5f,  0.5f, -0.5f, 1.0f);
		s_RenderData.leftVertexPositions[3] = vec4(-0.5f,  0.5f, -0.5f, 1.0f);

		s_RenderData.blocksTexture = Registry::Get<Texture>("blocks");
	}

	void Renderer::Shutdown()
	{
		glDeleteVertexArrays(1, &s_RenderData.vao);
		glDeleteBuffers(1, &s_RenderData.vbo);
		glDeleteBuffers(1, &s_RenderData.ibo);
	}

	void Renderer::Push(const Block& id, const vec3& pos, const Direction& faces)
	{
		mat4 transform = mat4(1.0f);
		transform = translate(transform, pos);

		if ((faces & Direction::UP) == Direction::UP) PushFace(transform, 0, id.textureID);
		if ((faces & Direction::DOWN) == Direction::DOWN) PushFace(transform, 1, id.textureID);
		if ((faces & Direction::BACK) == Direction::BACK) PushFace(transform, 2, id.textureID);
		if ((faces & Direction::FRONT) == Direction::FRONT) PushFace(transform, 3, id.textureID);
		if ((faces & Direction::RIGHT) == Direction::RIGHT) PushFace(transform, 4, id.textureID);
		if ((faces & Direction::LEFT) == Direction::LEFT) PushFace(transform, 5, id.textureID);
	}

	void Renderer::Flush()
	{
		if (s_RenderData.quadIndexCount == 0) return;

		s_RenderData.blocksTexture.Bind();

		s_RenderData.shader.Bind();
		s_RenderData.shader.SetMat4("uPV", s_RenderData.pvMatrix);
		
		u32 dataSize = (u32)((BYTE*)s_RenderData.quadVertexBufferPtr - (BYTE*)s_RenderData.quadVertexBufferBase);
		glBufferSubData(GL_ARRAY_BUFFER, 0, dataSize, s_RenderData.quadVertexBufferBase);
		
		glDrawElements(GL_TRIANGLES, s_RenderData.quadIndexCount, GL_UNSIGNED_INT, nullptr);
		s_RenderData.shader.Unbind();

		s_RenderData.quadIndexCount = 0;
		s_RenderData.quadVertexBufferPtr = s_RenderData.quadVertexBufferBase;
	}

	void Renderer::PushFace(const mat4& transform, u8 index, const u32& texID)
	{
		if (s_RenderData.quadIndexCount + 6 > s_RenderData.maxIndices) Flush();

		vec4* vertexPositions;
		if (index == 0) vertexPositions = s_RenderData.topVertexPositions; 
		if (index == 1) vertexPositions = s_RenderData.bottomVertexPositions; 
		if (index == 2) vertexPositions = s_RenderData.backVertexPositions;
		if (index == 3) vertexPositions = s_RenderData.frontVertexPositions;
		if (index == 4) vertexPositions = s_RenderData.rightVertexPositions;
		if (index == 5) vertexPositions = s_RenderData.leftVertexPositions;

		u32 texIndex = index;

		if (texIndex > 2) texIndex = 2;

		vec2 texSize = s_RenderData.blocksTexture.GetSize();

		vec2 texCoords[4] = {
			{(texIndex * SPRITE_SIZE) / texSize.x, (texID * SPRITE_SIZE) / texSize.y},
			{((texIndex + 1) * SPRITE_SIZE) / texSize.x, (texID * SPRITE_SIZE) / texSize.y},
			{((texIndex + 1) * SPRITE_SIZE) / texSize.x, ((texID + 1) * SPRITE_SIZE) / texSize.y},
			{(texIndex * SPRITE_SIZE) / texSize.x, ((texID + 1) * SPRITE_SIZE) / texSize.y}
		};

		if (index <= 3) 
		{ 
			vec2 copy[4];
			std::copy(std::begin(texCoords), std::end(texCoords), std::begin(copy));
			texCoords[0] = copy[1];
			texCoords[1] = copy[2];
			texCoords[2] = copy[3];
			texCoords[3] = copy[0];
		}
		else if (index == 5)
		{
			vec2 copy[4];
			std::copy(std::begin(texCoords), std::end(texCoords), std::begin(copy));
			texCoords[0] = copy[2];
			texCoords[1] = copy[3];
			texCoords[2] = copy[0];
			texCoords[3] = copy[1];
		}

		static constexpr u32 cubeVertexCount = 4;
		for (int i = 0; i < cubeVertexCount; i++)
		{
			s_RenderData.quadVertexBufferPtr->position = transform * vertexPositions[i];
			s_RenderData.quadVertexBufferPtr->uv = texCoords[i];
			s_RenderData.quadVertexBufferPtr++;
		}

		s_RenderData.quadIndexCount += 6;
	}
}