#include <coconet/cotensor/tensor.h>

namespace coconet
{
	template<>
	DataType CoTensor<f32>::dtype() const
	{
		return DataType::FLOAT;
	}

	template<>
	DataType CoTensor<f64>::dtype() const
	{
		return DataType::DOUBLE;
	}

	template<>
	DataType CoTensor<u8>::dtype() const
	{
		return DataType::BYTE;
	}

	template<>
	DataType CoTensor<i8>::dtype() const
	{
		return DataType::CHAR;
	}

	template<>
	DataType CoTensor<i16>::dtype() const
	{
		return DataType::SHORT;
	}

	template<>
	DataType CoTensor<i32>::dtype() const
	{
		return DataType::INT;
	}

	template<>
	DataType CoTensor<i64>::dtype() const
	{
		return DataType::LONG;
	}
}