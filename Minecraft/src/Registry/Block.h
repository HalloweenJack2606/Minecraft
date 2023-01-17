#pragma once
#include "Core/Base.h"
#include "Registry/Material.h"

namespace Minecraft
{
	class Block
	{
	public:
		Block(const Material& material) : m_Material(material) {}

		bool IsTransparent() const { return m_bIsTransparent; }

		Block& SetHarvestLevel(u32 harvestLevel) { m_HarvestLevel = harvestLevel; return *this; }
		Block& SetTransparent() { m_bIsTransparent = true; return *this; }
	private:
		friend class Renderer;

		bool m_bIsTransparent = false;

		u32 m_HarvestLevel = -1;
		u32 textureID = 0;
		Material m_Material;
	};
}