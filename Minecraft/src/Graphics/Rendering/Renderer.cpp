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

		glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, nullptr, GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(SHADER_VERTEX_POSITION);
		glEnableVertexAttribArray(SHADER_UV_POSITION);

		glVertexAttribPointer(SHADER_VERTEX_POSITION, 3, GL_FLOAT, GL_FALSE, RENDERER_SPRITE_SIZE, (void*)(0 * sizeof(float)));
		glVertexAttribPointer(SHADER_UV_POSITION, 3, GL_FLOAT, GL_FALSE, RENDERER_SPRITE_SIZE, (void*)(0 * sizeof(float)));

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_RenderData.vbo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, RENDERER_INDICES_SIZE, nullptr, GL_DYNAMIC_DRAW);

		s_RenderData.cubeVertexPositions[0] = vec4(-0.5f, -0.5f, -0.5f, 1.0f);
		s_RenderData.cubeVertexPositions[1] = vec4( 0.5f, -0.5f, -0.5f, 1.0f);
		s_RenderData.cubeVertexPositions[2] = vec4( 0.5f,  0.5f, -0.5f, 1.0f);
		s_RenderData.cubeVertexPositions[3] = vec4(-0.5f,  0.5f, -0.5f, 1.0f);
		s_RenderData.cubeVertexPositions[4] = vec4(-0.5f, -0.5f,  0.5f, 1.0f);
		s_RenderData.cubeVertexPositions[5] = vec4( 0.5f, -0.5f,  0.5f, 1.0f);
		s_RenderData.cubeVertexPositions[6] = vec4( 0.5f,  0.5f,  0.5f, 1.0f);
		s_RenderData.cubeVertexPositions[7] = vec4(-0.5f,  0.5f,  0.5f, 1.0f);
	}

	void Renderer::Shutdown()
	{
		glDeleteVertexArrays(1, &s_RenderData.vao);
		glDeleteBuffers(1, &s_RenderData.vbo);
		glDeleteBuffers(1, &s_RenderData.ibo);
	}

	void Renderer::Push(const Block& id, const vec3& pos)
	{
		mat4 transform = mat4(1.0f);
		transform = translate(transform, pos);

		static constexpr u32 cubeVertexCount = 8;
		for (int i = 0; i < cubeVertexCount; i++)
		{
			
		}
	}

	void Renderer::Flush()
	{

	}
}