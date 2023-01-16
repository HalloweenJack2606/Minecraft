#include "Registry/Registry.h"

namespace Minecraft
{
	std::vector<Block> Registry::s_Blocks;
	std::vector<Material> Registry::s_Materials;

	void Registry::Init()
	{
		RegisterMaterials();
		RegisterBlocks();
	}

	void Registry::RegisterMaterials()
	{
		Registry::Register<Material>("air", Material());
		Registry::Register<Material>("grass", Material());
		Registry::Register<Material>("rock", Material());
	}

	void Registry::RegisterBlocks()
	{
		Material air = Registry::Get<Material>("air");
		Material grass = Registry::Get<Material>("grass");
		//Material rock = Registry::Get<Material>("rock");

		Registry::Register<Block>("air", Block(air));
		Registry::Register<Block>("grass", Block(grass));
	}
}