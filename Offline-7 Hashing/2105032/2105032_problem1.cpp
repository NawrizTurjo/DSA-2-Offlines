#include <bits/stdc++.h>
using namespace std;
#include "HashTableDataSheet.cpp"

int main()
{
    long long totalNumbers = 10000;
    for (int i = 0; i < totalNumbers; i++)
    {
        v[i] = randomWordGenerator();
    }

    Hashing H(CHAINING, 1, 10000, 3);

    long long tableSize[3] = {5000, 10000, 20000};
    bool tableSizeFlag[3] = {false};
    int collisionRes[3] = {CHAINING, DOUBLE, CUSTOM};

    freopen("output.txt", "w", stdout);

    cout << " ________________________________________________________________________________ " << endl;
    cout << "| Hash       | Collision         | Hash Function 1       | Hash Function 2       |" << endl;
    cout << "| Table Size | Resolution Method | Colls.    | Probes    | Colls.    | Probes    |" << endl;
    cout << "|________________________________________________________________________________|" << endl;
    bool flag = false;
    for (int i = 0; i < 3; i++)
    {
        for (int m = 0; m < 3; m++)
        {
            H.reInitialize(collisionRes[m], 1, tableSize[i], 3);
            for (int k = 0; k < totalNumbers; k++)
            {
                H.insert(v[k], k + 1);
            }
            if (tableSizeFlag[i] == false)
            {
                cout << "| N = " << tableSize[i] << "   ";
                tableSizeFlag[i] = true;
            }
            else
            {
                cout << "|            ";
            }

            switch (collisionRes[m])
            {
            case CHAINING:
                cout << "| Separate Chaining";
                break;
            case DOUBLE:
                cout << "| Double Hashing   ";
                break;
            case CUSTOM:
                cout << "| Custom Probing   ";
                break;
            default:
                break;
            }

            cout << " |  " << setw(5) << H.getCollisions() << "   " << setw(6) << H.getAverageProbes(totalNumbers) << "   ";
            H.reInitialize(collisionRes[m], 2, tableSize[i], 3);
            for (int k = 0; k < totalNumbers; k++)
            {
                H.insert(v[k], k + 1);
            }



            cout << " |  " << setw(5) << H.getCollisions() << "   " << setw(6) << H.getAverageProbes(totalNumbers) << "  |";

            cout << endl;

            H.clear();
        }
        cout << "|_______________________________________________________________________________|" << endl;
    }

    fclose(stdout);
}
