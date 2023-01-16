#pragma once
#include "Core/Base.h"
#include "Registry/Block.h"

namespace Minecraft
{
	typedef std::map<std::string, Material> MaterialMap;
	typedef std::map<std::string, Block> BlockMap;

	class Registry
	{
	public:
		static void Init();

		//Registry
		template<class T>
		static T Register(const std::string& name, T t) {}

		template<>
		static Material Register<Material>(const std::string& name, Material material)
		{
			s_Materials.push_back(material);
		}

		template<>
		static Block Register<Block>(const std::string& name, Block block)
		{
			s_Blocks.push_back(block);
		}


		//Getters
		template<class T>
		static T Get(const u32& id) {}

		template<>
		static Material Get<Material>(const u32& id) { s_Materials[id]; }

		template<>
		static Block Get<Block>(const u32& id) { s_Blocks[id]; }
	private:
		static void RegisterMaterials();
		static void RegisterBlocks();
	private:
		static std::vector<Material> s_Materials;
		static std::vector<Block> s_Blocks;
	};
}