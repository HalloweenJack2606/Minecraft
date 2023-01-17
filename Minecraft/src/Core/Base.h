#pragma once
#include <glm/glm.hpp>

//std
#include <map>
#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace glm;

#define CHUNK_SIZE (vec3 {16.0f, 2.0f, 16.0f})
#define CHUNK_VOLUME (CHUNK_SIZE.x * CHUNK_SIZE.y * CHUNK_SIZE.z)
#define SPRITE_SIZE 16.0f


typedef std::uint8_t  u8;
typedef std::uint16_t u16;
typedef std::uint32_t u32;
typedef std::uint64_t u64;

typedef std::int8_t  s8;
typedef std::int16_t s16;
typedef std::int32_t s32;
typedef std::int64_t s64;

typedef unsigned char BYTE;

enum class Direction
{
	NONE = 0,
	BACK = 1,
	FRONT = 2,
	LEFT = 4,
	RIGHT = 8,
	UP = 16,
	DOWN = 32
};

inline Direction operator| (Direction a, Direction b)
{
	return static_cast<Direction>(static_cast<int>(a) | static_cast<int>(b));
}

inline Direction operator& (Direction a, Direction b)
{
	return static_cast<Direction>(static_cast<int>(a) & static_cast<int>(b));
}

inline Direction& operator|=(Direction& a, Direction b)
{
	a = a | b;
	return a;
}

inline void SortVec2(std::vector<vec2>& vec)
{
	std::sort(vec.begin(), vec.end(), [](const vec2& lhs, const vec2& rhs) {
		return lhs.x < rhs.x;
		});

	std::sort(vec.begin(), vec.end(), [](const vec2& lhs, const vec2& rhs) {
		return (lhs.x == rhs.x) && (lhs.y < rhs.y);
		});
}