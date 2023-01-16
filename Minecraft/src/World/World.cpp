#include "World.h"

namespace Minecraft
{
	World::World()
	{
		m_TestChunk = Chunk();
	}

	World::~World()
	{

	}

	void World::OnUpdate(const float& dt)
	{
		m_TestChunk.Render();
	}
}
