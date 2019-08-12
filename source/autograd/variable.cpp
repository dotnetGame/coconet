#include <coconet/autograd/variable.h>
namespace coconet
{
	namespace autograd
	{
		template<class T>
		inline Variable<T, PlatformType::CPU>::Variable(const tensor::DimVector& dimensions)
			:_data(new cotensor::CoTensor<T>(dimensions)), _grad(nullptr)
		{
		}

		template<class T>
		inline std::shared_ptr<Variable<T, PlatformType::CPU>> Variable<T, PlatformType::CPU>::zeros(std::initializer_list<idx_type> list)
		{
			std::shared_ptr<Variable<T, PlatformType::CPU>> ret(new Variable<T, PlatformType::CPU>(list));
			ret->fill_(static_cast<T>(0));
			return ret;
		}

		template<class T>
		inline std::shared_ptr<Variable<T, PlatformType::CPU>> Variable<T, PlatformType::CPU>::ones(std::initializer_list<idx_type> list)
		{
			std::shared_ptr<Variable<T, PlatformType::CPU>> ret(new Variable<T, PlatformType::CPU>(list));
			ret->fill_(static_cast<T>(1));
			return ret;
		}

		template<class T>
		inline void Variable<T, PlatformType::CPU>::fill_(scalar_type value)
		{
			cotensor::fill_(*_data, ScalarTo<T>::to(value));
		}

		template<class T>
		inline std::string Variable<T, PlatformType::CPU>::to_string() const
		{
			std::string ret;
			if (_data)
				ret = _data->to_string();
			return ret;
		}

		template class Variable<f32, PlatformType::CPU>;
		template class Variable<f64, PlatformType::CPU>;
		template class Variable<i8, PlatformType::CPU>;
		template class Variable<i16, PlatformType::CPU>;
		template class Variable<i32, PlatformType::CPU>;
		template class Variable<i64, PlatformType::CPU>;
		template class Variable<u8, PlatformType::CPU>;
	}
}