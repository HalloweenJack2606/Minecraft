#pragma once
#include "Core/Base.h"
#include "Registry/Material.h"

namespace Minecraft
{
	class Block
	{
	public:
		Block(const Material& material) : m_Material(material) {}

		Block& SetHarvestLevel(u32 harvestLevel) { m_HarvestLevel = harvestLevel; return *this; }
	private:
		Material m_Material;
		u32 m_HarvestLevel = -1;
	};
}