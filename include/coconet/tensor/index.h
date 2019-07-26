#ifndef COCONET_TENSOR_TENSOR_INDEX_H_
#define COCONET_TENSOR_TENSOR_INDEX_H_

#include <cstdint>
#include <cstring>
#include <cassert>
#include <stdexcept>
#include <memory>
#include <utility>
#include <initializer_list>
#include <coconet/core/type.h>
#include <coconet/util/smallvector.h>


namespace coconet
{
	using DimVector = SmallVector<idx_type, 5>;
	using StrideVector = SmallVector<idx_type, 5>;

    inline DimVector sort_index(DimVector dim)
    {
        DimVector sorted(dim.size());
        for (int i = 0; i < dim.size(); ++i)
            sorted[i] = i;

        for (int i = 0; i < dim.size() - 1; i++)
            for (int j = 0; j < dim.size() - 1 - i; j++)
                if (dim[j] < dim[j + 1])
                {
                    std::swap(dim[j], dim[j + 1]);
                    std::swap(sorted[j], sorted[j + 1]);
                }

        return sorted;
    }
} // namespace coconet

#endif