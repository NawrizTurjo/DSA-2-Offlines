#include <bits/stdc++.h>
using namespace std;
#define DEFAULT_SIZE 10
#define DEFAULT_CHAIN 3
vector<string> v(10010);
class HashTable
{
    vector<list<pair<int, string>>> hash;
    int currentTableSize;
    int probes;
    int collisions;
    int minTableSize;
    int elements;
    int maxChainLength;
    // pair<int, int> currMax;
    int order;

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
        if (isPrime(N))
        {
            return N;
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

    double LoadFactor()
    {
        return (double)elements / currentTableSize;
    }

public:
    HashTable(int size = DEFAULT_SIZE, int maxChainLength = DEFAULT_CHAIN) : currentTableSize(nextPrime(size)), elements(0), maxChainLength(maxChainLength), probes(0), collisions(0), order(0)
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
        if (hash[index].size() >= maxChainLength
            // || elements / currentTableSize > 0.2
            // || probes / (0.1 * currentTableSize) > 2
            || currentTableSize > 100 && probes / (0.1 * currentTableSize) > 2)
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
        ++order;

        hash[index].push_front({order, str});
        elements++;

        // cout << "Total Elements: " << elements << endl;
        // cout << "Total Collisions: " << collisions << endl;
    }

    bool Delete(string str)
    {
        // cout << "Deleting " << str << endl;
        if (search(str) == false)
        {
            return false;
        }
        int index = stringToInt(str);
        auto it = hash[index].begin();
        while (it != hash[index].end())
        {
            if (it->second == str)
            {
                hash[index].erase(it);
                elements--;

                if (elements / currentTableSize < 0.2 || currMaxLength() < maxChainLength * 0.8)
                {
                    reHash(false);
                }

                // cout << "Total Elements: " << elements << endl;
                // cout << "Total Collisions: " << collisions << endl;

                return true;
            }
            it++;
        }
        return false;
    }

    bool search(string str)
    {
        // cout << "search" << endl;
        int index = stringToInt(str);

        list<pair<int, string>> currList = hash[index];
        // cout << currList.size() << endl;
        if (currList.size() == 0)
            return false; // search failed

        // cout << "search2" << endl;
        probes++;
        for (auto s : currList)
        {
            if (s.second == str)
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
        // if (state)
        //     cout << "Rehashing for Insertion" << endl;
        // else
        //     cout << "Rehashing for Deletion" << endl;

        // printHash();
        fclose(stdout);
        freopen("CON", "w", stdin);

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
        cout << "Load Factor: " << (double)elements / currentTableSize << endl;
        cout << "Maximum Chain Length: " << currMaxLength() << endl;

        fclose(stdout);
        freopen("output.txt", "w", stdout);
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

        vector<list<pair<int, string>>> newHash(currentTableSize);

        for (auto i : hash)
        {
            for (auto j : i)
            {
                int index = stringToInt(j.second);
                newHash[index].push_front(j);
            }
        }
        hash.resize(0);
        hash = newHash;
    }

    double getAverageProbes(int num)
    {
        probes = 0;
        for (int i = 0; i < num; i++)
        {
            search(v[i]);
        }

        cout << "probes -> " << probes << endl;

        return (double)probes / (1.0 * num);
    }

    void printHash()
    {
        for (auto i : hash)
        {

            for (auto j : i)
            {
                cout << j.second << "-> " << j.first << " ";
            }
            cout << endl;
        }
    }
};
string randomWordGenerator()
{
    // srand(500);
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
    // srand(500);
    freopen("output.txt", "w", stdout);
    // freopen("string.txt", "w", stdout);
    HashTable h;

    for (int i = 0; i < 10000; i++)
    {
        string s = randomWordGenerator();
        v[i] = s;
        h.insert(s);
    }

    cout << "Average Probes From Main:  " << h.getAverageProbes(1000) << endl;
    // h.printHash();

    // for (int i = 0; i < 10000; i++)
    // {
    //     h.Delete(v[i]);
    // }

    // cout << endl
    //      << endl;
    fclose(stdout);

    // HashTable h1;
    // h1.insert("abc");
    // h1.printHash();
}