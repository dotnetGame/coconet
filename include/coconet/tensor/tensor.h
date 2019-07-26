#ifndef COCONET_TENSOR_TENSOR_TENSOR_H_
#define COCONET_TENSOR_TENSOR_TENSOR_H_

#include <coconet/core/type.h>
#include <coconet/tensor/index.h>

namespace coconet
{
	class ITensor
	{
	public:
        // virtual char* data_ptr() = 0;
        // virtual const char* data_ptr() const = 0;
        /*virtual device_id device() = 0;
        virtual DataType dtype() const = 0;
        virtual bool equal(const ITensor& other) const = 0;

        virtual idx_type ndimension() const = 0;
        virtual idx_type offset() const = 0;
        virtual void permute_(const DimVector& dims) const = 0;
        virtual PlatformType platform() const = 0;
		virtual DimVector size() const = 0;
		virtual idx_type size(idx_type i) const = 0;
		virtual DimVector stride() const = 0;
		virtual idx_type stride(idx_type i) const = 0;
        virtual std::string to_string() const = 0;*/
	};
}

#endif // !COCONET_CORE_TENSOR_H_
