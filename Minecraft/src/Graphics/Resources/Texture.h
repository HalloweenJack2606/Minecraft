#pragma once
#include "Core/Base.h"
#define GLEW_STATIC
#include <GL/glew.h>

namespace Minecraft
{
	enum class TextureFilter : u8
	{
		FILTER_NEAREST = 0,
		FILTER_LINEAR = 1,
	};

	enum class TextureWrap : u8
	{
		WRAP_REPEAT = 0,
		WRAP_MIRRORED_REPEAT = 1,
		WRAP_CLAMP = 2,
		WRAP_CLAMP_TO_EDGE = 3,
		WRAP_MIRROR_CLAMP_TO_EDGE = 4
	};

	struct TextureCreationInfo
	{
		std::string path = "";
		TextureFilter filterMin = TextureFilter::FILTER_NEAREST, filterMag = TextureFilter::FILTER_NEAREST;
		TextureWrap wrapS = TextureWrap::WRAP_REPEAT, wrapT = TextureWrap::WRAP_REPEAT;
	};

	class Texture
	{
	public:
		Texture() = default;
		Texture(const TextureCreationInfo& info);

		vec2 GetSize() const { return vec2(m_Width, m_Height); }

		void Bind(u32 slot = 0) const;
		void Unbind(u32 slot = 0) const;
		void Free();
	private:
		GLenum GetGLWrapEquivalent(const TextureWrap& wrap) const;
	private:
		u32 m_ID = 0;
		u32 m_Width = 0, m_Height = 0;

		BYTE* m_ImageData = nullptr;
	};
}