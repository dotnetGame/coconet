
#include <iostream>
#include <coconet/nn/variable.h>
#include <coconet/nn/function.h>


int main()
{
	{
		auto a = coconet::zeros<coconet::f32>({ 4,2 });
		auto b = coconet::zeros<coconet::f32>({ 2,4 });
		auto c = coconet::matmul(a, b);

	}
	

    return 0;
}