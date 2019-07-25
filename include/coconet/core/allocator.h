#ifndef COCONET_CORE_ALLOCATOR_H_
#define COCONET_CORE_ALLOCATOR_H_

#include <cstddef>

namespace coconet
{
	template<class T>
	class Allocator
	{
	public:
		Allocator(const Allocator&) = delete;
		Allocator& operator=(const Allocator&) = delete;
		Allocator(Allocator&&) = delete;
		Allocator& operator=(Allocator&&) = delete;
	public:
		virtual T* allocate(std::size_t n) = 0;
		virtual void deallocate(T* p, std::size_t n) = 0;
	};
}


#endif // !COCONET_CORE_ALLOCATOR_H_
