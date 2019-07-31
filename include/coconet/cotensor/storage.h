#ifndef COCONET_COTENSOR_STORAGE_H_
#define COCONET_COTENSOR_STORAGE_H_

#include <memory>
#include <coconet/tensor/storage.h>
#include <coconet/cotensor/allocator.h>

namespace coconet
{
	class CoTensorStorage: public Storage
	{
	private:
		char* _data;
		idx_type _len;
		DataType _dtype;
		std::unique_ptr<Allocator> _allocator;
	public:
		CoTensorStorage();
		CoTensorStorage(const CoTensorStorage& other);
		CoTensorStorage(CoTensorStorage&& other);
		~CoTensorStorage();
		CoTensorStorage& operator= (const CoTensorStorage& other);
		CoTensorStorage& operator= (CoTensorStorage&& other);
		
		
		void swap(CoTensorStorage& other) noexcept;

		virtual char* data_ptr() noexcept override;
		virtual const char* data_ptr() const noexcept override;
		virtual DataType dtype() const override;
		virtual std::int32_t element_size() const override;
		virtual PlatformType platform() const override;
		virtual void resize_(idx_type n) override;
	};
}


#endif //!COCONET_COTENSOR_STORAGE_H_