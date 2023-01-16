#pragma once
#include <glm/glm.hpp>

//std
#include <map>
#include <string>
#include <vector>

using namespace glm;

#define CHUNK_SIZE (vec3 {16.0f, 16.0f, 16.0f})
#define CHUNK_VOLUME (CHUNK_SIZE.x * CHUNK_SIZE.y * CHUNK_SIZE.z)


typedef std::uint8_t  u8;
typedef std::uint16_t u16;
typedef std::uint32_t u32;
typedef std::uint64_t u64;

typedef std::int8_t  s8;
typedef std::int16_t s16;
typedef std::int32_t s32;
typedef std::int64_t s64;

typedef unsigned char BYTE;