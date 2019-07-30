#ifndef COCONET_TENSOR_STORAGE_H_
#define COCONET_TENSOR_STORAGE_H_

#include <memory>
#include <coconet/tensor/allocator.h>

namespace coconet
{
    class Storage
    {
    public:
		Storage(std::unique_ptr<Allocator> allocator)
			: _buffer(nullptr)
		{

		}
    private:
		std::unique_ptr<Allocator> _allocator;
		char* _buffer;
	};
}

#endif //! COCONET_TENSOR_STORAGE_H_