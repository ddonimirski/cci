#include <iostream>
#include <string>

using std::cin, std::cout, std::endl;
using std::string;


int main()
{
    string s; 
    cout << "type :";
    cin >> s;

    auto check = [](unsigned char c)
    {
        static bool arr[128] = {false};

        if (c >= 128) return false;
        auto const ret = arr[c];
        arr[c] = true;
        return ret;
    };

    for (auto const c: s)
    {
        if (check(c))
        {
            cout << "not unique\n";
            return 0;
        }
    }

    cout << "unique\n";
    return 0;
}
