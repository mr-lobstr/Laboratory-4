#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <random>
#include <algorithm>
using namespace std;

minstd_rand0 gen;

vector<int> random_array (size_t length, int minV, int maxV)
{
    vector<int> arr(length);

    for (auto& el : arr)
    {
        el = minV + (gen() % (maxV - minV));
    }

    return arr;
}

template <class T>
ostream & operator<< (ostream& out, vector<T> const& v)
{
    for (auto el : v)
    {
        out << el << " ";
    }

    return out;
}

vector<int> task2 (vector<int> const& v)
{
    vector<int> res;
    for (size_t i = 0; i < v.size(); i += 2)
    {
        if (v[i] % 2 == 0)
            res.push_back(v[i]);
    }
    return res;
}

void task3 (vector<int> const& arr1, vector<int> const& arr2)
{
    vector<int> res;

    copy_if (arr2.begin(), arr2.end(), back_inserter(res), [&arr1] (int i) {
        return count(arr1.begin(), arr1.end(), i) != 0;
    });

    if (res.empty())
    {
        cout << "Ни одно число из arr2 в arr1 не встречается." << endl;
        return;
    }

    cout << "В arr1 встречаются следующие элементы из arr2: " << endl;
    for (auto el : res)
    {
        cout << el << " ("
             << count(arr1.begin(), arr1.end(), el)
             << ") ";
    }
    cout << endl;
}

vector<char> task4 (vector<char> v)
{
    rotate(v.begin(), v.begin() + 1, v.end());
    return v;
}

int f (int i)
{
    int digits[4];
    for (auto& d :digits)
    {
        d = i % 10;
        i /= 10;
    }

    auto [d, c, b, a] = digits;

    return c * 1000
         + b * 100
         + d * 10
         + a;
}

void task5(vector<int> const& v)
{
    vector<int> v2 = v;
    for (auto& el : v2)
    {
        el = f(el);
    }

    cout << endl << v << endl << v2 << endl;

    sort(v2.begin(), v2.end());
    int sumV = accumulate(v.begin(), v.end(), 0);
    int sumV2 = accumulate(v2.begin(), v2.end(), 0);

    cout << "Сумма элементов v (" << sumV << ") "
         << (sumV > sumV2 ? ">" : "<")
         << " суммы элементов v2 (" << sumV2 << ")."
         << endl;
}

int main()
{
    system("chcp 65001");
    size_t n;
    cin >> n;
    
    vector<int> arr1 = random_array(n, 15, 31);
    vector<int> arr2 = random_array(5, 15, 31);
    cout << arr1 << endl << arr2 << endl << endl;

    vector<int> res2 = task2(arr1);
    cout << "Чётные элементы массива arr1 на нечётных местах: "
         << res2 << endl <<"Их количество: "
         << res2.size() << endl << endl;

    task3(arr1, arr2);

    vector<char> v4 = {'v', '!', 'N', 'R', '(', '3'};
    cout << endl << v4 << endl
         << task4(v4) << endl;

    task5(random_array(10, 1000, 9001));
}