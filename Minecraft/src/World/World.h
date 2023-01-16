#pragma once
#include "World/Generation/Chunk.h"

namespace Minecraft
{
	class World
	{
	public:
		World();
		~World();

		void OnUpdate(const float& dt);
	private:
		Chunk m_TestChunk;
	};
}