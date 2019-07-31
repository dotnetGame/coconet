#include <coconet/cotensor/storage.h>

namespace coconet
{
	CoTensorStorage::CoTensorStorage()
		: _data(nullptr), _len(0), _allocator(std::make_unique<CoTensorAllocator>())
	{
	}

	CoTensorStorage::CoTensorStorage(const CoTensorStorage & other)
		: _data(nullptr), _len(0), _allocator(std::make_unique<CoTensorAllocator>())
	{
		CoTensorStorage temp;
		temp._data = new char[other._len];
		temp._len = other._len;

		std::memcpy(temp._data, other._data, other._len * sizeof(char));

		this->swap(temp);
	}

	CoTensorStorage::CoTensorStorage(CoTensorStorage && other)
		: _data(other._data), _len(other._len), _allocator(std::make_unique<CoTensorAllocator>())
	{
	}

	CoTensorStorage::~CoTensorStorage()
	{
		delete[] _data;
		_data = nullptr;
		_len = 0;
	}

	CoTensorStorage& CoTensorStorage::operator=(const CoTensorStorage& other)
	{
		CoTensorStorage temp;
		temp._data = new char[other._len];
		temp._len = other._len;

		std::memcpy(temp._data, other._data, other._len * sizeof(char));

		this->swap(temp);
		return *this;
	}

	CoTensorStorage& CoTensorStorage::operator=(CoTensorStorage && other)
	{
		_data = other._data;
		_len = other._len;

		return *this;
	}

	char* CoTensorStorage::data_ptr() noexcept
	{
		return _data;
	}

	const char* CoTensorStorage::data_ptr() const noexcept
	{
		return _data;
	}

	void CoTensorStorage::swap(CoTensorStorage & other) noexcept
	{
		std::swap(_data, other._data);
		std::swap(_len, other._len);
		std::swap(_dtype, other._dtype);
		std::swap(_allocator, other._allocator);
	}

	inline DataType CoTensorStorage::dtype() const
	{
		return _dtype;
	}

	inline std::int32_t CoTensorStorage::element_size() const
	{
		return dtype_size(_dtype);
	}

	inline PlatformType CoTensorStorage::platform() const
	{
		return PlatformType::CPU;
	}

	void CoTensorStorage::resize_(idx_type s)
	{
		if (s >= 0 && s != _len)
		{
			CoTensorStorage temp;
			temp._data = new char[s];
			temp._len = s;

			if (s > _len)
				std::memcpy(temp._data, _data, _len * sizeof(char));
			else
				std::memcpy(temp._data, _data, s * sizeof(char));

			this->swap(temp);
		}
	}
}