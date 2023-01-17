#include "Graphics/Resources/Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace Minecraft
{
	Texture::Texture(const TextureCreationInfo& info)
	{
		if (info.path.empty())
		{
			std::cout << "Invalid texture path" << std::endl;
			return;
		}

		s32 width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		auto data = stbi_load(info.path.c_str(), &width, &height, &channels, 0);
		m_Width = width;
		m_Height = height;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_ID);
		glTextureStorage2D(m_ID, 1, GL_RGBA8, m_Width, m_Height);
		glTextureParameteri(m_ID, GL_TEXTURE_MIN_FILTER, (info.filterMin == TextureFilter::FILTER_LINEAR ? GL_LINEAR : GL_NEAREST));
		glTextureParameteri(m_ID, GL_TEXTURE_MAG_FILTER, (info.filterMag == TextureFilter::FILTER_LINEAR ? GL_LINEAR : GL_NEAREST));
		glTextureParameteri(m_ID, GL_TEXTURE_WRAP_S, GetGLWrapEquivalent(info.wrapS));
		glTextureParameteri(m_ID, GL_TEXTURE_WRAP_T, GetGLWrapEquivalent(info.wrapT));

		glTextureSubImage2D(m_ID, 0, 0, 0, m_Width, m_Height, GL_RGBA, GL_UNSIGNED_BYTE, data);
		stbi_image_free(data);
	}
	void Texture::Bind(u32 slot) const
	{
		glBindTextureUnit(slot, m_ID);
	}

	void Texture::Unbind(u32 slot) const
	{
		glBindTextureUnit(slot, 0);
	}

	void Texture::Free()
	{
		glDeleteTextures(1, &m_ID);
	}

	GLenum Texture::GetGLWrapEquivalent(const TextureWrap& wrap) const
	{
		switch (wrap)
		{
		case TextureWrap::WRAP_REPEAT:
			return GL_REPEAT;
		case TextureWrap::WRAP_MIRRORED_REPEAT:
			return GL_MIRRORED_REPEAT;
		case TextureWrap::WRAP_CLAMP:
			return GL_CLAMP;
		case TextureWrap::WRAP_CLAMP_TO_EDGE:
			return GL_CLAMP_TO_EDGE;
		case TextureWrap::WRAP_MIRROR_CLAMP_TO_EDGE:
			return GL_MIRROR_CLAMP_TO_EDGE;
		}

		return NULL;
	}
}