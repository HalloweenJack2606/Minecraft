#pragma once
#include "Core/Base.h"
#include "Registry/Registry.h"

namespace Minecraft
{
	class Chunk
	{
	public:
		Chunk();
		~Chunk();

		void Render();

		bool BlockInBounds(vec3 pos);
		u32 PositionToBlockID(const vec3 pos);
		Block GetBlockData(const vec3& pos);
	public:
		vec3 offset = vec3(0.0f); //@note: chunk number
		vec3 position = vec3(0.0f); //@note: chunk position
	private:
		bool m_bDirty = true;
		std::vector<u32> m_Blocks;
	};
}
