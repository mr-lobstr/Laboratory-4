#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <tuple>
using namespace std;

using Output_data = tuple<double, double, double>;
using Outs = vector<Output_data>;

double f (double x)
{
    return pow(x, 2) + pow(M_E, x) - 2;
}


double deriv_f (double x)
{
    return 2 * x + pow(M_E, x);
}


pair<double, Outs>
method_bisection (double a, double b, double eps, size_t maxIters)
{
    Outs outs;
    double result = 0;

    for (size_t i = 0; i < maxIters and b-a >= eps; ++i)
    {
        double c = (a + b) / 2;
        result = c;
        outs.emplace_back(a, b, result);

        if (f(c) == 0)
            break;

        (f(a) * f(c) < 0 ? b : a) = c;
    }

    return {result, outs};
}


pair<double, Outs>
method_Newton (double x0, double eps, size_t maxIters)
{
    Outs outs;
    double result = 0;

    for (size_t i = 0; i < maxIters; ++i)
    {
        double xNext = x0 - f(x0) / deriv_f(x0);
        result = xNext;
        outs.emplace_back(xNext, x0, result);

        if (fabs(xNext - x0) < eps)
            break;

        x0 = xNext;
    }

    return {result, outs};
}


pair<double, Outs>
method_8 (double x, double xPrev, double eps, size_t maxIters)
{
    Outs outs;
    double result = 0;

    for (size_t i = 0; i < maxIters; ++i)
    {
        double xNext = x - (x - xPrev) * f(x) / (f(x) - f(xPrev));
        result = xNext;
        outs.emplace_back(x, xPrev, result);

        if (fabs(xNext - x) < eps)
            break;
        
        xPrev = x;
        x = xNext;
    }

    return {result, outs};
}

ostream & operator<< (ostream& out, Outs const& v)
{
    for (auto [a, b, r] : v)
    {
        out << setw(10) << left << a
            << setw(10) << left << b
            << setw(10) << left << r
            << endl;
    }

    return out;
}

int main()
{
    system("chcp 65001");
    
    double a = -2, b = -0.01, c = 1;
    ofstream out("file.txt");
    Outs outs, outs2;
    double res, res2;

    out << fixed << setprecision(4);

    tie(res, outs) = method_bisection (a, b, 0.001, 100);
    tie(res2, outs2) = method_bisection (b, c, 0.001, 100);

    out << "Решение методом половинного деления.\n"
        << "Корни: " << res << " " << res2 << endl
        << outs << endl << outs2 << endl;

    tie(res, outs) = method_Newton (a, 0.001, 100);
    tie(res2, outs2) = method_Newton (b, 0.001, 100);

    out << "Решение методом Ньютона.\n"
        << "Корни: " << res << " " << res2 << endl
        << outs << endl << outs2 << endl;

    tie(res, outs) = method_8 (a, b, 0.001, 100);
    tie(res2, outs2) = method_8 (b, c, 0.001, 100);

    out << "Решение комбинированным методом секущих-хорд.\n"
        << "Корни: " << res << " " << res2 << endl
        << outs << endl << outs2 << endl;

    out.close();
}