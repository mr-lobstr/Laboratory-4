#include <iostream>
#include <tuple>
#include <cmath>
#include <vector>
using namespace std;

long long pow_mod(long long a, long long x, long long p)
{
    long long result = 1;

    while (x > 0)
    {
        if (x % 2 == 1)
            result = result * a % p;

        a = a * a % p;
		x /= 2;
    }

    return result;
}

pair <long long, long long>
pseudo_rand_BBS (long long x_n, long long M)
{
	long long rndS = 0;
	
	for (int i = 0; i < sizeof(long long) * 8; ++i)
	{
		x_n = pow_mod (x_n, 2, M);
		rndS = rndS * 2 + (x_n % 2);
	}

	return {rndS, x_n};
}

pair <vector<long long>, long long>
pseudo_rand_array (size_t len,  long x_n, long long M)
{
    vector<long long> res (len);
    long long r, x = x_n;

    for (auto& el : res)
    {
        tie(r, x) = pseudo_rand_BBS(x, M);
        el = r;
    }

    return {res, x};
}

int main()
{
    long long p = 6025631;
	long long q = 8478859;

    auto [rndVec, gen] = pseudo_rand_array(10, 1234, p*q);

    for (auto el : rndVec)
    {
        cout << el << endl;
    }

    cout << endl;
}