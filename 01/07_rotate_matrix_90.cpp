
#include <iostream>

using std::cout, std::cin, std::endl;

constexpr auto MAX_STR = 200;

struct matrix final
{
    int _N;
    unsigned* _arr;

    explicit matrix(int N):_N(N), _arr(new unsigned [_N*_N])
    {

    }

    ~matrix()
    {
        delete [] _arr;
    }

    unsigned* operator[] (int i)
    {
        return _arr + i * _N;
    }

    unsigned const* operator[] (int i) const
    {
        return _arr + i * _N;
    }

    friend std::ostream& operator << (std::ostream& os, matrix const& m)
    {
        for (int i = 0; i < m._N; ++i)
        {
            for (int j = 0; j < m._N; ++j)
            {
                os << m[i][j] << '\t';
            }
            os << endl;
        }

        return os;
    }
};


void rotate(matrix& m)
{
    auto const n = m._N;

    for (auto layer = 0; layer < n/2; ++layer)
    {
        auto const b = layer;
        auto const e = n - 1 - layer;
        for (int i = b; i < e; ++i)
        {
            auto const off = i - b;
            auto const tmp = m[b][i];
            m[b][i] = m[e-off][b];
            m[e-off][b] = m[e][e-off];
            m[e][e-off] = m[i][e];
            m[i][e] = tmp;
        }
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    int N;
    cin >> N;

    if (N <= 0)
    {
        cout << "N must be greater then 0 " << endl;
        return 0;
    }

    matrix m{N};

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            cin >> m[i][j];

    rotate(m);
    cout << m << endl;
}
