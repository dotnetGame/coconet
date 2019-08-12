#ifndef COCONET_COTENSOR_TENSOR_H_
#define COCONET_COTENSOR_TENSOR_H_

#include <string>
#include <memory>
#include <stdexcept>
#include <functional>

#include <coconet/core/type.h>
#include <coconet/tensor/tensor.h>
#include <coconet/tensor/index.h>

#include <coconet/cotensor/storage.h>

namespace coconet
{
	namespace cotensor
	{
		template<class T>
		class CoTensor: public tensor::ITensor
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
			std::shared_ptr<CoTensorStorage> _rep;
			tensor::DimVector _dimensions;
			tensor::StrideVector _strides;
			idx_type _offset;
			DataType _dtype;
		public:
			CoTensor();
			explicit CoTensor(const tensor::DimVector& dimensions);

			CoTensor(const CoTensor& other) = delete;
			CoTensor(CoTensor&& other) = delete;
			CoTensor& operator= (const CoTensor& other) = delete;
			CoTensor& operator= (CoTensor&& other) = delete;

		public:
			T* data_ptr();
			const T* data_ptr() const;
			device_id device();
			DataType dtype() const;
			bool equal(const tensor::ITensor& other) const;
			bool is_contiguous() const;

			idx_type ndimension() const;
			idx_type numel() const;
			idx_type offset() const;
			PlatformType platform() const;
			tensor::DimVector size() const;
			idx_type size(idx_type i) const;
			tensor::Storage& storage();
			tensor::StrideVector stride() const;
			idx_type stride(idx_type i) const;
			std::string to_string() const;
		};

		using FloatCoTensor = CoTensor<f32>;
		using DoubleCoTensor = CoTensor<f64>;
		using CharCoTensor = CoTensor<i8>;
		using ShortCoTensor = CoTensor<i16>;
		using IntCoTensor = CoTensor<i32>;
		using LongCoTensor = CoTensor<i64>;
		using ByteCoTensor = CoTensor<u8>;
		
	}
}

#endif // !COCONET_COTENSOR_TENSOR_H_
