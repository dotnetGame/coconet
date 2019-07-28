#ifndef COCONET_TENSOR_STORAGE_H_
#define COCONET_TENSOR_STORAGE_H_

#include <memory>
#include <coconet/tensor/allocator.h>

namespace coconet
{
    class Storage
    {
    public:

    private:
		std::unique_ptr<Allocator> _allocator;
		std::unique_ptr<char, BufferDeleter> _buffer;
	};
}

#endif //! COCONET_TENSOR_STORAGE_H_