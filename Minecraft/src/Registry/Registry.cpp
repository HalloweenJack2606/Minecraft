#include "Registry/Registry.h"

namespace Minecraft
{
	std::vector<Block> Registry::s_Blocks;
	MaterialMap Registry::s_Materials;
	TextureMap Registry::s_Textures;

	void Registry::Init()
	{
		RegisterMaterials();
		RegisterBlocks();
		RegisterTextures();
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
		Material rock = Registry::Get<Material>("rock");

		Registry::Register<Block>("air", Block(air).SetTransparent());
		Registry::Register<Block>("grass", Block(grass));
	}

	void Registry::RegisterTextures()
	{
		Registry::Register<TextureCreationInfo>("blocks", TextureCreationInfo{
			.path = "assets/textures/blocks.png"
			});
	}
}