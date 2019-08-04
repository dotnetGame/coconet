
#include <iostream>
#include <coconet/tensor/index.h>
#include <coconet/cotensor/tensor.h>
#include <coconet/cotensor/apply.h>


int main()
{
	{
		coconet::tensor::DimVector shape({ 5,4,3,2,1 });

		for (auto& each : shape)
		{
			std::cout << each << ",";
		}

		std::cout << std::endl;
	}

	{
		coconet::tensor::DimVector shape({ 5,4,3 });

		for (auto& each : shape)
		{
			std::cout << each << ",";
		}

		std::cout << std::endl;
	}
	

	{
		coconet::cotensor::CoTensor<coconet::f32> tensor({ 2,3,4 });
		coconet::cotensor::fill_(tensor, 1.f);
		std::cout << tensor.to_string();
	}

    return 0;
}