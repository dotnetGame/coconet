#ifndef COCONET_COTENSOR_STORAGE_H_
#define COCONET_COTENSOR_STORAGE_H_

#include <memory>

namespace coconet
{
	template <class T>
	class CoTensorStorage
	{
	public:
		using value_type = T;
		using self_type = CoTensorStorage<T>;

		using pointer = self_type*;
		using const_pointer = const self_type*;
		using reference = self_type&;
		using const_reference = const self_type&;
	private:
		T* _data;
		idx_type _len;
	public:
		CoTensorStorage();
		CoTensorStorage(const CoTensorStorage& other);
		CoTensorStorage(CoTensorStorage&& other);
		~CoTensorStorage();
		CoTensorStorage& operator= (const CoTensorStorage& other);
		CoTensorStorage& operator= (CoTensorStorage&& other);

		void swap(CoTensorStorage& other) noexcept;
	};

	template class CoTensorStorage<f32>;
	template class CoTensorStorage<f64>;
	template class CoTensorStorage<i8>;
	template class CoTensorStorage<i16>;
	template class CoTensorStorage<i32>;
	template class CoTensorStorage<i64>;
	template class CoTensorStorage<u8>;

	using FloatCoTensorStorage = CoTensorStorage<f32>;
	using DoubleCoTensorStorage = CoTensorStorage<f64>;
	using CharCoTensorStorage = CoTensorStorage<i8>;
	using ShortCoTensorStorage = CoTensorStorage<i16>;
	using IntCoTensorStorage = CoTensorStorage<i32>;
	using LongCoTensorStorage = CoTensorStorage<i64>;
	using ByteCoTensorStorage = CoTensorStorage<u8>;

	template<class T>
	inline CoTensorStorage<T>::CoTensorStorage()
		: _data(nullptr), _len(0)
	{
	}

	template<class T>
	inline CoTensorStorage<T>::CoTensorStorage(const CoTensorStorage & other)
		: _data(nullptr), _len(0)
	{
		CoTensorStorage temp;
		temp._data = new T[other._len];
		temp._len = other._len;

		std::memcpy(temp._data, other._data, other._len * sizeof(T));

		this->swap(temp);
	}
	template<class T>
	inline CoTensorStorage<T>::CoTensorStorage(CoTensorStorage && other)
		: _data(other._data), _len(other._len)
	{
	}

	template<class T>
	inline CoTensorStorage<T>::~CoTensorStorage()
	{
		delete[] _data;
		_data = nullptr;
		_len = 0;
	}

	template<class T>
	inline CoTensorStorage<T> & CoTensorStorage<T>::operator=(const CoTensorStorage<T> & other)
	{
		CoTensorStorage temp;
		temp._data = new T[other._len];
		temp._len = other._len;

		std::memcpy(temp._data, other._data, other._len * sizeof(T));

		this->swap(temp);
	}
	template<class T>
	inline CoTensorStorage<T> & CoTensorStorage<T>::operator=(CoTensorStorage<T> && other)
	{
		_data = other._data;
		_len = other._len;

		return *this;
	}

	template<class T>
	inline void CoTensorStorage<T>::swap(CoTensorStorage & other) noexcept
	{
		std::swap(_data, other._data);
		std::swap(_len, other._len);
	}
}


#endif //!COCONET_COTENSOR_STORAGE_H_