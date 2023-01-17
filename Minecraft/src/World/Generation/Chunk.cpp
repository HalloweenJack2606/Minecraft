#include "World/Generation/Chunk.h"
#include "Registry/Registry.h"
#include "Graphics/Rendering/Renderer.h"

namespace Minecraft
{
	Chunk::Chunk(vec3 offset)
		:offset(offset)
	{
		this->position = offset * CHUNK_SIZE;
		m_Blocks.reserve(CHUNK_VOLUME);
		for (int i = 0; i < CHUNK_VOLUME; i++) m_Blocks.push_back(1);
	}

	Chunk::~Chunk()
	{

	}

	void Chunk::Render()
	{
		std::vector<vec4> neighbors;
		neighbors.resize(6);
		for (u32 x = 0; x < CHUNK_SIZE.x; x++)
		{
			for (u32 y = 0; y < CHUNK_SIZE.y; y++)
			{
				for (u32 z = 0; z < CHUNK_SIZE.z; z++)
				{
					vec3 pos = vec3(x, y, z);
					GetNeighbors(pos, neighbors);
					Direction faces = Direction::NONE;
					for (const auto& it : neighbors)
					{
						auto nData = GetBlockData(it);
						if (nData.IsTransparent())
						{
							faces |= (Direction)(it.w);
						}
					}
					Renderer::Push(GetBlockData(pos), pos + position, faces);
				}
			}
		}
	}

	void Chunk::GetNeighbors(vec3 pos, std::vector<vec4>& neighbors)
	{
		u32 i = 0;
		vec4 pos4 = vec4(pos, 0.0f);
		neighbors[i++] = pos4 + vec4( 1.0f,  0.0f,  0.0f, Direction::FRONT);
		neighbors[i++] = pos4 + vec4(-1.0f,  0.0f,  0.0f, Direction::BACK);
		neighbors[i++] = pos4 + vec4( 0.0f,  1.0f,  0.0f, Direction::UP);
		neighbors[i++] = pos4 + vec4( 0.0f, -1.0f,  0.0f, Direction::DOWN);
		neighbors[i++] = pos4 + vec4( 0.0f,  0.0f,  1.0f, Direction::RIGHT);
		neighbors[i++] = pos4 + vec4( 0.0f,  0.0f, -1.0f, Direction::LEFT);
	}

	bool Chunk::BlockInBounds(vec3 pos)
	{
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