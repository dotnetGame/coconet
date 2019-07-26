#ifndef COCONET_TENSOR_COTENSOR_TENSOR_H_
#define COCONET_TENSOR_COTENSOR_TENSOR_H_

#include <coconet/core/type.h>
#include <coconet/tensor/tensor.h>
#include <coconet/tensor/index.h>

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
	public:
		CoTensor();
		explicit CoTensor(const DimVector& dimensions);
		explicit CoTensor(const DimVector& dimensions, const DimVector& strides);
		CoTensor(const T& t);

		CoTensor(const CoTensor& other) = delete;
		CoTensor(CoTensor&& other) = delete;
		CoTensor& operator= (const CoTensor& other) = delete;
		CoTensor& operator= (CoTensor&& other) = delete;
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
	{
	}

	template<class T>
	inline CoTensor<T>::CoTensor(const DimVector & dimensions, const DimVector & strides)
	{
	}

	template<class T>
	inline CoTensor<T>::CoTensor(const T & t)
	{
	}
}

#endif // !COCONET_TENSOR_COTENSOR_TENSOR_H_
