#pragma once
#include "Core/Base.h"
#include "Registry/Block.h"
#include "Graphics/Resources/Texture.h"

namespace Minecraft
{
	typedef std::map<std::string, Material> MaterialMap;
	typedef std::map<std::string, Block> BlockMap;
	typedef std::map<std::string, Texture> TextureMap;

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
			s_Materials[name] = material;
			return s_Materials[name];
		}

		template<>
		static Block Register<Block>(const std::string& name, Block block)
		{
			s_Blocks.push_back(block);
			return s_Blocks.back();
		}

		template<>
		static TextureCreationInfo Register<TextureCreationInfo>(const std::string& name, TextureCreationInfo info)
		{
			Texture texture(info);
			s_Textures[name] = texture;
			return info;
		}


		//Getters
		template<class T>
		static T Get(const u32& id) {}
		template<class T>
		static T Get(const std::string& name) {}

		template<>
		static Material Get<Material>(const std::string& name) { return s_Materials[name]; }

		template<>
		static Block Get<Block>(const u32& id) { return s_Blocks[id]; }

		template<>
		static Texture Get<Texture>(const std::string& name) { return s_Textures[name]; }
	private:
		static void RegisterMaterials();
		static void RegisterBlocks();
		static void RegisterTextures();
	private:
		static TextureMap s_Textures;
		static MaterialMap s_Materials;
		static std::vector<Block> s_Blocks;
	};
}