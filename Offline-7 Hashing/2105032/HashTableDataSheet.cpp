#include <bits/stdc++.h>
using namespace std;

#define CHAINING 1
#define DOUBLE 2
#define CUSTOM 3

#define DEFAULT_SIZE 10
#define DEFAULT_CHAIN 3

#define C1 32
#define C2 115

#define SEED1 2105032
#define SEED2 12103115

vector<string> v(20050);

class Hashing
{
    vector<list<pair<long long, string>>> chaining;
    vector<pair<long long, string>> doubleHash;
    vector<pair<long long, string>> customHash;
    vector<bool> isElement;

    long long currentTableSize;
    long long probes;
    long long collisions;
    long long minTableSize;
    long long elements;
    long long maxChainLength;
    long long order;
    long long hashFunction;

    long long hashType;
    long long insertCount;
    long long deleteCount;

    long long hash1(string str)
    {
        long long hashVal = 0;
        for (long long i = 0; i < str.length(); i++)
        {
            hashVal = 37 * hashVal + str[i];
        }

        hashVal = hashVal % currentTableSize;
        if (hashVal < 0)
        {
            hashVal += currentTableSize;
        }

        return hashVal;
    }

    long long hash2(const string &str)
    {
        unsigned long long hash = 5381;
        for (char c : str)
        {
            hash = ((hash << 5) + hash) + c;
        }
        hash = hash % currentTableSize;
        if (hash < 0)
        {
            hash += currentTableSize;
        }

        return hash;
    }

    bool isPrime(long long N)
    {
        if (N <= 1)
            return false;
        if (N < 4)
            return true;
        if (N % 2 == 0 || N % 3 == 0)
            return false;
        for (long long i = 5; i * i <= N; i += 6)
        {
            if (N % i == 0 || N % (i + 2) == 0)
                return false;
        }
        return true;
    }

    long long nextPrime(long long N)
    {
        if (isPrime(N))
        {
            return N;
        }
        return nextPrime(N + 1);
    }

    long long auxHash(string s)
    {
        long long sum = 0;
        for (long long i = 0; i < s.size(); i++)
        {
            sum += s[i];
        }

        return sum % currentTableSize;
    }

    long long getHash(string s)
    {
        if (hashFunction == 1)
            return hash1(s);
        else
            return hash2(s);
    }

    long long currMaxLength()
    {
        long long max = 0;
        for (auto i : chaining)
        {
            if (i.size() > max)
            {
                max = i.size();
            }
        }
        return max;
    }

public:
    Hashing(long long type, long long hashFunction, long long size = DEFAULT_SIZE, long long maxChainLength = DEFAULT_CHAIN) : currentTableSize(nextPrime(size)), elements(0), maxChainLength(maxChainLength), probes(0), collisions(0), order(0), hashFunction(hashFunction), insertCount(0), deleteCount(0)
    {
        if (type == CHAINING)
        {
            chaining.resize(currentTableSize);
            doubleHash.resize(0);
            customHash.resize(0);
            hashType = CHAINING;
        }
        else if (type == DOUBLE)
        {
            doubleHash.resize(currentTableSize);
            chaining.resize(0);
            customHash.resize(0);
            hashType = DOUBLE;
        }
        else if (type == CUSTOM)
        {
            customHash.resize(currentTableSize);
            chaining.resize(0);
            doubleHash.resize(0);
            hashType = CUSTOM;
        }
        isElement.resize(currentTableSize);
        for (long long i = 0; i < currentTableSize; i++)
        {
            isElement[i] = false;
        }
    }

    ~Hashing()
    {
        chaining.clear();
        doubleHash.clear();
        customHash.clear();
    }

    void clear()
    {
        chaining.clear();
        doubleHash.clear();
        customHash.clear();
        currentTableSize = 0;
        probes = 0;
        collisions = 0;
        minTableSize = 0;
        elements = 0;
        maxChainLength = 0;
        order = 0;
        hashFunction = 0;

        hashType = 0;
        insertCount = 0;
        deleteCount = 0;
    }

    void reInitialize(long long type, long long hashFunction, long long size = DEFAULT_SIZE, long long maxChainLength = DEFAULT_CHAIN)
    {
        clear();
        this->currentTableSize = nextPrime(size);
        elements = 0;
        this->maxChainLength = maxChainLength;
        probes = 0;
        collisions = 0;
        order = 0;
        this->hashFunction = hashFunction;
        insertCount = 0;
        deleteCount = 0;
        this->hashType = type;

        if (type == CHAINING)
        {
            chaining.assign(currentTableSize, list<pair<long long, string>>());
            doubleHash.clear();
            customHash.clear();
            hashType = CHAINING;
        }

        else if (type == DOUBLE)
        {
            doubleHash.resize(currentTableSize);
            chaining.resize(0);
            customHash.resize(0);
            hashType = DOUBLE;
        }
        else if (type == CUSTOM)
        {
            customHash.resize(currentTableSize);
            chaining.resize(0);
            doubleHash.resize(0);
            hashType = CUSTOM;
        }
        isElement.resize(currentTableSize);
        for (long long i = 0; i < currentTableSize; i++)
        {
            isElement[i] = false;
        }
    }

    void insert(string s, long long key)
    {
        double load = (double)elements / (double)currentTableSize;
        if (elements >= currentTableSize)
        {
            collisions++;
            return;
        }
        if (search(s))
        {
            return;
        }
        long long index = getHash(s);
        insertCount++;
        if (hashType == CHAINING)
        {
            if (insertCount == 100 && chaining[index].size() >= maxChainLength || currentTableSize > 100 && probes / (0.1 * currentTableSize) > 2)
            {
                insertCount = 0;
                reHash(true);
                index = getHash(s);
            }

            if (chaining[index].size() != 0)
            {
                collisions++;
            }

            chaining[index].push_front({key, s});
            elements++;
        }
        else if (hashType == DOUBLE)
        {

            bool isCollision = false;
            long long prev = collisions;

            for (long long i = 0; i < currentTableSize; i++)
            {
                index = (index + i * auxHash(s)) % currentTableSize;

                if (isElement[index] == false)
                {
                    isElement[index] = true;
                    doubleHash[index].first = key;
                    doubleHash[index].second = s;
                    elements++;
                    return;
                }
                if (!isCollision)
                {
                    collisions++;
                    isCollision = true;
                }
            }
            collisions = prev;
            return;
        }
        else if (hashType == CUSTOM)
        {
            bool isCollision = false;
            long long prev = collisions;

            for (long long i = 0; i < currentTableSize; i++)
            {
                index = (index + C1 * i * auxHash(s) + C2 * i * i) % currentTableSize;

                if (index < 0 || index >= currentTableSize)
                {
                    return;
                }

                if (isElement[index] == false)
                {
                    isElement[index] = true;
                    customHash[index].first = key;
                    customHash[index].second = s;
                    elements++;
                    return;
                }
                if (!isCollision)
                {
                    collisions++;
                    isCollision = true;
                }
            }
            collisions = prev;
            return;
        }
    }

    void Delete(string str)
    {
        if (search(str) == false)
        {
            return;
        }
        long long index = getHash(str);
        if (hashType == CHAINING)
        {
            auto it = chaining[index].begin();
            while (it != chaining[index].end())
            {
                if (it->second == str)
                {
                    chaining[index].erase(it);
                    elements--;
                    deleteCount++;

                    if (elements / currentTableSize < 0.2 || currMaxLength() < maxChainLength * 0.8 || deleteCount >= 100)
                    {
                        deleteCount = 0;
                        reHash(false);
                    }
                    return;
                }
                it++;
            }
            return;
        }
        else if (hashType == DOUBLE)
        {
            for (long long i = 0; i < currentTableSize; i++)
            {

                index = (index + i * auxHash(str)) % currentTableSize;
                if (doubleHash[index].second == str)
                {
                    doubleHash[index].second = "";
                    elements--;
                    return;
                }
            }
        }
        else if (hashType == CUSTOM)
        {
            for (long long i = 0; i < currentTableSize; i++)
            {

                index = (index + C1 * i * auxHash(str) + C2 * i * i) % currentTableSize;
                if (customHash[index].second == str)
                {
                    customHash[index].second = "";
                    elements--;
                    return;
                }
            }
        }
    }

    bool search(string s)
    {
        long long index = getHash(s);
        long long oldProbes = probes;
        if (hashType == CHAINING)
        {
            list<pair<long long, string>> currList = chaining[index];
            if (currList.size() == 0)
                return false;

            probes++;
            for (auto i : currList)
            {
                if (i.second == s)
                {
                    return true;
                }
                probes++;
            }
            probes = ++oldProbes;
            return false;
        }
        else if (hashType == DOUBLE)
        {
            probes++;

            for (long long i = 0; i < currentTableSize; i++)
            {
                index = (index + i * auxHash(s)) % currentTableSize;

                if (doubleHash[index].second == s)
                    return true;
                probes++;
            }
            probes = ++oldProbes;
            return false;
        }
        else if (hashType == CUSTOM)
        {
            probes++;

            for (long long i = 0; i < currentTableSize; i++)
            {
                index = (index + C1 * i * auxHash(s) + C2 * i * i) % currentTableSize;

                if (customHash[index].second == s)
                    return true;
                probes++;
            }
            probes = ++oldProbes;
            return false;
        }
        probes = ++oldProbes;
        return false;
    }

    void reHash(bool state)
    {
        if (hashType != CHAINING)
            return;

        long long x = 0;
        probes = 0;
        while (x < 2000)
        {
            string s;
            s = v[x];
            search(s);
            x++;
        }
        ofstream file;
        file.open("rehash_log.txt", ios::app);
        file << "-------Rehashing------" << endl;
        file << "Total Probes: " << probes << endl;
        file << "Avereage Probes: " << (double)probes / 2000 << endl;
        file << "Load Factor: " << (double)elements / currentTableSize << endl;
        file << "Maximum Chain Length: " << currMaxLength() << endl;
        file << "Total Collisions: " << collisions << endl;
        file << "Total Elements: " << elements << endl;
        file << "----------------------" << endl
             << endl;

        file.close();
        elements = 0;
        probes = 0;
        if (state)
            currentTableSize = nextPrime(currentTableSize * 2);
        else
            currentTableSize = nextPrime(currentTableSize / 2);

        vector<list<pair<long long, string>>> oldHash = chaining;

        chaining.clear();
        chaining.resize(currentTableSize);
        for (auto i : oldHash)
        {
            for (auto j : i)
            {
                insert(j.second, j.first);
            }
        }
    }

    long long getCollisions()
    {
        return collisions;
    }

    double getAverageProbes(long long num)
    {
        probes = 0;

        const int totalNumbers = num;
        const int percentage = 10;
        const int rangeStart = 0;
        const int rangeEnd = 9999;

        int numElements = totalNumbers * percentage / 100;

        mt19937 gen(SEED1);

        uniform_int_distribution<> dis(rangeStart, rangeEnd);
        unordered_map<int, int> mp;

        for (int i = 0; i < numElements; ++i)
        {
            int randomNumber = dis(gen);
            mp.insert({randomNumber, i});
        }

        while (mp.size() < numElements)
        {
            int randomNumber = dis(gen);
            mp.insert({randomNumber, -1});
        }

        for (auto it : mp)
        {
            search(v[it.first]);
        }

        return (double)probes / (1.0 * numElements);
    }

    long long getElements()
    {
        return elements;
    }

    double LoadFactor()
    {
        return (double)elements / currentTableSize;
    }

    void printHash()
    {
        if (hashType == CHAINING)
        {
            for (auto i : chaining)
            {
                for (auto j : i)
                {
                    cout << j.second << " ";
                }
                cout << endl;
            }
        }

        else if (hashType == DOUBLE)
        {
            for (auto i : doubleHash)
            {
                cout << i.second << " ";
            }
            cout << endl;
        }

        else if (hashType == CUSTOM)
        {
            for (auto i : customHash)
            {
                cout << i.second << " ";
            }
            cout << endl;
        }
    }
};

string randomWordGenerator()
{
    static long long counter = 0;
    srand(2000 + counter * counter);
    counter++;

    long long len = (rand() % (10 - 5 + 1)) + 5;

    long long wordSize = len;
    string word = "";

    for (long long i = 0; i < len; i++)
    {
        word += 'a' + (rand() % 26);
    }

    return word;
}