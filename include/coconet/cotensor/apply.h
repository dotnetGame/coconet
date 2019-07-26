#ifndef COCONET_COTENSOR_APPLY_H_
#define COCONET_COTENSOR_APPLY_H_

#include <coconet/cotensor/tensor.h>

namespace coconet
{
	template<class T, class Fn>
	void apply(CoTensor<T>& tensor, Fn f)
	{

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