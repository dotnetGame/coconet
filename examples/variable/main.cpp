
#include <iostream>
#include <coconet/nn/variable.h>
#include <coconet/nn/function.h>


int main()
{
	{
		auto a = coconet::nn::Variable<coconet::f32>::zeros({ 4,2 });
		auto b = coconet::nn::Variable<coconet::f32>::zeros({ 2,4 });
		auto c = coconet::nn::Variable<coconet::f32>::matmul(a, b);

	}
	

    return 0;
}