#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>
#include <coconet/cotensor/tensor.h>

TEST_CASE("cotensor test", "[CoTensor]")
{
	coconet::cotensor::CoTensor<coconet::f32> v({3, 4});

	REQUIRE(v.size(0) == 3);
	REQUIRE(v.size(1) == 4);
	REQUIRE(v.stride(0) == 4);
	REQUIRE(v.stride(1) == 1);
	REQUIRE(v.device() == 0);
	REQUIRE(v.platform() == coconet::PlatformType::CPU);
	REQUIRE(v.is_contiguous() == true);
	REQUIRE(v.offset() == 0);
	REQUIRE(v.dtype() == coconet::DataType::FLOAT);

	/*SECTION("resizing bigger changes size and capacity") {
		v.resize(10);

		REQUIRE(v.size() == 10);
		REQUIRE(v.capacity() >= 10);
	}*/
}