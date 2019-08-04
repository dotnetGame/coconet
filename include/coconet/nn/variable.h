#ifndef COCONET_NN_VARIABLE_H_
#define COCONET_NN_VARIABLE_H_

#include <memory>
#include <initializer_list>

#include <coconet/core/type.h>
#include <coconet/tensor/tensor.h>
#include <coconet/nn/operation.h>

namespace coconet
{
	namespace nn
	{
		template<class T>
		class Variable
		{
		public:

		private:
			std::unique_ptr<tensor::ITensor> _data;
			std::unique_ptr<tensor::ITensor> _grad;
			std::unique_ptr<OpBase> _grad_fn;
			std::vector<tensor::ITensor*> _inputs;
		};
		
		template class Variable<f32>;
		template class Variable<f64>;
		template class Variable<i8>;
		template class Variable<i16>;
		template class Variable<i32>;
		template class Variable<i64>;
		template class Variable<u8>;

		using FloatVariable = Variable<f32>;
		using DoubleVariable = Variable<f64>;
		using CharVariable = Variable<i8>;
		using ShortVariable = Variable<i16>;
		using IntVariable = Variable<i32>;
		using LongVariable = Variable<i64>;
		using ByteVariable = Variable<u8>;
	}
}

#endif // !COCONET_NN_VARIABLE_H_
