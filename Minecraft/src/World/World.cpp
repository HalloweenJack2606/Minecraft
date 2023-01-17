#include "World/World.h"

namespace Minecraft
{
	World::World()
	{
		m_Camera = Camera();
	}

	World::~World()
	{
		for (const auto& c : m_Chunks)
		{
			//delete c.second;
		}
	}

	void World::OnUpdate(const float& dt)
	{
		static bool firstPass = true;
		auto currentChunk = PositionToChunk(m_Camera.position);
		if (currentChunk != m_LastChunk || firstPass)
		{
			firstPass = false;
			m_LastChunk = currentChunk;
			
			std::vector<vec2> newChunks;
			std::vector<vec2> chunksToLoad;
			CalculateNewChunks(newChunks);
			UnloadOldChunks(newChunks, chunksToLoad);
			LoadChunks(chunksToLoad);
		}

		m_Camera.OnUpdate(dt);

		//std::cout << m_LoadedChunksList.size() << std::endl;

		for (const auto& chunk : m_LoadedChunksList)
		{
			if(m_Chunks[chunk] != nullptr) m_Chunks[chunk]->Render();
		}
	}

	vec2 World::PositionToChunk(vec3 pos)
	{
		vec2 offset = vec2(floor(pos.x / CHUNK_SIZE.x), floor(pos.z / CHUNK_SIZE.z));
		//std::cout << "(" << offset.x << ", " << offset.y << ")" << std::endl;
		return offset;
	}

	void World::CalculateNewChunks(std::vector<vec2>& newChunks)
	{
		for (int i = 0; i < m_RenderDistance; i++)
		{
			if (i == 0)
			{
				newChunks.push_back(m_LastChunk);
				newChunks.push_back(m_LastChunk + vec2( 1.0f,  0.0f));
				newChunks.push_back(m_LastChunk + vec2(-1.0f,  0.0f));
				newChunks.push_back(m_LastChunk + vec2( 0.0f,  1.0f));
				newChunks.push_back(m_LastChunk + vec2( 0.0f, -1.0f));
			}
			else
			{
				vec2 maxLeft = m_LastChunk, maxRight = m_LastChunk, maxFront = m_LastChunk, maxBack = m_LastChunk;

				for (const auto& c : newChunks)
				{
					if (c.x < maxLeft.x) maxLeft = c;
					if (c.x > maxRight.x) maxRight = c;
					if (c.y > maxFront.y) maxFront = c;
					if (c.y < maxBack.y) maxBack = c;
				}

				newChunks.push_back(maxLeft + vec2(-1.0f,  0.0f));
				newChunks.push_back(maxLeft + vec2( 0.0f,  1.0f));
				newChunks.push_back(maxLeft + vec2( 0.0f, -1.0f));

				newChunks.push_back(maxRight + vec2( 1.0f,  0.0f));
				newChunks.push_back(maxRight + vec2( 0.0f,  1.0f));
				newChunks.push_back(maxRight + vec2( 0.0f, -1.0f));

				newChunks.push_back(maxFront + vec2( 1.0f, 0.0f));
				newChunks.push_back(maxFront + vec2(-1.0f, 0.0f));
				newChunks.push_back(maxFront + vec2( 0.0f, 1.0f));

				newChunks.push_back(maxBack + vec2( 1.0f,  0.0f));
				newChunks.push_back(maxBack + vec2(-1.0f,  0.0f));
				newChunks.push_back(maxBack + vec2( 0.0f, -1.0f));
			}
		}

		//vec2 maxLeft = m_LastChunk, maxRight = m_LastChunk, maxFront = m_LastChunk, maxBack = m_LastChunk;
		//
		//for (const auto& c : newChunks)
		//{
		//	if (c.x < maxLeft.x) maxLeft = c;
		//	if (c.x > maxRight.x) maxRight = c;
		//	if (c.y > maxFront.y) maxFront = c;
		//	if (c.y < maxBack.y) maxBack = c;
		//}
		//
		//{
		//	for (u32 i = 0; i < m_RenderDistance; i++)
		//	{
		//
		//	}
		//}

		SortVec2(newChunks);
		newChunks.erase(std::unique(newChunks.begin(), newChunks.end()), newChunks.end());
	}

	void World::UnloadOldChunks(const std::vector<vec2>& newChunks, std::vector<vec2>& chunksToLoad)
	{
		std::vector<vec2> unload;

		for (const auto& older : m_LoadedChunksList)
		{
			bool found = false;
			for (const auto& newer : newChunks)
			{
				if (newer == older)
				{
					found = true;
					break;
				}
			}
			if (!found) unload.push_back(older);
		}

		for (const auto& newer : newChunks)
		{
			bool found = false;
			for (const auto& older : m_LoadedChunksList)
			{
				if (newer == older)
				{
					found = true;
					break;
				}
			}
			if (!found) chunksToLoad.push_back(newer);
		}

		SortVec2(unload);
		unload.erase(std::unique(unload.begin(), unload.end()), unload.end());

		for (const auto& c : unload)
		{
			delete m_Chunks[c];
			m_Chunks[c] = nullptr;
			m_LoadedChunksList.erase(std::find(m_LoadedChunksList.begin(), m_LoadedChunksList.end(), c));
		}
	}

	void World::LoadChunks(const std::vector<vec2>& chunksToLoad)
	{
		for (const auto& c : chunksToLoad)
		{
			m_Chunks[c] = new Chunk(vec3(c.x, 0.0f, c.y));
			m_LoadedChunksList.push_back(c);
		}
	}
}
