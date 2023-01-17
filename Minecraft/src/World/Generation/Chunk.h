#pragma once
#include "Core/Base.h"
#include "Registry/Registry.h"

namespace Minecraft
{
	class Chunk
	{
	public:
		Chunk(vec3 offset);
		~Chunk();

		void Render();

		void GetNeighbors(vec3 pos, std::vector<vec4>& neighbors);

		bool BlockInBounds(vec3 pos);
		u32 PositionToBlockID(const vec3 pos);
		Block GetBlockData(const vec3& pos);
	public:
		vec3 offset = vec3(0.0f); //@note: chunk number
		vec3 position = vec3(0.0f); //@note: chunk position
	private:
		bool m_bDirty = true;
		std::vector<s32> m_Blocks;
	};
}
