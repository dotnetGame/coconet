#ifndef COCONET_NN_VARIABLE_H_
#define COCONET_NN_VARIABLE_H_

#include <memory>
#include <initializer_list>

#include <coconet/core/type.h>
#include <coconet/tensor/tensor.h>
#include <coconet/tensor/index.h>
#include <coconet/cotensor/tensor.h>
#include <coconet/cotensor/apply.h>
#include <coconet/nn/operation.h>

namespace coconet
{
	namespace nn
	{
		class IVariable
		{

		};

		template<class T, PlatformType Platform = PlatformType::CPU>
		class Variable : public IVariable
		{
		public:

		private:
			/*
			std::unique_ptr<cotensor::CoTensor<T>> _data;
			std::unique_ptr<cotensor::CoTensor<f32>> _grad;
			std::unique_ptr<OpBase> _grad_fn;
			std::vector<IVariable*> _inputs;
			*/
		};

		template<class T>
		class Variable<T, PlatformType::CPU> : public IVariable
		{
		public:
			using value_type = T;
			using self_type = Variable<T, PlatformType::CPU>;
			using base_type = IVariable;

			using raw_pointer = self_type * ;
			using raw_const_pointer = const self_type*;
			using shared_pointer = std::shared_ptr<self_type>;
			using reference = self_type & ;
			using const_reference = const self_type&;
		public:
			Variable(tensor::DimVector dimensions);
		public:
			// create
			static shared_pointer zeros(std::initializer_list<idx_type> list);
			static shared_pointer ones(std::initializer_list<idx_type> list);

			// arithmetic
			static shared_pointer matmul(shared_pointer left, shared_pointer right);

		public:
			void fill_(T value);
		private:
			std::unique_ptr<cotensor::CoTensor<T>> _data;
			std::unique_ptr<cotensor::CoTensor<f32>> _grad;
			std::unique_ptr<OpBase> _grad_fn;
			std::vector<IVariable*> _inputs;
		};
		
		template class Variable<f32, PlatformType::CPU>;
		template class Variable<f64, PlatformType::CPU>;
		template class Variable<i8, PlatformType::CPU>;
		template class Variable<i16, PlatformType::CPU>;
		template class Variable<i32, PlatformType::CPU>;
		template class Variable<i64, PlatformType::CPU>;
		template class Variable<u8, PlatformType::CPU>;

		using FloatVariable = Variable<f32, PlatformType::CPU>;
		using DoubleVariable = Variable<f64, PlatformType::CPU>;
		using CharVariable = Variable<i8, PlatformType::CPU>;
		using ShortVariable = Variable<i16, PlatformType::CPU>;
		using IntVariable = Variable<i32, PlatformType::CPU>;
		using LongVariable = Variable<i64, PlatformType::CPU>;
		using ByteVariable = Variable<u8, PlatformType::CPU>;

		template<class T>
		inline Variable<T, PlatformType::CPU>::Variable(tensor::DimVector dimensions)
			:_data(new cotensor::CoTensor<T>(dimensions)), _grad(nullptr), _grad_fn(nullptr), _inputs()
		{
		}

		template<class T>
		inline std::shared_ptr<Variable<T, PlatformType::CPU>> Variable<T, PlatformType::CPU>::zeros(std::initializer_list<idx_type> list)
		{
			std::shared_ptr<Variable<T, PlatformType::CPU>> ret(new Variable<T, PlatformType::CPU>(list));
			ret->fill_(0);
			return ret;
		}

		template<class T>
		inline std::shared_ptr<Variable<T, PlatformType::CPU>> Variable<T, PlatformType::CPU>::ones(std::initializer_list<idx_type> list)
		{
			std::shared_ptr<Variable<T, PlatformType::CPU>> ret(new Variable<T, PlatformType::CPU>(list));
			ret->fill_(1);
			return ret;
		}

		template<class T>
		inline std::shared_ptr<Variable<T, PlatformType::CPU>> Variable<T, PlatformType::CPU>::matmul(shared_pointer left, shared_pointer right)
		{
			return shared_pointer(nullptr);
		}

		template<class T>
		inline void Variable<T, PlatformType::CPU>::fill_(T value)
		{
			cotensor::fill_(*_data, value);
		}
	}
}

#endif // !COCONET_NN_VARIABLE_H_
