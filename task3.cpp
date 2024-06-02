#include <iostream>
#include <numeric>
#include <random>
#include <cmath>
#include <iomanip>
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


double real_math_expectation (vector<int> const& v)
{
    return accumulate (v.begin(), v.end(), 0.0) / v.size();
}


double p_table (int df)
{
    static double his [] = {
        3.84, 5.99, 7.81, 9.49, 11.07,
        12.59, 14.07, 15.51, 16.92, 18.31
    };

    return his[df-1];
}


double hi_square (vector<int> const& v, int minV, int maxV, size_t numIntv)
{
    double expCnt = v.size() / static_cast<double>(numIntv);
    vector<int> intervals (numIntv, 0);

    for (auto el : v)
    {
        size_t ind = numIntv * (el - minV) / (maxV - minV + 1);
        ++intervals[ind];
    }

    return accumulate (intervals.begin(), intervals.end(), 0.0,
        [expCnt] (double prev, int nCnt)
        {
            return prev + pow(nCnt - expCnt, 2) / expCnt;
        }
    );
}

int main()
{
    system("chcp 65001");
    size_t df = 9;
    vector<vector<int>> arrays = 
    {
        random_array(50, 1, 100),
        random_array(100, 1, 100),
        random_array(1000, 1, 100)
    };
    
    for (auto const& arr : arrays)
    {
        double hi = hi_square(arr, 1, 100, df);

        cout << "Ожидаемое математическое ожидание: " << df << endl
             << "Реальное математическое ожидание: " 
             << real_math_expectation(arr) << endl
             << "Значение хи-квадрат: " << hi << endl
             << "Гипотеза о нормально распределении "
             << (hi < p_table(df) ? "не" : "") << " подтверждается." << endl;
        cout << endl;
    }
}