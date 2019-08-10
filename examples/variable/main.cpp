
#include <iostream>
#include <coconet/cppbind/coconet.h>


int main()
{
	{
		auto a = coconet::cppbind::TensorFactory<coconet::f32>::zeros({2, 3});
		auto b = coconet::cppbind::TensorFactory<coconet::f32>::zeros({ 2, 3 });
		auto c = coconet::cppbind::add(a, b);
	}
	/*{
		coconet::autograd::VariableGraph session;
		auto addOp = std::make_shared<coconet::autograd::AddFunction>();
		auto a = coconet::autograd::Variable<coconet::f32>::zeros({ 4,2 });
		session.add_variable(a);
		auto b = coconet::autograd::Variable<coconet::f32>::ones({ 4,2 });
		session.add_variable(b);
		auto c = addOp->forward({a,b})[0];
		session.add_edge({ a, b }, { c }, addOp);

		std::cout << b->to_string();

	}
	*/

    return 0;
}