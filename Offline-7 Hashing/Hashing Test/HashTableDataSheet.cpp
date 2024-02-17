#include <bits/stdc++.h>
using namespace std;

#define CHAINING 1
#define DOUBLE 2
#define CUSTOM 3

#define DEFAULT_SIZE 10
#define DEFAULT_CHAIN 3

#define C1 32
#define C2 115

vector<string> v(20010);

class Hashing
{
    vector<list<pair<int, string>>> chaining;
    vector<pair<int, string>> doubleHash;
    vector<pair<int, string>> customHash;

    int currentTableSize;
    int probes;
    int collisions;
    int minTableSize;
    int elements;
    int maxChainLength;
    int order;
    int hashFunction;

    int hashType;
    int insertCount;
    int deleteCount;

    int hash1(string str)
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

    int hash2(const std::string &str)
    {
        unsigned int hash = 5381; // Initial value, chosen as a prime number
        for (char c : str)
        {
            hash = ((hash << 5) + hash) + c; // Bitwise left shift by 5 and add current character
        }
        return hash % currentTableSize;
    }

    // int hash2(const std::string &str)
    // {
    //     int hashValue = 0;
    //     int step = 3; // Choose an appropriate step size for folding
    //     int len = str.length();
    //     int chunks = len / step;
    //     for (int i = 0; i < chunks; ++i)
    //     {
    //         std::string chunk = str.substr(i * step, step);
    //         int foldedValue = 0;
    //         for (char c : chunk)
    //         {
    //             foldedValue += c; // Add ASCII value of each character in the chunk
    //         }
    //         hashValue += foldedValue;
    //     }
    //     // Handle remaining characters if string length is not divisible by step
    //     std::string remaining = str.substr(chunks * step);
    //     for (char c : remaining)
    //     {
    //         hashValue += c; // Add ASCII value of each character
    //     }
    //     return hashValue % currentTableSize; // Modulo to fit within table size
    // }

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

    int auxHash(string s)
    {
        int sum = 0;
        for (int i = 0; i < s.size(); i++)
        {
            sum += s[i];
        }

        return sum % currentTableSize;
    }

    int getHash(string s)
    {
        if (hashFunction == 1)
            return hash1(s);
        else
            return hash2(s);
    }

    int currMaxLength()
    {
        int max = 0;
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
    Hashing(int type, int hashFunction, int size = DEFAULT_SIZE, int maxChainLength = DEFAULT_CHAIN) : currentTableSize(nextPrime(size)), elements(0), maxChainLength(maxChainLength), probes(0), collisions(0), order(0), hashFunction(hashFunction), insertCount(0), deleteCount(0)
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
    }

    ~Hashing()
    {
        chaining.clear();
        doubleHash.clear();
        customHash.clear();
    }

    void insert(string s)
    {
        if (search(s))
        {
            return;
        }
        int index = getHash(s);
        insertCount++;
        if (chaining.size() > 0)
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

            ++order;

            chaining[index].push_front({order, s});
            elements++;
        }
        else if (doubleHash.size() > 0)
        {
            if (elements == currentTableSize)
            {
                cout << "Hash Table is Full" << endl;
                return;
            }
            if (search(s))
            {
                cout << "already exists" << endl;
                return;
            }

            bool isCollision = false;

            for (int i = 0; i < currentTableSize; i++)
            {
                index = (index + i * auxHash(s)) % currentTableSize;

                // if(index<0)
                // {
                //     index+=currentTableSize;
                //     index%=currentTableSize;
                // }

                if (doubleHash[index].second == "")
                {
                    ++order;
                    doubleHash[index].first = order;
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
            cout << "insertion failed---" << s << endl;
        }
        else if (customHash.size() > 0)
        {
            if (elements == currentTableSize)
            {
                cout << "Hash Table is Full" << endl;
                return;
            }
            if (search(s))
            {
                cout << "already exists" << endl;
                return;
            }
            bool isCollision = false;

            for (int i = 0; i < currentTableSize; i++)
            {
                index = (index + C1 * i * auxHash(s) + C2 * i * i) % currentTableSize;

                if (customHash[index].second == "")
                {
                    ++order;
                    customHash[index].first = order;
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
            cout << "insertion failed---" << s << endl;
        }
    }

    void Delete(string str)
    {
        if (search(str) == false)
        {
            return;
        }
        int index = getHash(str);
        if (chaining.size() > 0)
        {
            auto it = chaining[index].begin();
            while (it != chaining[index].end())
            {
                if (it->second == str)
                {
                    chaining[index].erase(it);
                    elements--;

                    if (elements / currentTableSize < 0.2 || currMaxLength() < maxChainLength * 0.8)
                    {
                        reHash(false);
                    }
                    return;
                }
                it++;
            }
            return;
        }
        else if (doubleHash.size() > 0)
        {
            for (int i = 0; i < currentTableSize; i++)
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
        else if (customHash.size() > 0)
        {
            for (int i = 0; i < currentTableSize; i++)
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
        int index = getHash(s);
        if (chaining.size() > 0)
        {
            list<pair<int, string>> currList = chaining[index];
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
        else if (doubleHash.size() > 0)
        {
            probes++;

            for (int i = 0; i < currentTableSize; i++)
            {
                index = (index + i * auxHash(s)) % currentTableSize;

                if (doubleHash[index].second == s)
                    return true;
                probes++;
            }
            // return true;
            return false;
        }
        else if (customHash.size() > 0)
        {
            probes++;

            for (int i = 0; i < currentTableSize; i++)
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

        int x = 0;
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
        // int oldCollisions = collisions;
        elements = 0; // as new Hash
        // collisions = 0; // as new Hash
        probes = 0; // as new Hash
        if (state)  // T means insertion reHash
            currentTableSize = nextPrime(currentTableSize * 2);
        else
            currentTableSize = nextPrime(currentTableSize / 2);

        vector<list<pair<int, string>>> oldHash = chaining;

        // hash.resize(0);
        chaining.clear();
        chaining.resize(currentTableSize);
        for (auto i : oldHash)
        {
            for (auto j : i)
            {
                // int index = stringToInt(j);
                // hash[index].push_front(j);
                insert(j.second);
            }
        }
        // collisions = oldCollisions;
    }

    int getCollisions()
    {
        return collisions;
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

    int getElements()
    {
        return elements;
    }

    double LoadFactor()
    {
        return (double)elements / currentTableSize;
    }

    void printHash()
    {
        if (chaining.size() > 0)
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

        else if (doubleHash.size() > 0)
        {
            for (auto i : doubleHash)
            {
                cout << i.second << " ";
            }
            cout << endl;
        }

        else if (customHash.size() > 0)
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
    static int counter = 0;          // Static variable to keep track of the number of calls
    srand(2000 + counter * counter); // Seed the random number generator with current time + counter
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
    // freopen("chaining_1.txt", "w", stdout);

    Hashing CH1(CHAINING, 1, 20000, 3);
    for (int i = 0; i < 20000; i++)
    {
        string s = randomWordGenerator();
        v[i] = s;
        CH1.insert(s);
    }
    cout << "Chiaining 1" << endl;
    cout << "Total Collisions: " << CH1.getCollisions() << endl;
    cout << "Average Probes From Main:  " << CH1.getAverageProbes(2000) << endl;
    cout << "Load Factor: " << CH1.LoadFactor() << endl;
    cout << "Total Elements: " << CH1.getElements() << endl;

    // fclose(stdout);
    // v.clear();
    // cout << v.size() << endl;

    // freopen("chaining_2.txt", "w", stdout);

    Hashing CH2(CHAINING, 2, 20000, 3);
    for (int i = 0; i < 20000; i++)
    {
        // string s = randomWordGenerator();
        // v[i] = s;
        CH2.insert(v[i]);
    }

    cout << "Chiaining 2" << endl;
    cout << "Total Collisions: " << CH2.getCollisions() << endl;
    cout << "Average Probes From Main:  " << CH2.getAverageProbes(2000) << endl;
    cout << "Load Factor: " << CH2.LoadFactor() << endl;
    cout << "Total Elements: " << CH2.getElements() << endl;

    // v.clear();
    // fclose(stdout);

    // freopen("double_1.txt", "w", stdout);

    Hashing D1(DOUBLE, 1, 20000, 3);
    for (int i = 0; i < 20000; i++)
    {
        // string s = randomWordGenerator();
        // v[i] = s;
        D1.insert(v[i]);
    }

    cout << "Double 1" << endl;
    cout << "Total Collisions: " << D1.getCollisions() << endl;
    cout << "Average Probes From Main:  " << D1.getAverageProbes(2000) << endl;
    cout << "Load Factor: " << D1.LoadFactor() << endl;
    cout << "Total Elements: " << D1.getElements() << endl;

    // v.clear();
    // fclose(stdout);

    // freopen("double_2.txt", "w", stdout);

    Hashing D2(DOUBLE, 2, 20000, 3);
    for (int i = 0; i < 20000; i++)
    {
        // string s = randomWordGenerator();
        // v[i] = s;
        D2.insert(v[i]);
    }

    cout << "Double 2" << endl;
    cout << "Total Collisions: " << D2.getCollisions() << endl;
    cout << "Average Probes From Main:  " << D2.getAverageProbes(2000) << endl;
    cout << "Load Factor: " << D2.LoadFactor() << endl;
    cout << "Total Elements: " << D2.getElements() << endl;

    // v.clear();
    // fclose(stdout);

    // freopen("custom_1.txt", "w", stdout);

    Hashing CUS1(CUSTOM, 1, 20000, 3);
    for (int i = 0; i < 20000; i++)
    {
        // string s = randomWordGenerator();
        // v[i] = s;
        CUS1.insert(v[i]);
    }

    cout << "Custom 1" << endl;
    cout << "Total Collisions: " << CUS1.getCollisions() << endl;
    cout << "Average Probes From Main:  " << CUS1.getAverageProbes(2000) << endl;
    cout << "Load Factor: " << CUS1.LoadFactor() << endl;
    cout << "Total Elements: " << CUS1.getElements() << endl;

    // v.clear();
    // fclose(stdout);

    // freopen("custom_2.txt", "w", stdout);

    Hashing CUS2(CUSTOM, 2, 20000, 3);
    for (int i = 0; i < 20000; i++)
    {
        // string s = randomWordGenerator();
        // v[i] = s;
        CUS2.insert(v[i]);
    }

    cout << "Custom 2" << endl;
    cout << "Total Collisions: " << CUS2.getCollisions() << endl;
    cout << "Average Probes From Main:  " << CUS2.getAverageProbes(2000) << endl;
    cout << "Load Factor: " << CUS2.LoadFactor() << endl;
    cout << "Total Elements: " << CUS2.getElements() << endl;

    // v.clear();
    // fclose(stdout);
}