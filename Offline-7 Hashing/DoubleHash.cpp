#include <bits/stdc++.h>
using namespace std;
vector<string> v(1010);
#define C1 32
#define C2 115
class DoubleHash
{
    vector<string> hash;
    int minTableSize;
    int collisions;
    int elements;
    int tableSize;
    bool func;
    int probes;
    bool isCustom;

    int stringToInt(string str)
    {
        long long hashVal = 0;
        for (int i = 0; i < str.length(); i++)
        {
            hashVal = 37 * hashVal + str[i];
        }

        hashVal = hashVal % tableSize;
        // cout<<hashVal<<endl;
        if (hashVal < 0)
        {
            hashVal += tableSize;
        }

        return hashVal;
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

        return total % tableSize;
    }

    int auxHash(string s)
    {
        int sum = 0;
        for (int i = 0; i < s.size(); i++)
        {
            sum += s[i];
        }

        return sum % tableSize;
    }

    int hashFunction(string s)
    {
        if (func)
            return stringToInt(s);
        return flodingString(s);
    }
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

public:
    DoubleHash(int size = 10, bool func = true, string type = "double") : tableSize(nextPrime(max(size, 10))), elements(0), probes(0), collisions(0), func(func)
    {
        hash.resize(tableSize);
        if (type == "custom")
            isCustom = true;
        else
            isCustom = false;
    }

    void insert(string s)
    {
        if (elements == tableSize)
        {
            cout << "Hash Table is Full" << endl;
            return;
        }
        if (search(s))
        {
            cout << "already exists" << endl;
            return;
        }
        int index = hashFunction(s);
        // int i = 1;
        // while (hash[index] != "")
        // {
        //     index = (index + i * auxHash(s)) % tableSize;
        //     i++;
        //     collisions++;
        // }
        // hash[index] = s;
        // elements++;

        for (int i = 0; i < tableSize; i++)
        {
            if (!isCustom)
                index = (index + i * auxHash(s)) % tableSize;
            else
                index = (index + C1 * i * auxHash(s) + C2 * i * i) % tableSize;
            if (hash[index] == "")
            {
                hash[index] = s;
                elements++;
                return;
            }
            collisions++;
        }
        cout << "insertion failed---" << s << endl;
    }

    void Delete(string s)
    {
        if (!(search(s)))
        {
            cout << "string DNE" << endl;
            return;
        }
        int index = hashFunction(s);
        // int i = 1;
        // while (hash[index] != s)
        // {
        //     index = (index + i * auxHash(s)) % tableSize;
        //     i++;
        // }
        // hash[index] = "";
        // elements--;
        for (int i = 0; i < tableSize; i++)
        {
            if (!isCustom)
                index = (index + i * auxHash(s)) % tableSize;
            else
                index = (index + C1 * i * auxHash(s) + C2 * i * i) % tableSize;
            if (hash[index] == s)
            {
                hash[index] = "";
                elements--;
                return;
            }
            // collisions++;
        }
    }

    bool search(string s)
    {
        int index = hashFunction(s);
        // int i = 1;
        // while (hash[index] != s)
        // {
        //     index = (index + i * auxHash(s)) % tableSize;
        //     i++;
        //     if (hash[index] == "")
        //         return false;
        // }

        for (int i = 0; i < tableSize; i++)
        {
            if (!isCustom)
                index = (index + i * auxHash(s)) % tableSize;
            else
                index = (index + C1 * i * auxHash(s) + C2 * i * i) % tableSize;
            if (hash[index] == s)
                return true;
        }
        // return true;
        return false;
    }

    void printHash()
    {
        for (auto i : hash)
        {
            if (i == "")
                cout << "empty slot" << endl;
            else
                cout << i << endl;
        }
    }
};

string randomWordGenerator()
{
    // srand(time(0));
    static int counter = 0;          // Static variable to keep track of the number of calls
    srand(1000 + counter * counter); // Seed the random number generator with current time + counter
    counter++;                       // Increment the counter for the next call

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
    freopen("D_out.txt", "w", stdout);
    DoubleHash h(15, false);

    for (int i = 0; i < 15; i++)
    {
        string s = randomWordGenerator();
        v[i] = s;
        h.insert(s);

        // h.printHash();
        // cout << endl
        //      << endl;
    }

    h.printHash();

    for (int i = 0; i < 15; i++)
    {
        // cout << "deleting----" << v[i] << endl;
        h.Delete(v[i]);
        // h.printHash();
        // cout << endl
        //      << endl;
    }
    fclose(stdout);

    freopen("C_out.txt", "w", stdout);
    DoubleHash h1(15, false, "custom");

    for (int i = 0; i < 15; i++)
    {
        h1.insert(v[i]);
    }

    h1.printHash();

    for (int i = 0; i < 15; i++)
    {
        h1.Delete(v[i]);
    }
    fclose(stdout);

    // h.insert("abc");
    // h.insert("def");
    // h.insert("ghi");
    // h.insert("abc");

    // h.printHash();

    // h.Delete("abc");
    // h.Delete("def");
    // h.Delete("ghi");
    // h.Delete("abc");
}