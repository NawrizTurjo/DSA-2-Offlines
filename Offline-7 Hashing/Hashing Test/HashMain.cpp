#include <bits/stdc++.h>
#include "HashTableDataSheet.cpp"
using namespace std;

int main()
{

    long long totalNumbers = 10000;
    for (int i = 0; i < totalNumbers; i++)
    {
        v[i] = randomWordGenerator();
    }

    Hashing H(CHAINING, 1, 10000, 3);

    long long tableSize[3] = {5000, 10000, 20000};
    int collisionRes[3] = {CHAINING, DOUBLE, CUSTOM};


    freopen("output.txt", "w", stdout);

    for (int i = 0; i < 3; i++)
    {
        cout<<endl<<"Table Size: "<<tableSize[i]<<endl<<endl;
        for (int j = 1; j <= 2; j++)
        {
            for (int m = 0; m < 3; m++)
            {
                H.reInitialize(collisionRes[m], j, tableSize[i], 3);
                for (int k = 0; k < totalNumbers; k++)
                {
                    H.insert(v[k], k + 1);
                }
                switch (collisionRes[m])
                {
                case CHAINING:
                    cout << "Separate Chaining (function "<<j<<")" << endl;
                    break;
                case DOUBLE:
                    cout << "Double Hashing (function "<<j<<")" << endl;
                    break;
                case CUSTOM:
                    cout << "Custom Hashing (function "<<j<<")" << endl;
                    break;
                default:
                    break;
                }
                // cout << "Chiaining 1" << endl;
                cout << "Total Collisions: " << H.getCollisions() << endl;
                cout << "Average Probes From Main:  " << H.getAverageProbes(totalNumbers) << endl;
                cout << "Load Factor: " << H.LoadFactor() << endl;
                cout << "Total Elements: " << H.getElements() << endl;
                H.clear();
            }
        }
    }

    fclose(stdout);
}