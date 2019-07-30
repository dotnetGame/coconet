#include <coconet/cotensor/allocator.h>

#include <cstdlib>

namespace coconet
{
	char * CoTensorAllocator::allocate(idx_type size)
	{
		return (char *)malloc(size);
	}

	void CoTensorAllocator::deallocate(char * ptr)
	{
		free(ptr);
	}
}


