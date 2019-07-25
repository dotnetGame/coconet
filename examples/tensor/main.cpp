
#include <iostream>
#include <coconet/tensor/cotensor/index.h>


int main()
{
	{
		coconet::DimVector shape({ 5,4,3,2,1 });

		for (auto& each : shape)
		{
			std::cout << each << ",";
		}

		std::cout << std::endl;
	}

	{
		coconet::DimVector shape({ 5,4,3 });

		for (auto& each : shape)
		{
			std::cout << each << ",";
		}

		std::cout << std::endl;
	}
	

    return 0;
}