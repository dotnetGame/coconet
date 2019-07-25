#ifndef COCONET_CORE_TYPE_H_
#define COCONET_CORE_TYPE_H_

#include <cstdint>

namespace coconet
{
    using f32 = float;
    using f64 = double;
    using i8 = std::int8_t;
    using i16 = std::int16_t;
    using i32 = std::int32_t;
    using i64 = std::int64_t;
    using u8 = std::uint8_t;
    using u16 = std::uint16_t;
    using u32 = std::uint32_t;
    using u64 = std::uint64_t;
    using grad_type = f32;
    using idx_type = i32;
    using size_type = i32;
    using device_id = i32;

    enum LayoutType
    {
        ROW_MAJOR,
        COLUMN_MAJOR
    };

    enum PlatformType
    {
        CPU,
        CUDA,
        OPENCL,
        VULKAN,
        OPENGL
    };

    enum DataType
    {
        BYTE,
        CHAR,
        SHORT,
        INT,
        LONG,
        FLOAT,
        DOUBLE
    };
}


#endif