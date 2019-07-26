#ifndef COCONET_COTENSOR_TENSOR_H_
#define COCONET_COTENSOR_TENSOR_H_

#include <memory>
#include <stdexcept>

#include <coconet/core/type.h>
#include <coconet/tensor/tensor.h>
#include <coconet/tensor/index.h>

#include <coconet/cotensor/storage.h>

namespace coconet
{
	template<class T>
	class CoTensor: public ITensor
	{
	public:
		using value_type = T;
		using self_type = CoTensor<T>;
		using base_type = ITensor;

		using raw_pointer = self_type * ;
		using raw_const_pointer = const self_type*;
		using shared_pointer = std::shared_ptr<self_type>;
		using reference = self_type & ;
		using const_reference = const self_type&;
	private:
		std::unique_ptr<CoTensorStorage<T>> _rep;
		DimVector _dimensions;
		StrideVector _strides;
		idx_type _offset;
	public:
		CoTensor();
		explicit CoTensor(const DimVector& dimensions);
		explicit CoTensor(const DimVector& dimensions, const StrideVector& strides);

		CoTensor(const CoTensor& other) = delete;
		CoTensor(CoTensor&& other) = delete;
		CoTensor& operator= (const CoTensor& other) = delete;
		CoTensor& operator= (CoTensor&& other) = delete;

	public:
		device_id device();
		DataType dtype() const;
		bool equal(const ITensor& other) const;

		idx_type ndimension() const;
		idx_type offset() const;
		PlatformType platform() const;
		DimVector size() const;
		idx_type size(idx_type i) const;
		StrideVector stride() const;
		idx_type stride(idx_type i) const;
		std::string to_string() const;
	};

	template class CoTensor<f32>;
	template class CoTensor<f64>;
	template class CoTensor<i8>;
	template class CoTensor<i16>;
	template class CoTensor<i32>;
	template class CoTensor<i64>;
	template class CoTensor<u8>;

	using FloatCoTensor = CoTensor<f32>;
	using DoubleCoTensor = CoTensor<f64>;
	using CharCoTensor = CoTensor<i8>;
	using ShortCoTensor = CoTensor<i16>;
	using IntCoTensor = CoTensor<i32>;
	using LongCoTensor = CoTensor<i64>;
	using ByteCoTensor = CoTensor<u8>;

	template<class T>
	inline CoTensor<T>::CoTensor()
	{
	}

	template<class T>
	inline CoTensor<T>::CoTensor(const DimVector & dimensions)
		: _rep(nullptr), _dimensions(dimensions), _strides(dimensions.size(), 0), _offset(0)
	{
		idx_type cum_stride = 1;
		for (int i = _strides.size() - 1; i >=0; --i)
		{
			_strides[i] = cum_stride;
			cum_stride *= _dimensions[i];
		}
	}

	template<class T>
	inline CoTensor<T>::CoTensor(const DimVector & dimensions, const StrideVector & strides)
		: _rep(nullptr), _dimensions(dimensions), _strides(strides), _offset(0)
	{
	}
	template<class T>
	inline device_id CoTensor<T>::device()
	{
		return 0;
	}
	template<class T>
	inline bool CoTensor<T>::equal(const ITensor & other) const
	{
		return false;
	}
	template<class T>
	inline idx_type CoTensor<T>::ndimension() const
	{
		return _dimensions.size();
	}
	template<class T>
	inline idx_type CoTensor<T>::offset() const
	{
		return _offset;
	}
	template<class T>
	inline PlatformType CoTensor<T>::platform() const
	{
		return PlatformType::CPU;
	}
	template<class T>
	inline DimVector CoTensor<T>::size() const
	{
		return _dimensions;
	}
	template<class T>
	inline idx_type CoTensor<T>::size(idx_type i) const
	{
		auto shape_size = _dimensions.size();
		if (i >= 0 && i < _dimensions.size())
			return _dimensions[i];
		else if (i <= -1 && i >= -_dimensions.size())
			return _dimensions[shape_size + i];
		else
			throw std::runtime_error("Dimension out of range");
	}
	template<class T>
	inline StrideVector CoTensor<T>::stride() const
	{
		return _strides;
	}
	template<class T>
	inline idx_type CoTensor<T>::stride(idx_type i) const
	{
		auto shape_size = _strides.size();
		if (i >= 0 && i < _strides.size())
			return _strides[i];
		else if (i <= -1 && i >= -_strides.size())
			return _strides[shape_size + i];
		else
			throw std::runtime_error("Dimension out of range");
	}
	template<class T>
	inline std::string CoTensor<T>::to_string() const
	{
		return "";
	}
}

#endif // !COCONET_COTENSOR_TENSOR_H_
