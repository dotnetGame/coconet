
#include <iostream>
#include <coconet/autograd/variable.h>
#include <coconet/autograd/function.h>
#include <coconet/autograd/executor.h>


int main()
{
	{
		coconet::autograd::VariableGraph session;
		auto addOp = std::make_shared<coconet::autograd::AddFunction>();
		auto a = coconet::autograd::Variable<coconet::f32>::zeros({ 4,2 });
		auto b = coconet::autograd::Variable<coconet::f32>::ones({ 4,2 });
		auto c = addOp->forward({a,b})[0];
		session.add_variable(a);
		session.add_variable(b);
		session.add_edge({ a, b }, { c }, addOp);

		std::cout << b->to_string();

	}
	

    return 0;
}