#ifndef COCONET_NN_OPERATION_H_
#define COCONET_NN_OPERATION_H_

#include <vector>

#include <coconet/tensor/tensor.h>

namespace coconet
{
	namespace nn
	{
		class OpContext
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

		class OpBase
		{
		public:
			OpContext context;

			virtual tensor::ITensor* forward(std::vector<tensor::ITensor*> inputs) = 0;
			virtual std::vector<tensor::ITensor*> backward(tensor::ITensor* output_grad) = 0;
		};

		class MatmulOp : public OpBase
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


#endif //!COCONET_NN_OPERATION_H_