
#include <pybind11/pybind11.h>
namespace py = pybind11;


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
				.def("clear", &tensor::DimVector::clear)
				.def("pop_back", &tensor::DimVector::pop_back)
				.def("push_back", &tensor::DimVector::push_back)
				.def("__len__", [](const tensor::DimVector &v) { return v.size(); })
				.def("__iter__", [](tensor::DimVector &v) {
					return py::make_iterator(v.begin(), v.end());
					}, py::keep_alive<0, 1>());

			py::class_<autograd::ByteVariable>(m, "ByteTensor")
				.def(py::init<const tensor::DimVector&>())
				.def("fill_", &autograd::ByteVariable::fill_);
		}
	}
}