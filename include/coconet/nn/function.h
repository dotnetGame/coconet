#ifndef COCONET_NN_FUNCTION_H_
#define COCONET_NN_FUNCTION_H_

#include <memory>

#include <coconet/nn/variable.h>

namespace coconet
{
	namespace nn
	{
		// create
		template<class T>
		std::shared_ptr<Variable<T>> zeros(std::initializer_list<idx_type> list)
		{
			return std::make_shared<Variable<T>>();
		}

		template<class T>
		std::shared_ptr <Variable<T>> ones(std::initializer_list<idx_type> list)
		{
			return std::make_shared<Variable<T>>();
		}

		// arithmetic
		template<class T>
		std::shared_ptr<Variable<T>> matmul(std::shared_ptr<Variable<T>> left, std::shared_ptr<Variable<T>> right)
		{
			return left;
		}
	}


}

#endif // !COCONET_NN_FUNCTION_H_
