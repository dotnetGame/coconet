#ifndef COCONET_TENSOR_TENSOR_INDEX_H_
#define COCONET_TENSOR_TENSOR_INDEX_H_

#include <cstdint>
#include <cstring>
#include <cassert>
#include <stdexcept>
#include <memory>
#include <utility>
#include <initializer_list>
#include <coconet/core/type.h>

#define DIMVECTOR_SMALL_VECTOR_OPTIMIZATION 5

namespace coconet
{
    class DimVectorIterator
    {
    public:
        DimVectorIterator(idx_type * p):ptr(p){}
        bool operator!= (const DimVectorIterator & other) const
        {
            return ptr != other.ptr;
        }

        idx_type& operator* () const 
        {
            return *ptr;
        }

        DimVectorIterator& operator++ ()
        {
            ++ptr;
            return *this;
        }

        DimVectorIterator operator++ (int)  
        {
            ++ptr;
            return *this;
        }

        DimVectorIterator& operator+(int offset)  
        {
            ptr += offset;
            return *this;
        }

    private:
        idx_type *ptr;
    };

    class DimVectorConstIterator
    {
    public:
        DimVectorConstIterator(const idx_type * p):ptr(p){}
        bool operator!= (const DimVectorConstIterator & other) const
        {
            return ptr != other.ptr;
        }

        const idx_type& operator* () const 
        {
            return *ptr;
        }

        DimVectorConstIterator& operator++ ()
        {
            ++ptr;
            return *this;
        }

        DimVectorConstIterator operator++ (int)  
        {
            ++ptr;
            return *this;
        }

        DimVectorConstIterator& operator+(int offset)  
        {
            ptr += offset;
            return *this;
        }

    private:
        const idx_type *ptr;
    };

    class DimVector
    {
    public:
        using value_type = idx_type;
        using iterator = DimVectorIterator;
    private:
        std::unique_ptr<idx_type[]> pointer_data;
        idx_type stack_data[DIMVECTOR_SMALL_VECTOR_OPTIMIZATION];
        idx_type dim_num;

    public:
        DimVector()
            : pointer_data(nullptr), dim_num(0)
        {
        }

        DimVector(idx_type size)
            : pointer_data(nullptr), dim_num(0)
        {
            if (size < 0)
                return;
            if (size > DIMVECTOR_SMALL_VECTOR_OPTIMIZATION)
            {
                pointer_data = std::make_unique<idx_type[]>(size);
            }

            dim_num = size;
        }

        DimVector(std::initializer_list<int> list)
            : pointer_data(nullptr), dim_num(0)
        {
            for (auto &each : list)
            {
                this->push_back(each);
            }
        }

        DimVector(const DimVector &other)
        {
            if (other.dim_num > DIMVECTOR_SMALL_VECTOR_OPTIMIZATION)
            {
                pointer_data = std::make_unique<idx_type[]>(other.dim_num);
                std::memcpy( pointer_data.get(), other. pointer_data.get(), other.dim_num * sizeof(idx_type));
            }
            else
            {
                std::memcpy(stack_data, other.stack_data, other.dim_num * sizeof(idx_type));
            }
            dim_num = other.dim_num;
        }

        DimVector(DimVector &&other)
        {
            if (other.dim_num > DIMVECTOR_SMALL_VECTOR_OPTIMIZATION)
            {
                pointer_data = std::move(other. pointer_data);
            }
            else
            {
                std::memcpy(stack_data, other.stack_data, other.dim_num * sizeof(idx_type));
            }
            dim_num = other.dim_num;
        }

        DimVector &operator=(const DimVector &other) noexcept
        {
            if (this != &other)
            {
                if (other.dim_num > DIMVECTOR_SMALL_VECTOR_OPTIMIZATION)
                {
                    pointer_data = std::make_unique<idx_type[]>(other.dim_num);
                    std::memcpy(pointer_data.get(), other.pointer_data.get(), other.dim_num * sizeof(idx_type));
                }
                else
                {
                    std::memcpy(stack_data, other.stack_data, other.dim_num * sizeof(idx_type));
                }
                dim_num = other.dim_num;
            }

            return *this;
        }

        DimVector &operator=(DimVector &&other) noexcept
        {
            if (this != &other)
            {
                if (other.dim_num > DIMVECTOR_SMALL_VECTOR_OPTIMIZATION)
                {
                    pointer_data = std::move(other.pointer_data);
                }
                else
                {
                    std::memcpy(stack_data, other.stack_data, other.dim_num * sizeof(idx_type));
                }
                dim_num = other.dim_num;
            }
            return *this;
        }

        bool operator==(const DimVector &other) const
        {
            if (dim_num != other.dim_num)
                return false;

            for (idx_type i = 0; i < dim_num; ++i)
                if (this->operator[](i) != other[i])
                    return false;

            return true;
        }

        bool operator!=(const DimVector &other) const
        {
            if (dim_num != other.dim_num)
                return true;

            for (idx_type i = 0; i < dim_num; ++i)
                if (this->operator[](i) != other[i])
                    return true;

            return false;
        }

        idx_type* data()
        {
            if (dim_num > DIMVECTOR_SMALL_VECTOR_OPTIMIZATION)
            {
                return pointer_data.get();
            }
            else
            {
                return stack_data;
            } 
        }

        DimVectorIterator begin() noexcept
        {
            return DimVectorIterator(this->data());
        }

        DimVectorIterator end() noexcept
        {
            return DimVectorIterator(this->data() + dim_num);
        }

        void erase(idx_type idx)
        {
            if (idx > 0 && idx < dim_num)
            {
                for (idx_type i = idx + 1; i < dim_num; ++i)
                {
                    this->operator[](i - 1) = this->operator[](i);
                }
                resize(size() - 1);
            }
        }

        void push_back(idx_type idx)
        {
            resize(size() + 1);
            this->operator[](size() - 1) = idx;
        }

        void resize(idx_type size)
        {
            if (size < 0 || size == dim_num)
                return;
            if (size > DIMVECTOR_SMALL_VECTOR_OPTIMIZATION)
            {
                if (dim_num > DIMVECTOR_SMALL_VECTOR_OPTIMIZATION)
                {
                    idx_type move_size = (size > dim_num ? dim_num : size);
                    std::unique_ptr<idx_type[]> temp(new idx_type[size]);
                    std::memcpy(temp.get(), pointer_data.get(), move_size * sizeof(idx_type));
                    pointer_data = std::move(temp);
                }
                else
                {
                    pointer_data = std::unique_ptr<idx_type[]>(new idx_type[size]);
                    std::memcpy(pointer_data.get(), stack_data, dim_num * sizeof(idx_type));
                }
            }
            else
            {
                if (dim_num > DIMVECTOR_SMALL_VECTOR_OPTIMIZATION)
                {
                    pointer_data = std::unique_ptr<idx_type[]>(nullptr);
                    if (size != 0)
                        std::memcpy(stack_data, pointer_data.get(), size * sizeof(idx_type));
                }
            }
            dim_num = size;
        }

        idx_type size() const { return this->dim_num; }

        idx_type flat_size() const
        {
            idx_type flat_size = 1;

            if (size() == 0)
            {
                flat_size = 0;
            }
            else
            {
                for (idx_type i = 0; i < size(); ++i)
                {
                    flat_size *= this->operator[](i);
                }
            }

            return flat_size;
        }

        bool in_range(idx_type dim) const
        {
            if (dim < 0)
                dim = dim_num + dim;

            return dim >= 0 && dim < dim_num;
        }

        idx_type &operator[](idx_type dim)
        {
            if (dim < 0)
                dim = dim_num + dim;

            if (dim < 0 || dim >= dim_num)
                throw std::runtime_error("index out of dim vector size");

            if (dim_num > DIMVECTOR_SMALL_VECTOR_OPTIMIZATION)
                return pointer_data[dim];
            else
                return stack_data[dim];
        }

        idx_type operator[](idx_type dim) const
        {
            if (dim < 0)
                dim = dim_num + dim;

            if (dim < 0 || dim >= dim_num)
                throw std::runtime_error("index out of dim vector size");

            if (dim_num > DIMVECTOR_SMALL_VECTOR_OPTIMIZATION)
                return pointer_data[dim];
            else
                return stack_data[dim];
        }
    };

    inline DimVector sort_index(DimVector dim)
    {
        DimVector sorted(dim.size());
        for (int i = 0; i < dim.size(); ++i)
            sorted[i] = i;

        for (int i = 0; i < dim.size() - 1; i++)
            for (int j = 0; j < dim.size() - 1 - i; j++)
                if (dim[j] < dim[j + 1])
                {
                    std::swap(dim[j], dim[j + 1]);
                    std::swap(sorted[j], sorted[j + 1]);
                }

        return sorted;
    }
} // namespace coconet

#endif