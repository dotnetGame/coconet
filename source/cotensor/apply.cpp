#include <coconet/cotensor/apply.h>

#include <coconet/core/type.h>

#ifdef COCONET_FEATURE_SIMD
#include <xsimd/xsimd.hpp>
#endif // COCONET_FEATURE_SIMD


#ifdef COCONET_FEATURE_MULTI_THREAD
#include <taskflow/taskflow.hpp>
#endif // COCONET_FEATURE_MULTI_THREAD

namespace coconet
{
	namespace cotensor
	{
		template<class T, class Fn>
		void apply_naive(CoTensor<T>& tensor, Fn f)
		{
			// traversal
			bool is_finished = false;

			DimVector counter(tensor.ndimension(), 0);
			T* cur_data = tensor.data_ptr();

			while (!is_finished)
			{
				// update counter
				for (idx_type i = tensor.ndimension() - 1; i >= 0; --i)
				{
					if (i == tensor.ndimension() - 1)
					{
						f(*cur_data);
					}
					++counter[i];
					cur_data += tensor.stride(i);
					if (counter[i] == tensor.size(i))
					{
						if (i == 0)
						{
							is_finished = true;
							break;
						}
						else
						{
							cur_data -= tensor.size(i) * tensor.stride(i);
							counter[i] = 0;
						}
					}
					else
					{
						break;
					}
				}
			}

		}

		template<class T, class Fn>
		void apply_simple(CoTensor<T>& tensor, Fn f)
		{
			// traversal
			bool is_finished = false;

			tensor::DimVector counter(tensor.ndimension(), 0);
			T* cur_data = tensor.data_ptr();

			while (!is_finished)
			{
				for (idx_type i = 0; i < tensor.size(tensor.ndimension() - 1); ++i)
				{
					f(*cur_data);
					cur_data += tensor.stride(tensor.ndimension() - 1);
				}

				// reset pointer to current dim begin
				cur_data -= tensor.size(tensor.ndimension() - 1) * tensor.stride(tensor.ndimension() - 1);

				// update counter
				for (idx_type i = tensor.ndimension() - 2; i >= 0; --i)
				{
					++counter[i];
					cur_data += tensor.stride(i);
					if (counter[i] == tensor.size(i))
					{
						counter[i] = 0;
						if (i == 0)
						{
							is_finished = true;
							break;
						}
						else
						{
							cur_data -= tensor.size(i) * tensor.stride(i);
						}
					}
					else
					{
						break;
					}
				}
			}

		}

		template<class T, class Fn>
		void apply(CoTensor<T>& tensor, Fn f)
		{
			// split tensor
			idx_type split_pos = -1;
			for (idx_type i = tensor.ndimension() - 1; i >= 0; --i)
			{
				if (i == tensor.ndimension() - 1)
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
			if (split_pos == -1)
			{
				apply_contiguous(tensor, f);
				return;
			}

			// A tensor info
			idx_type a_tensor_len = 0;
			if (split_pos != tensor.ndimension() - 1)
			{
				a_tensor_len = tensor.size(split_pos + 1) * tensor.stride(split_pos + 1);
			}
			else
			{
				a_tensor_len = 1;
			}

			// traversal
			bool is_finished = false;

			tensor::DimVector counter(tensor.ndimension(), 0);
			T* cur_data = tensor.data_ptr();

			while (!is_finished)
			{
				for (idx_type i = 0; i < tensor.size(tensor.ndimension() - 1); ++i)
				{
					apply_contiguous(cur_data, a_tensor_len, f);
					cur_data += tensor.stride(tensor.ndimension() - 1);
				}

				// reset pointer to current dim begin
				cur_data -= tensor.size(tensor.ndimension() - 1) * tensor.stride(tensor.ndimension() - 1);

				// update counter
				for (idx_type i = tensor.ndimension() - 2; i >= 0; --i)
				{
					++counter[i];
					cur_data += tensor.stride(i);
					if (counter[i] == tensor.size(i))
					{
						if (i == 0)
						{
							is_finished = true;
							break;
						}
						else
						{
							cur_data -= tensor.size(i) * tensor.stride(i);
							counter[i] = 0;
						}
					}
					else
					{
						break;
					}
				}
			}
		}

	#ifndef COCONET_FEATURE_MULTI_THREAD
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
	#else
		template<class T, class Fn>
		void apply_contiguous(T* tensor, idx_type len, Fn f)
		{
			T *element_ptr = tensor;
			T *end_ptr = element_ptr + len;

			tf::Executor executor;
			tf::Taskflow taskflow;

			taskflow.parallel_for(element_ptr, end_ptr, f);
			executor.run(taskflow).get();
		}
	#endif

		template<class T, class Fn>
		void apply_contiguous(CoTensor<T>& tensor, Fn f)
		{
			idx_type cum_size = 1;
			for (idx_type i = static_cast<idx_type>(tensor.ndimension() - 1); i >= 0; --i)
				cum_size *= tensor.size(i);

			T *element_ptr = tensor.data_ptr();
			T *end_ptr = element_ptr + cum_size;
			while (element_ptr < end_ptr)
			{
				f(*element_ptr);
				element_ptr++;
			}
		}

		template<class T>
		void fill_impl(CoTensor<T>& tensor, T value)
		{
			apply(tensor, [&](T& item) {item = value; });
		}
		void fill_(CoTensor<f32>& tensor, f32 value) { fill_impl(tensor, value); }
		void fill_(CoTensor<f64>& tensor, f64 value) { fill_impl(tensor, value); }
		void fill_(CoTensor<u8>& tensor, u8 value) { fill_impl(tensor, value); }
		void fill_(CoTensor<i8>& tensor, i8 value) { fill_impl(tensor, value); }
		void fill_(CoTensor<i16>& tensor, i16 value) { fill_impl(tensor, value); }
		void fill_(CoTensor<i32>& tensor, i32 value) { fill_impl(tensor, value); }
		void fill_(CoTensor<i64>& tensor, i64 value) { fill_impl(tensor, value); }
	}
}