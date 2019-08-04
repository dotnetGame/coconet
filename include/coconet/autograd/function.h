#ifndef COCONET_AUTOGRAD_FUNCTION_H_
#define COCONET_AUTOGRAD_FUNCTION_H_

#include <memory>

#include <coconet/autograd/variable.h>

namespace coconet
{
	namespace autograd
	{
		class FunctionContext
		{
		private:
			std::vector<tensor::ITensor*> _saved_tensors;
		public:
			void save(tensor::ITensor* tensor)
			{
				_saved_tensors.push_back(tensor);
			}

			std::vector<tensor::ITensor*> get_saved_tensors() const
			{
				return _saved_tensors;
			}
		};

		class FunctionBase
		{
		public:
			FunctionContext context;

			virtual tensor::ITensor* forward(std::vector<tensor::ITensor*> inputs) = 0;
			virtual std::vector<tensor::ITensor*> backward(tensor::ITensor* output_grad) = 0;
		};

		class MatmulFunction : public FunctionBase
		{
		public:
			virtual tensor::ITensor* forward(std::vector<tensor::ITensor*> inputs) override
			{
				return nullptr;
			}

			virtual std::vector<tensor::ITensor*> backward(tensor::ITensor* output_grad) override
			{
				return {};
			}
		};
		
	}


}

#endif // !COCONET_AUTOGRAD_FUNCTION_H_
