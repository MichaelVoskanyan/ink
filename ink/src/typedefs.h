#ifndef INK_TYPEDEFS_H
#define INK_TYPEDEFS_H

#include <cstdint>
#include <memory>
#include <vector>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef float f32;
typedef double f64;

// Code below from https://github.com/TheCherno/Hazel
// I don't wanna type std::shared_ptr<VertexArray> or
// const std::vector<float> &identifier every time

template <typename T>
using Ref = std::shared_ptr<T>;

template <typename T>
using Scope = std::unique_ptr<T>;

template <typename T>
using Vec = std::vector<T>;

#endif