#include "World/Generation/Chunk.h"
#include "Registry/Registry.h"
#include "Graphics/Rendering/Renderer.h"

namespace Minecraft
{
	Chunk::Chunk()
	{
		m_Blocks.reserve(CHUNK_VOLUME);
		for (int i = 0; i < CHUNK_VOLUME; i++) m_Blocks.push_back(1);
	}

	Chunk::~Chunk()
	{

	}

	void Chunk::Render()
	{
		for (u32 x = position.x; x < (position.x + CHUNK_SIZE.x); x++)
		{
			for (u32 y = position.y; y < (position.y + CHUNK_SIZE.y); y++)
			{
				for (u32 z = position.z; z < (position.z + CHUNK_SIZE.z); z++)
				{
					vec3 pos = vec3(x, y, z);
					Renderer::Push(GetBlockData(pos), pos);
				}
			}
		}
	}

	bool Chunk::BlockInBounds(vec3 pos)
	{
		pos -= position;
		return pos.x >= 0 && pos.y >= 0 && pos.z >= 0 &&
			pos.x < CHUNK_SIZE.x&& pos.y < CHUNK_SIZE.y&& pos.z < CHUNK_SIZE.z;
	}

	Block Chunk::GetBlockData(const vec3& pos)
	{
		u32 id = PositionToBlockID(pos);
		return Registry::Get<Block>(id);
	}

	u32 Chunk::PositionToBlockID(const vec3 pos)
	{
		if (BlockInBounds(pos)) return m_Blocks[pos.x + CHUNK_SIZE.x * (pos.y + CHUNK_SIZE.y * pos.z)];
		return 0;
	}
}