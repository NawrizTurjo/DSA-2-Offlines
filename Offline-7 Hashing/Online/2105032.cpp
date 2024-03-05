#include <bits/stdc++.h>
using namespace std;
#include "HashTableDataSheet.cpp"

string manipulate(string instr)
{
    string str = instr;
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] == 'A')
        {
            str[i] = 'T';
        }
        else if (str[i] == 'T')
        {
            str[i] = 'A';
        }
        else if (str[i] == 'G')
        {
            str[i] = 'C';
        }
        else if (str[i] == 'C')
        {
            str[i] = 'G';
        }
    }

    for (int i = 0; i < str.length() / 2; i++)
    {
        char c = str[i];
        str[i] = str[str.length() - i - 1];
        str[str.length() - i - 1] = c;
    }

    return str;
}

int main()
{
    Hashing H(CHAINING, 1, 1000, 3);

    // string str = "ATGC";
    // cout << str << "  =>  " << manipulate(str) << endl;

    vector<string> lists;
    int items, size;
    cin >> items >> size;
    int order = 1;

    string temp;
    for (int i = 0; i < items; i++)
    {
        cin >> temp;
        lists.push_back(temp);
    }
    cout << endl
         << endl;
    for (auto i : lists)
    {
        string manipstr = manipulate(i);
        if (H.search(manipstr))
            cout << manipstr << "  " << i << endl;
        else
        {
            H.insert(i, order);
            order++;
        }
    }
}
/*
5 4
ATGC
GCAT
TACG
CGTA
TTAA

4 5
TTAAG
AATTC
CTTAA
CTTAA

*/