#include <bits/stdc++.h>
using namespace std;
#include "HashTableDataSheet.cpp"

int main()
{
    long long totalNumbers = 10000;
    int max_chain = 5;
    for (int i = 0; i < totalNumbers; i++)
    {
        v[i] = randomWordGenerator();
    }
    // cout << 1 << endl;

    // freopen("out.txt","w",stdout);

    Hashing H(CHAINING, 1, totalNumbers * 2, max_chain);

    // for (int i = 0; i < totalNumbers; i++)
    // {
    //     H.insert(v[i], i + 1);
    // }
    // cout << H.getCollisions() << " " << H.getAverageProbes(totalNumbers) << " " << H.getElements() << endl;

    // for (int i = 0; i < totalNumbers / 2; i++)
    // {
    //     // cout << i + 1 << endl;
    //     H.Delete(v[i]);
    // }

    // cout << H.getCollisions() << " " << H.getAverageProbes(totalNumbers) << " " << H.getElements() << endl;

    long long tableSize[3] = {5000, 10000, 20000};
    bool tableSizeFlag[3] = {false};
    int collisionRes[3] = {CHAINING, DOUBLE, CUSTOM};

    freopen("report.txt", "w", stdout);

    cout << "C1 => " << C1 << "\tC2 => " << C2 << endl;
    cout << "Current Seed for Average probes count => " << SEED1 << endl;
    cout << "Maximum Chain length => " << max_chain << endl;

    cout << " ________________________________________________________________________________ " << endl;
    cout << "| Hash       | Collision         | Hash Function 1       | Hash Function 2       |" << endl;
    cout << "| Table      | Resolution        | # of      | Average   | # of      | Average   |" << endl;
    cout << "| Size       | Method            | Collisions| Probes    | Collisions| Probes    |" << endl;
    cout << "|________________________________________________________________________________|" << endl;
    bool flag = false;
    for (int i = 0; i < 3; i++)
    {
        for (int m = 0; m < 3; m++)
        {
            H.reInitialize(collisionRes[m], 1, tableSize[i], max_chain);
            for (int k = 0; k < totalNumbers; k++)
            {
                H.insert(v[k], k + 1);
            }
            if (tableSizeFlag[i] == false)
            {
                cout << "| N = " << setw(7) << left << tableSize[i];
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

            cout << " |  " << setw(9) << left << H.getCollisions() << "| " << setw(6) << left << H.getAverageProbes(totalNumbers) << "   ";
            H.reInitialize(collisionRes[m], 2, tableSize[i], 3);
            for (int k = 0; k < totalNumbers; k++)
            {
                H.insert(v[k], k + 1);
            }

            // cout << " |  " << setw(5) << H.getCollisions() << "   " << setw(6) << H.getAverageProbes(totalNumbers) << "  |";
            cout << " |  " << setw(9) << left << H.getCollisions() << "| " << setw(8) << left << H.getAverageProbes(totalNumbers) << "  |";

            cout << endl;

            H.clear();
        }
        cout << "|________________________________________________________________________________|" << endl;
    }

    fclose(stdout);
}
