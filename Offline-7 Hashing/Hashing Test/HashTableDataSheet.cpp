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
        // cout<<hashVal<<endl;
        if (hashVal < 0)
        {
            hashVal += currentTableSize;
        }

        return hashVal;
    }

    long long hash2(const string &str)
    {
        unsigned long long hash = 5381; // Initial value, chosen as a prime number
        for (char c : str)
        {
            hash = ((hash << 5) + hash) + c; // Bitwise left shift by 5 and add current character
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
            chaining.assign(currentTableSize, list<pair<long long, string>>()); // Resetting elements to empty lists
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
        // cout << load;
        if (elements >= currentTableSize)
        {
            // cout << "Hash Table is Full" << endl;
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
            // if()
            if (insertCount == 100 && chaining[index].size() >= maxChainLength
                // || elements / currentTableSize > 0.2
                // || probes / (0.1 * currentTableSize) > 2
                || currentTableSize > 100 && probes / (0.1 * currentTableSize) > 2)
            {
                insertCount = 0;
                reHash(true);
                index = getHash(s);
            }

            if (chaining[index].size() != 0)
            {
                collisions++;
            }

            // ++order;

            chaining[index].push_front({key, s});
            elements++;
        }
        else if (hashType == DOUBLE)
        {
            // if (elements >= currentTableSize)
            // {
            //     cout << "Hash Table is Full" << endl;
            //     return;
            // }

            // if (search(s))
            // {
            //     cout << "already exists" << endl;
            //     return;
            // }

            bool isCollision = false;
            long long prev = collisions;

            for (long long i = 0; i < currentTableSize; i++)
            {
                index = (index + i * auxHash(s)) % currentTableSize;

                // if(index<0)
                // {
                //     index+=currentTableSize;
                //     index%=currentTableSize;
                // }

                // if (doubleHash[index].second == "")
                if (isElement[index] == false)
                {
                    // ++order;
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
            // cout << "insertion failed---" << s << endl;
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

                // cout << index << endl;

                if (index < 0 || index >= currentTableSize)
                {
                    // cout << "index Error" << endl;
                    return;
                }

                if (isElement[index] == false)
                {
                    // ++order;
                    isElement[index] = true;
                    customHash[index].first = key;
                    customHash[index].second = s;
                    elements++;
                    // cout << endl;
                    return;
                }
                if (!isCollision)
                {
                    collisions++;
                    isCollision = true;
                }
            }
            // cout << "insertion failed---" << s << endl;
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
                // collisions++;
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
                // collisions++;
            }
        }
    }

    bool search(string s)
    {
        long long index = getHash(s);
        if (hashType == CHAINING)
        {
            list<pair<long long, string>> currList = chaining[index];
            // cout << currList.size() << endl;
            if (currList.size() == 0)
                return false; // search failed

            // cout << "search2" << endl;
            probes++;
            for (auto i : currList)
            {
                if (i.second == s)
                {
                    return true;
                }
                probes++;
            }
            return false; // search failed
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
            // return true;
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
            // return true;
            return false;
        }
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
        // long long oldCollisions = collisions;
        elements = 0; // as new Hash
        // collisions = 0; // as new Hash
        probes = 0; // as new Hash
        if (state)  // T means insertion reHash
            currentTableSize = nextPrime(currentTableSize * 2);
        else
            currentTableSize = nextPrime(currentTableSize / 2);

        vector<list<pair<long long, string>>> oldHash = chaining;

        // hash.resize(0);
        chaining.clear();
        chaining.resize(currentTableSize);
        for (auto i : oldHash)
        {
            for (auto j : i)
            {
                // long long index = stringTolong long(j);
                // hash[index].push_front(j);
                insert(j.second, j.first);
            }
        }
        // collisions = oldCollisions;
    }

    long long getCollisions()
    {
        return collisions;
    }

    double getAverageProbes(long long num)
    {
        // num = elements;
        probes = 0;
        // for (long long i = 0; i < num; i++)
        // {
        //     search(v[i]);
        // }

        // cout << "probes -> " << probes << endl;

        const int totalNumbers = num;
        const int percentage = 10;
        const int rangeStart = 0;
        const int rangeEnd = 9999;

        int numElements = totalNumbers * percentage / 100;
        // long seed = 2105032;

        mt19937 gen(SEED1);

        uniform_int_distribution<> dis(rangeStart, rangeEnd);
        unordered_map<int, int> mp;

        for (int i = 0; i < numElements; ++i)
        {
            int randomNumber = dis(gen);
            mp.insert({randomNumber, i});
        }
        // cout << "Size of the map: " << mp.size() << endl;

        while (mp.size() < numElements)
        {
            int randomNumber = dis(gen);
            mp.insert({randomNumber, -1});
        }
        // cout << "Size of the map: " << mp.size() << endl;

        for (auto it : mp)
        {
            // cout << it.first << " " << endl;
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
    // srand(time(0));
    static long long counter = 0;    // Static variable to keep track of the number of calls
    srand(2000 + counter * counter); // Seed the random number generator with current time + counter
    counter++;                       // Increment the counter for the next call

    long long len = (rand() % (10 - 5 + 1)) + 5;
    // cout << len << endl;

    long long wordSize = len;
    string word = "";

    for (long long i = 0; i < len; i++)
    {
        word += 'a' + (rand() % 26);
    }

    // cout << word << endl;

    return word;
}
/*
int main()
{
    long long size = 10000;

    long long tableSize = 20000;
    // then 10000 and 20000

    long long probeCnt = 1000;

    // ofstream file;
    // file.open("out.txt",ios::app);

    for (long long i = 0; i < size; i++)
    {
        v[i] = randomWordGenerator();
    }
    // unordered_map<string, long long> mp;

    // for(long long i=0;i<10000;i++)
    // {
    //     mp.insert({v[i],i+1});
    // }

    // cout<<mp.size()<<endl;
    // freopen("chaining_1.txt", "w", stdout);

    Hashing CH1(CHAINING, 1, tableSize, 3);
    for (long long i = 0; i < size; i++)
    {
        CH1.insert(v[i], i + 1);
    }
    cout << "Chiaining 1" << endl;
    cout << "Total Collisions: " << CH1.getCollisions() << endl;
    cout << "Average Probes From Main:  " << CH1.getAverageProbes(probeCnt) << endl;
    cout << "Load Factor: " << CH1.LoadFactor() << endl;
    cout << "Total Elements: " << CH1.getElements() << endl;

    CH1.reInitialize(DOUBLE, 1, tableSize, 3);

    for (long long i = 0; i < size; i++)
    {
        CH1.insert(v[i], i + 1);
    }
    cout << "Double 1" << endl;
    cout << "Total Collisions: " << CH1.getCollisions() << endl;
    cout << "Average Probes From Main:  " << CH1.getAverageProbes(probeCnt) << endl;
    cout << "Load Factor: " << CH1.LoadFactor() << endl;
    cout << "Total Elements: " << CH1.getElements() << endl;

    CH1.reInitialize(CUSTOM, 1, tableSize, 3);

    for (long long i = 0; i < size; i++)
    {
        CH1.insert(v[i], i + 1);
    }
    cout << "Custom 1" << endl;
    cout << "Total Collisions: " << CH1.getCollisions() << endl;
    cout << "Average Probes From Main:  " << CH1.getAverageProbes(probeCnt) << endl;
    cout << "Load Factor: " << CH1.LoadFactor() << endl;
    cout << "Total Elements: " << CH1.getElements() << endl;

    // fclose(stdout);
    // v.clear();
    // cout << v.size() << endl;

    // freopen("chaining_2.txt", "w", stdout);

    // Hashing CH2(CHAINING, 2, tableSize, 3);
    // for (long long i = 0; i < size; i++)
    // {
    //     CH2.insert(v[i], i + 1);
    // }

    // cout << "Chiaining 2" << endl;
    // cout << "Total Collisions: " << CH2.getCollisions() << endl;
    // cout << "Average Probes From Main:  " << CH2.getAverageProbes(probeCnt) << endl;
    // cout << "Load Factor: " << CH2.LoadFactor() << endl;
    // cout << "Total Elements: " << CH2.getElements() << endl;
    // CH2.clear();

    // // v.clear();
    // // fclose(stdout);

    // // freopen("double_1.txt", "w", stdout);

    // Hashing D1(DOUBLE, 1, tableSize, 3);
    // for (long long i = 0; i < size; i++)
    // {
    //     // string s = randomWordGenerator();
    //     // v[i] = s;
    //     D1.insert(v[i], i + 1);
    // }

    // cout << "Double 1" << endl;
    // cout << "Total Collisions: " << D1.getCollisions() << endl;
    // cout << "Average Probes From Main:  " << D1.getAverageProbes(probeCnt) << endl;
    // cout << "Load Factor: " << D1.LoadFactor() << endl;
    // cout << "Total Elements: " << D1.getElements() << endl;
    // D1.clear();

    // // // // v.clear();
    // // // fclose(stdout);

    // // // freopen("double_2.txt", "w", stdout);

    // Hashing D2(DOUBLE, 2, tableSize, 3);
    // for (long long i = 0; i < size; i++)
    // {
    //     // string s = randomWordGenerator();
    //     // v[i] = s;
    //     D2.insert(v[i], i + 1);
    // }

    // cout << "Double 2" << endl;
    // cout << "Total Collisions: " << D2.getCollisions() << endl;
    // cout << "Average Probes From Main:  " << D2.getAverageProbes(probeCnt) << endl;
    // cout << "Load Factor: " << D2.LoadFactor() << endl;
    // cout << "Total Elements: " << D2.getElements() << endl;
    // D2.clear();

    // // v.clear();
    // // fclose(stdout);

    // // freopen("custom_1.txt", "w", stdout);

    // Hashing CUS1(CUSTOM, 1, tableSize, 3);
    // for (long long i = 0; i < size; i++)
    // {
    //     // string s = randomWordGenerator();
    //     // v[i] = s;
    //     CUS1.insert(v[i], i + 1);
    // }

    // cout << "Custom 1" << endl;
    // cout << "Total Collisions: " << CUS1.getCollisions() << endl;
    // cout << "Average Probes From Main:  " << CUS1.getAverageProbes(probeCnt) << endl;
    // cout << "Load Factor: " << CUS1.LoadFactor() << endl;
    // cout << "Total Elements: " << CUS1.getElements() << endl;
    // CUS1.clear();

    // // v.clear();
    // // fclose(stdout);

    // // freopen("custom_2.txt", "w", stdout);

    // Hashing CUS2(CUSTOM, 2, tableSize, 3);
    // for (long long i = 0; i < size; i++)
    // {
    //     // string s = randomWordGenerator();
    //     // v[i] = s;
    //     CUS2.insert(v[i], i + 1);
    //     // cout << i << endl;
    // }

    // cout << "Custom 2" << endl;
    // cout << "Total Collisions: " << CUS2.getCollisions() << endl;
    // cout << "Average Probes From Main:  " << CUS2.getAverageProbes(probeCnt) << endl;
    // cout << "Load Factor: " << CUS2.LoadFactor() << endl;
    // cout << "Total Elements: " << CUS2.getElements() << endl;
    // CUS2.clear();

    // // v.clear();
    // // fclose(stdout);

    // long long totalNumbers = 10000;
    // for (int i = 0; i < totalNumbers; i++)
    // {
    //     v[i] = randomWordGenerator();
    // }

    // Hashing H(CHAINING, 1, 10000, 3);

    // long long tableSize[3] = {5000, 10000, 20000};
    // int collisionRes[3] = {CHAINING,DOUBLE,CUSTOM};

    // freopen("output.txt", "w", stdout);

    // for (int i = 0; i < 3; i++)
    // {
    //     for (int j = 1; j <= 2; j++)
    //     {
    //         H.reInitialize(collisionRes[i], j, tableSize[i], 3);
    //         for (int k = 0; k < totalNumbers; k++)
    //         {
    //             H.insert(v[k], k + 1);
    //         }
    //         // cout << "Chiaining 1" << endl;
    //         cout << "Total Collisions: " << H.getCollisions() << endl;
    //         cout << "Average Probes From Main:  " << H.getAverageProbes(totalNumbers) << endl;
    //         cout << "Load Factor: " << H.LoadFactor() << endl;
    //         cout << "Total Elements: " << H.getElements() << endl;
    //     }
    // }

    // fclose(stdout);
}
*/