#if !defined MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <memory>



template<class T, size_t ROW=1, size_t COL=1>
struct matrix_compsize
{
    size_t const rows;
    size_t const cols;
    T __cont[COL*ROW];

    explicit matrix_compsize(T const val = 0)
        :rows(ROW), cols(COL)
    {
        static_assert(COL>0 && ROW>0);
        for (auto& v: __cont)
            v = val;
    }


    T* operator[](int row)
    {
        return &__cont[row*cols];
    }


    T const* operator[](int row) const
    {
        return const_cast<matrix_compsize*>(this)->operator [] (row);
    }

    friend std::ostream& operator << (std::ostream& os, matrix_compsize const& m)
    {
        for (int r = 0; r < m.rows; r++)
        {
            for (int c = 0; c < m.cols; c++)
            {
                os << m[r][c] << ' ';
            }
            os << '\n';
        }

        return os;
    }
};


template<class T>
struct matrix_sized
{
    size_t const rows;
    size_t const cols;
    std::unique_ptr<T> __cont;

    explicit matrix_sized(size_t r, size_t c, T const& val = 0)
        :rows(r), cols(c), __cont(new T[rows*cols])
    {
       auto* b = __cont.get(); 
       auto* const e = b + (rows*cols);

       while (b !=  e)
       {
           *b++ = val;
       }
    }

    T* operator[](int row)
    {
        return &__cont.get()[row*cols];
    }


    T const* operator[](int row) const
    {
        return const_cast<matrix_sized*>(this)->operator [] (row);
    }


    friend std::ostream& operator << (std::ostream& os, matrix_sized const& m)
    {
        for (int r = 0; r < m.rows; r++)
        {
            for (int c = 0; c < m.cols; c++)
            {
                os << m[r][c] << ' ';
            }
            os << '\n';
        }

        return os;
    }
};

#endif
