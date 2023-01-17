#pragma once
#include "World/Generation/Chunk.h"
#include "Graphics/Camera.h"
#include "Core/Base.h"
#include <glm/gtx/hash.hpp>

namespace Minecraft
{
	typedef std::unordered_map<vec2, Chunk*> ChunkMap;

	class World
	{
	public:
		World();
		~World();

		void OnUpdate(const float& dt);
	private:
		vec2 PositionToChunk(vec3 pos);
		void CalculateNewChunks(std::vector<vec2>& newChunks);
		void UnloadOldChunks(const std::vector<vec2>& newChunks, std::vector<vec2>& chunksToLoad);
		void LoadChunks(const std::vector<vec2>& chunksToLoad);
	private:
		u8 m_RenderDistance = 8;

		vec2 m_LastChunk = vec2(10.0f);

		std::vector<vec2> m_LoadedChunksList;

		Camera m_Camera;

		ChunkMap m_Chunks;
	};
}