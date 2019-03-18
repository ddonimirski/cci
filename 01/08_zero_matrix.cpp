#include <iostream>

using std::cout, std::cin, std::endl;

constexpr auto MAX_STR = 200;

struct matrix final
{
    int _N;
    int _M;
    unsigned* _arr;

    explicit matrix(int N, int M):_N(N), _M(M), _arr(new unsigned [_N*_M])
    {

    }

    ~matrix()
    {
        delete [] _arr;
    }

    unsigned* operator[] (int i)
    {
        return _arr + i * _M;
    }

    unsigned const* operator[] (int i) const
    {
        return _arr + i * _M;
    }


    friend std::ostream& operator << (std::ostream& os, matrix const& m)
    {
        for (int i = 0; i < m._N; ++i)
        {
            for (int j = 0; j < m._M; ++j)
            {
                os << m[i][j] << '\t';
            }
            os << endl;
        }

        return os;
    }
};

template<class T>
struct scope_del
{
    int __n;
    T* const __ptr;

    scope_del(int N):__n(N), __ptr(new T[N])
    {
    }

    ~scope_del()
    {
        delete [] __ptr;
    }

    T operator[](int i) const
    {
        return __ptr[i];
    }

    T& operator[](int i)
    {
        return __ptr[i];
    }

    friend std::ostream& operator <<(std::ostream& os, scope_del const& arr)
    {
        for (int i = 0; i < arr.__n; ++i)
            os << arr.__ptr[i] << ' ';
        return os;
    }
};

#if defined FIRST // O(N) memory, O(NM)

void zero_matrix(matrix& m)
{
    scope_del<bool> row{m._N};
    scope_del<bool> col{m._M};

    for (int i = 0; i < m._N; ++i)
        for (int j = 0; j < m._M; ++j)
            if (m[i][j] == 0)
            {
                row[i] = true;
                col[j] = true;
            }


    cout << row << endl;
    cout << col << endl;

    for (int i = 0; i < m._N; ++i)
    {
        if (row[i])
        {
            for (int j = 0; j < m._M; ++j)
                m[i][j] = 0;
        }
    }

    for (int j = 0; j < m._M; ++j)
    {
        if (col[j])
        {
            for (int i = 0; i < m._N; ++i)
                m[i][j] = 0;
        }
    }
}

#else

// O(1) memory space, O(NM)
void zero_matrix(matrix& m)
{
    bool rowZero = false, colZero = false;

    for (int j = 0; j < m._M; ++j)
        if (m[0][j] == 0)
        {
            rowZero = true;
            break;
        }

    for (int j = 0; j < m._N; ++j)
        if (m[j][0] == 0)
        {
            colZero = true;
            break;
        }


    for (int i = 0; i < m._N; ++i)
        for (int j = 0; j < m._M; ++j)
            if (m[i][j] == 0)
            {
                m[0][j] = 0;
                m[i][0] = 0;
            }


    cout << rowZero << ' ' << colZero << ' ' << endl;
    cout << m << endl;


    for (int i = 0; i < m._N; ++i)
    {
        if (m[i][0] == 0)
        {
            for (int j = 0; j < m._M; ++j)
                m[i][j] = 0;
        }
    }

    for (int j = 0; j < m._M; ++j)
    {
        if (m[0][j] == 0)
        {
            for (int i = 0; i < m._N; ++i)
                m[i][j] = 0;
        }
    }

    if (colZero)
        for (int i = 0; i < m._N; ++i)
            m[i][0] = 0;

    if (rowZero)
        for (int j = 0; j < m._M; ++j)
            m[0][j] = 0;
}
#endif

int main()
{
    std::ios_base::sync_with_stdio(false);
    int N, M;
    cin >> N >> M;
    cout << N << 'x' << M << endl;

    if (N <= 0 || M <= 0)
    {
        cout << "N and M must be greater then 0 " << endl;
        return 0;
    }

    matrix m{N, M};

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            cin >> m[i][j];

    zero_matrix(m);
    cout << m << endl;
    return 0;
}
