#include <bits/stdc++.h>
using namespace std;
int Size;
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
    if (isPrime(N))
    {
        return N;
    }
    return nextPrime(N + 1);
}

int flodingString(string str)
{
    vector<int> v;
    int total = 0;
    int chunk = str.length() / 4;
    int index = 0;
    for (int i = 0; i < 4; i++)
    {
        int sum = 0;
        int p = chunk - 1;
        for (int j = index; j < index + chunk; j++)
        {
            sum += pow(10, p) * (str[j] - '0');
            p--;
        }
        total += sum;
    }
    int extra = str.size() - chunk * 4;
    int p = extra - 1;
    int sum = 0;
    for (int i = chunk * 4; i < str.size(); i++)
    {
        sum = 0;
        sum += pow(10, p) * (str[i] - '0');
        p--;
    }
    total += sum;

    return total % Size;
}

int stringToInt(string str)
{
    long long hashVal = 0;
    for (int i = 0; i < str.length(); i++)
    {
        hashVal = 37 * hashVal + str[i];
    }

    hashVal = hashVal % Size;
    // cout<<hashVal<<endl;
    if (hashVal < 0)
    {
        hashVal += Size;
    }

    return hashVal;
}

string randomWordGenerator()
{
    // srand(500);
    int len = (rand() % (10 - 5 + 1)) + 5;
    // cout << len << endl;

    int wordSize = len;
    string word = "";

    for (int i = 0; i < len; i++)
    {
        word += 'a' + (rand() % 26);
    }

    // cout << word << endl;

    return word;
}
int main()
{
    // int x;
    // for (int i = 0; i < 100; i++)
    // {
    //     x = nextPrime(i);
    //     cout << "nextPrime of " << i << " is " << x << endl;
    // }
    Size = nextPrime(10);
    for (int i = 0; i < 10; i++)
    {
        string s = randomWordGenerator();
        cout << stringToInt(s) << " " << flodingString(s) << endl;
    }

    return 0;
}