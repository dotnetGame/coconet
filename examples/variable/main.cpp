
#include <iostream>
#include <coconet/autograd/variable.h>
#include <coconet/autograd/function.h>


int main()
{
	{
		auto a = coconet::autograd::Variable<coconet::f32>::zeros({ 4,2 });
		auto b = coconet::autograd::Variable<coconet::f32>::ones({ 2,4 });
		std::cout << b->to_string();

	}
	

    return 0;
}