
#include <vector>
#include <memory>
#include <algorithm>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
namespace py = pybind11;

#include <coconet/tensor/index.h>
#include <coconet/autograd/variable.h>
#include <coconet/autograd/executor.h>
#include <coconet/runtime/singleton.h>

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

			py::class_<autograd::ByteVariable, std::shared_ptr<autograd::ByteVariable>>(m, "ByteVariable")
				.def(py::init<const tensor::DimVector&>())
				.def(py::init([](std::vector<coconet::idx_type> dim){
					return autograd::ByteVariable(tensor::DimVector(dim.cbegin(),dim.cend()));
				}))
				.def("fill_", &autograd::ByteVariable::fill_);

			py::class_<autograd::CharVariable, std::shared_ptr<autograd::CharVariable>>(m, "CharVariable")
				.def(py::init<const tensor::DimVector&>())
				.def(py::init([](std::vector<coconet::idx_type> dim){
					return autograd::CharVariable(tensor::DimVector(dim.cbegin(),dim.cend()));
				}))
				.def("fill_", &autograd::CharVariable::fill_);

			py::class_<autograd::ShortVariable, std::shared_ptr<autograd::ShortVariable>>(m, "ShortVariable")
				.def(py::init<const tensor::DimVector&>())
				.def(py::init([](std::vector<coconet::idx_type> dim){
					return autograd::ShortVariable(tensor::DimVector(dim.cbegin(),dim.cend()));
				}))
				.def("fill_", &autograd::ShortVariable::fill_);

			py::class_<autograd::IntVariable, std::shared_ptr<autograd::IntVariable>>(m, "IntVariable")
				.def(py::init<const tensor::DimVector&>())
				.def(py::init([](std::vector<coconet::idx_type> dim){
					return autograd::IntVariable(tensor::DimVector(dim.cbegin(),dim.cend()));
				}))
				.def("fill_", &autograd::IntVariable::fill_);
			
			py::class_<autograd::LongVariable, std::shared_ptr<autograd::LongVariable>>(m, "LongVariable")
				.def(py::init<const tensor::DimVector&>())
				.def(py::init([](std::vector<coconet::idx_type> dim){
					return autograd::LongVariable(tensor::DimVector(dim.cbegin(),dim.cend()));
				}))
				.def("fill_", &autograd::LongVariable::fill_);

			py::class_<autograd::FloatVariable, std::shared_ptr<autograd::FloatVariable>>(m, "FloatVariable")
				.def(py::init<const tensor::DimVector&>())
				.def(py::init([](std::vector<coconet::idx_type> dim){
					return autograd::FloatVariable(tensor::DimVector(dim.cbegin(),dim.cend()));
				}))
				.def("fill_", &autograd::FloatVariable::fill_);

			py::class_<autograd::DoubleVariable, std::shared_ptr<autograd::DoubleVariable>>(m, "DoubleVariable")
				.def(py::init<const tensor::DimVector&>())
				.def(py::init([](std::vector<coconet::idx_type> dim){
					return autograd::DoubleVariable(tensor::DimVector(dim.cbegin(),dim.cend()));
				}))
				.def("fill_", &autograd::DoubleVariable::fill_);

			m.def("zeros", [](std::vector<coconet::idx_type> dim, coconet::DataType dtype, coconet::PlatformType platform, bool require_grad){
				auto dimvector = tensor::DimVector(dim.cbegin(), dim.cend());
				auto session = runtime::Singleton<autograd::VariableGraph>::getInstance();

				auto ret = std::shared_ptr<autograd::IVariable>(nullptr);
				if (platform == coconet::PlatformType::CPU){
					if (dtype == coconet::DataType::BYTE) {
						ret = std::make_shared<autograd::Variable<coconet::u8, coconet::PlatformType::CPU>>(dimvector);
					} else {
						throw std::runtime_error("Unsupported dtype");
					}
				} else {
					throw std::runtime_error("Unsupported platform");
				}
				
				ret->fill_(0);
				if (require_grad)
					session.add_variable(ret);
				return ret;
			},
			"Create variable filled zeros",
			py::arg("dim"),
			py::arg("dtype") = coconet::DataType::FLOAT,
			py::arg("platform") = coconet::PlatformType::CPU,
			py::arg("require_grad") = false);
		}
	}
}