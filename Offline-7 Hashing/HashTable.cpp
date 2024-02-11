#include <bits/stdc++.h>
using namespace std;
#define DEFAULT_SIZE 10
#define DEFAULT_CHAIN 3
vector<string> v(1010);
class HashTable
{
    vector<list<string>> hash;
    int currentTableSize;
    int probes;
    int collisions;
    int minTableSize;
    int elements;
    int maxChainLength;
    // pair<int, int> currMax;

    int stringToInt(string str)
    {
        long long hashVal = 0;
        for (int i = 0; i < str.length(); i++)
        {
            hashVal = 37 * hashVal + str[i];
        }

        hashVal = hashVal % currentTableSize;
        // cout<<hashVal<<endl;
        if (hashVal < 0)
        {
            hashVal += currentTableSize;
        }

        return hashVal;
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
        if (isPrime(N + 1))
        {
            return N + 1;
        }
        return nextPrime(N + 1);
    }

    int currMaxLength()
    {
        int max = 0;
        for (auto i : hash)
        {
            if (i.size() > max)
            {
                max = i.size();
            }
        }
        return max;
    }

public:
    HashTable(int size = DEFAULT_SIZE, int maxChainLength = DEFAULT_CHAIN) : currentTableSize(nextPrime(size)), elements(0), maxChainLength(maxChainLength), probes(0), collisions(0)
    {
        hash.resize(currentTableSize);
        minTableSize = currentTableSize;
        // currMax = {0, 0};
    }
    void insert(string str)
    {
        // cout << "insert" << endl;
        if (search(str))
        {
            // cout << str << " is already there" << endl;
            return;
        }
        int index = stringToInt(str);
        // cout << "insert--checking" << endl;
        // cout << index << endl;
        if (hash[index].size() >= maxChainLength)
        {
            reHash(true);
            index = stringToInt(str);
        }

        if (hash[index].size() != 0)
        {
            collisions++;
        }

        // if (hash[index].size() > currMax.second)
        // {
        //     currMax = {index, hash[index].size()};
        // }

        hash[index].push_front(str);
        elements++;

        cout << "Total Elements: " << elements << endl;
        cout << "Total Collisions: " << collisions << endl;
    }

    bool Delete(string str)
    {
        cout << "Deleting " << str << endl;
        if (search(str) == false)
        {
            return false;
        }
        int index = stringToInt(str);
        auto it = find(hash[index].begin(), hash[index].end(), str);
        if (it != hash[index].end())
        {
            hash[index].erase(it);
            elements--;

            // if (currMaxLength() < maxChainLength * 0.8 && elements >= minTableSize)
            // {
            //     reHash(false);
            // }

            if(elements/currentTableSize < 0.2)
            {
                reHash(false);
            }

            cout << "Total Elements: " << elements << endl;
            cout << "Total Collisions: " << collisions << endl;

            return true;
        }
        return false;
    }

    bool search(string str)
    {
        // cout << "search" << endl;
        int index = stringToInt(str);

        list<string> currList = hash[index];
        // cout << currList.size() << endl;
        if (currList.size() == 0)
            return false; // search failed

        // cout << "search2" << endl;
        for (auto s : currList)
        {
            if (s == str)
            {
                return true;
            }
            probes++;
        }
        return false; // search failed
    }

    void makeEmpty()
    {
        for (auto i : hash)
        {
            i.clear();
        }
    }

    void reHash(bool state)
    {
        if (state)
            cout << "Rehashing for Insertion" << endl;
        else
            cout << "Rehashing for Deletion" << endl;
        // printHash();
        // freopen("string.txt", "r", stdin);

        int x = 0;
        probes = 0;
        while (x < 1000)
        {
            string s;
            s = v[x];
            search(s);
            x++;
        }
        cout << "Total Probes: " << probes << endl;
        cout << "Avereage Probes: " << (double)probes / 1000 << endl;

        // fclose(stdin);
        collisions = 0; // as new Hash
        probes = 0;     // as new Hash
        if (state)      // T means insertion reHash
            currentTableSize = nextPrime(currentTableSize * 2);
        else
            currentTableSize = nextPrime(currentTableSize / 2);

        // vector<list<string>> oldHash = hash;

        // hash.resize(0);
        // hash.resize(currentTableSize);
        // for (auto i : oldHash)
        // {
        //     for (auto j : i)
        //     {
        //         // int index = stringToInt(j);
        //         // hash[index].push_front(j);
        //         insert(j);
        //     }
        // }

        vector<list<string>> newHash(currentTableSize);

        for (auto i : hash)
        {
            for (auto j : i)
            {
                int index = stringToInt(j);
                newHash[index].push_front(j);
            }
        }
        hash.resize(0);
        hash = newHash;
    }

    void printHash()
    {
        for (auto i : hash)
        {

            for (auto j : i)
            {
                cout << j << " ";
            }
            cout << endl;
        }
    }
};
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
    // srand(500);
    freopen("output.txt", "w", stdout);
    // freopen("string.txt", "w", stdout);
    HashTable h;

    for (int i = 0; i < 1000; i++)
    {
        string s = randomWordGenerator();
        v[i] = s;
        h.insert(s);
    }

    for (int i = 0; i < 1000; i++)
    {
        h.Delete(v[i]);
    }

    cout << endl
         << endl;
    h.printHash();
    fclose(stdout);
}