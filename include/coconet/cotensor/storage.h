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
	public:
		CoTensorStorage();
		CoTensorStorage(const CoTensorStorage& other);
		CoTensorStorage(CoTensorStorage&& other);
		~CoTensorStorage();
		CoTensorStorage& operator= (const CoTensorStorage& other);
		CoTensorStorage& operator= (CoTensorStorage&& other);
		
		char* data_ptr() noexcept;
		const char* data_ptr() const noexcept;
		void swap(CoTensorStorage& other) noexcept;
		void resize(idx_type s);
	};

	CoTensorStorage::CoTensorStorage()
		: Storage(std::make_unique<CoTensorAllocator>()), _data(nullptr), _len(0)
	{
	}

	CoTensorStorage::CoTensorStorage(const CoTensorStorage & other)
		: Storage(std::make_unique<CoTensorAllocator>()), _data(nullptr), _len(0)
	{
		CoTensorStorage temp;
		temp._data = new char[other._len];
		temp._len = other._len;

		std::memcpy(temp._data, other._data, other._len * sizeof(char));

		this->swap(temp);
	}

	CoTensorStorage::CoTensorStorage(CoTensorStorage && other)
		: Storage(std::make_unique<CoTensorAllocator>()), _data(other._data), _len(other._len)
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
	}

	void CoTensorStorage::resize(idx_type s)
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


#endif //!COCONET_COTENSOR_STORAGE_H_