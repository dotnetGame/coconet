
#include <coconet/cotensor/tensor.h>

#include <fmt/format.h>

namespace coconet
{
	namespace cotensor
	{
		template<class T>
		CoTensor<T>::CoTensor()
		{
		}
		template<class T>
		CoTensor<T>::CoTensor(const tensor::DimVector & dimensions)
			: _rep(nullptr), _dimensions(dimensions), _strides(dimensions.size(), 0), _offset(0), _dtype(GetDataType<T>::get())
		{
			idx_type cum_stride = 1;
			for (idx_type i = static_cast<idx_type>(_strides.size() - 1); i >= 0; --i)
			{
				_strides[i] = cum_stride;
				cum_stride *= _dimensions[i];
			}

			_rep = std::make_shared<CoTensorStorage>(_dtype, cum_stride);
		}
		template<class T>
		inline T * CoTensor<T>::data_ptr()
		{
			return reinterpret_cast<T*>(_rep->data_ptr()) + _offset;
		}
		template<class T>
		inline const T * CoTensor<T>::data_ptr() const
		{
			return reinterpret_cast<T*>(_rep->data_ptr()) + _offset;
		}
		template<class T>
		inline device_id CoTensor<T>::device()
		{
			return 0;
		}
		template<class T>
		inline DataType CoTensor<T>::dtype() const
		{
			return GetDataType<T>::get();
		}

		template<class T>
		inline bool CoTensor<T>::equal(const tensor::ITensor & other) const
		{
			return false;
		}

		/*
		Returns True if self tensor is contiguous in memory in C order.
		*/
		template<class T>
		inline bool CoTensor<T>::is_contiguous() const
		{
			if (stride(-1) != 1)
				return false;

			for (idx_type i = ndimension() - 1; i > 0; --i)
			{
				if (size(i) * stride(i) != stride(i - 1))
					return false;
			}

			return true;
		}

		template<class T>
		inline idx_type CoTensor<T>::ndimension() const
		{
			return static_cast<idx_type>(_dimensions.size());
		}
		template<class T>
		inline idx_type CoTensor<T>::numel() const
		{
			return _rep->size() - _offset;
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
		inline tensor::DimVector CoTensor<T>::size() const
		{
			return _dimensions;
		}
		template<class T>
		inline idx_type CoTensor<T>::size(idx_type i) const
		{
			auto shape_size = _dimensions.size();
			if (i >= 0 && i < _dimensions.size())
				return _dimensions[i];
			else if (i <= -1 && i >= -static_cast<idx_type>(_dimensions.size()))
				return _dimensions[shape_size + i];
			else
				throw std::runtime_error("Dimension out of range");
		}
		template<class T>
		inline tensor::Storage & CoTensor<T>::storage()
		{
			return *_rep;
		}
		template<class T>
		inline tensor::StrideVector CoTensor<T>::stride() const
		{
			return _strides;
		}
		template<class T>
		inline idx_type CoTensor<T>::stride(idx_type i) const
		{
			auto shape_size = _strides.size();
			if (i >= 0 && i < _strides.size())
				return _strides[i];
			else if (i <= -1 && i >= -static_cast<idx_type>(_strides.size()))
				return _strides[shape_size + i];
			else
				throw std::runtime_error("Dimension out of range");
		}
		template<class T>
		inline std::string CoTensor<T>::to_string() const
		{
			std::function<std::string(const CoTensor<T>& t, idx_type dim, idx_type idx)> to_string_impl =
				[&](const CoTensor<T>& t, idx_type dim, idx_type idx)->std::string {
				std::string result;
				if (dim == t.ndimension())
				{
					result += fmt::format("{:.4f}", t.data_ptr()[idx]);
					return result;
				}

				for (idx_type i = 0; i < t.size(dim); ++i)
				{
					if (dim != t.ndimension() - 1 && i != 0) result += ",\n";
					if (dim != t.ndimension() - 1)	result += "[";
					result += to_string_impl(t, dim + 1, idx);
					if (i != t.size(dim) - 1 && dim == t.ndimension() - 1)
						result += ",";
					if (dim != t.ndimension() - 1) result += "]";

					idx += t.stride(dim);
				}

				return result;
			};

			std::string result;
			result += "[" + to_string_impl(*this, 0, 0) + "]";
			return result;
		}

		template class CoTensor<f32>;
		template class CoTensor<f64>;
		template class CoTensor<i8>;
		template class CoTensor<i16>;
		template class CoTensor<i32>;
		template class CoTensor<i64>;
		template class CoTensor<u8>;
    }
}