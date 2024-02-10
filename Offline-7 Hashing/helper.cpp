#include <bits/stdc++.h>
using namespace std;
bool isPrime(int N)
{
    if (N <= 1)
        return false;
    if (N < 4)
        return true;
    if (N % 2 == 0 || N % 3 == 0)
        return false;
    for (int i = 5; i * i <= N; i += 6)
    {
        if (N % i == 0 || N % (i + 2) == 0)
            return false;
    }
    return true;
}

int nextPrime(int N)
{
    if (isPrime(N + 1))
    {
        return N + 1;
    }
    return nextPrime(N + 1);
}
int main()
{
    int x;
    for (int i = 0; i < 100; i++)
    {
        x = nextPrime(i);
        cout << "nextPrime of " << i << " is " << x << endl;
    }

    return 0;
}