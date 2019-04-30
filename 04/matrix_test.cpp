#include <iostream>
#include <algorithm>
#include "matrix.hpp"

using std::cout, std::cerr, std::endl;

int main()
{
    {
        matrix_compsize<int,10,5> m;

        for (int r = 0; r < m.rows; ++r)
            for (int c = 0; c < m.cols; ++c)
                m[r][c] = r*m.cols + c;
        cout << m << endl;
    }

    {
        matrix_sized <int> m(10,5);

        for (int r = 0; r < m.rows; ++r)
            for (int c = 0; c < m.cols; ++c)
                m[r][c] = r*m.cols + c;
        cout << m << endl;
    }
}
