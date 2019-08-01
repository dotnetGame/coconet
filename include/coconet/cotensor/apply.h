#ifndef COCONET_COTENSOR_APPLY_H_
#define COCONET_COTENSOR_APPLY_H_

#include <coconet/cotensor/tensor.h>
#include <xsimd/xsimd.hpp>

namespace coconet
{
	template<class T, class Fn>
	void apply(CoTensor<T>& tensor, Fn f)
	{
		// split tensor
		idx_type split_pos = -tensor.ndimension() - 1;
		for (idx_type i = -1; i >= -tensor.ndimension(); --i)
		{
			if (i == -1)
			{
				if (tensor.stride(i) != 1)
				{
					split_pos = i;
					break;
				}
			}
			else
			{
				if (tensor.size(i + 1) * tensor.stride(i + 1) != tensor.stride(i))
				{
					split_pos = i;
					break;
				}
			}
		}

		// special case
		if (split_pos == -tensor.ndimension() - 1)
		{
			apply_contiguous(tensor, f);
			return;
		}

		// right tensor info
		idx_type right_tensor_len = 0;
		if(split_pos != -1)
		{
			right_tensor_len = tensor.size(split_pos + 1) * tensor.stride(split_pos + 1);
		}
		else
		{
			right_tensor_len = 1;
		}
		

		// init pointers
		SmallVector<T*, 5> start_pos(tensor.ndimension(), tensor->data_ptr() + tensor->offset());
		SmallVector<T*, 5> end_pos(tensor.ndimension());

		for (idx_type i = 0; i < tensor.ndimension(); ++i)
		{
			end_pos[i] = start_pos[i] + tensor.size(i) * tensor.stride(i);
		}

		// traversal
		DimVector counter(tensor.ndimension, 0);
		bool is_finished = false;
		T* cur_data = tensor->data_ptr() + tensor->offset();
		while (is_finished)
		{
			for (idx_type i = 0; i < tensor->size(split_pos); ++i)
			{
				if (split_pos == -1)
				{
					f(cur_data);
				}
				else
				{
					apply_contiguous(cur_data, right_tensor_len, f);
				}
				cur_data += tensor.stride(split_pos);
			}
			// acc counter
			counter[tensor.ndimension() + split_pos] += tensor.size(split_pos);
			for (idx_type i = tensor.ndimension() - 1; i >= 0; --i)
			{
				if (counter[i] >= tensor.size(i) - 1)
				{
					counter[i] = 0;
					if (i == 0)
					{
						is_finished = true;
					}
					else
					{
						++counter[i - 1];
					}
				}
			}
		}
	}

	template<class T, class Fn>
	void apply_contiguous(T* tensor, idx_type len, Fn f)
	{
		T *element_ptr = tensor;
		T *end_ptr = element_ptr + len;
		while (element_ptr < end_ptr)
		{
			f(*element_ptr);
			element_ptr++;
		}
	}

	template<class T, class Fn>
	void apply_contiguous(CoTensor<T>& tensor, Fn f)
	{
		T *element_ptr = tensor.data_ptr();
		T *end_ptr = element_ptr + tensor.storage()->numel();
		while (element_ptr < end_ptr)
		{
			f(*element_ptr);
			element_ptr++;
		}
	}
}

#endif