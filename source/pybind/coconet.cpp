
#include <vector>
#include <algorithm>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
namespace py = pybind11;

#include <coconet/tensor/index.h>
#include <coconet/autograd/variable.h>

namespace coconet
{
	namespace pybind
	{
		PYBIND11_MODULE(coconet, m)
		{
			m.doc() = "coconet python bind"; // optional module docstring

			py::class_<tensor::DimVector>(m, "DimVector")
				.def(py::init<>())
				.def(py::init<std::size_t>())
				.def(py::init<std::size_t, std::size_t>())
				.def("clear", &tensor::DimVector::clear)
				.def("pop_back", &tensor::DimVector::pop_back)
				.def("push_back", &tensor::DimVector::push_back)
				.def("__len__", [](const tensor::DimVector &v) { return v.size(); })
				.def("__iter__", [](tensor::DimVector &v) {
					return py::make_iterator(v.begin(), v.end());
					}, py::keep_alive<0, 1>());

			py::class_<autograd::ByteVariable>(m, "ByteTensor")
				.def(py::init<const tensor::DimVector&>())
				.def(py::init([](std::vector<coconet::idx_type> dim){
					return autograd::ByteVariable(tensor::DimVector(dim.cbegin(),dim.cend()));
				}))
				.def("fill_", &autograd::ByteVariable::fill_);
		}
	}
}