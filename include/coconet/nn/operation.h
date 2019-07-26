#ifndef COCONET_NN_OPERATION_H_
#define COCONET_NN_OPERATION_H_

#include <vector>

#include <coconet/tensor/tensor.h>

namespace coconet
{
	class OpContext
	{
	private:
		std::vector<ITensor*> _saved_tensors;
	public:
		void save(ITensor* tensor)
		{
			_saved_tensors.push_back(tensor);
		}

		std::vector<ITensor*> get_saved_tensors() const
		{
			return _saved_tensors;
		}
	};

	class OpBase
	{
	public:
		OpContext context;

		virtual ITensor* forward(std::vector<ITensor*> inputs) = 0;
		virtual std::vector<ITensor*> backward(ITensor* output_grad) = 0;
	};

	class MatmulOp : public OpBase
	{
	public:
		virtual ITensor* forward(std::vector<ITensor*> inputs) override
		{
			return nullptr;
		}

		virtual std::vector<ITensor*> backward(ITensor* output_grad) override
		{
			return {};
		}
	};
}


#endif //!COCONET_NN_OPERATION_H_