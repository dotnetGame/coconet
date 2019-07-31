#ifndef COCONET_TENSOR_STORAGE_H_
#define COCONET_TENSOR_STORAGE_H_

#include <memory>
#include <coconet/core/type.h>
#include <coconet/tensor/allocator.h>

namespace coconet
{
    class Storage
    {
    public:
		
		virtual char* data_ptr() noexcept = 0;
		virtual const char* data_ptr() const noexcept = 0;
		virtual DataType dtype() const = 0;

		virtual PlatformType platform() const = 0;
		virtual void resize_(idx_type n) = 0;
		virtual std::int32_t element_size() const = 0;
	};
}

#endif //! COCONET_TENSOR_STORAGE_H_