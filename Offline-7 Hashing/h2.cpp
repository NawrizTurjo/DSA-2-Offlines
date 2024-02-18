#include<bits/stdc++.h>
using namespace std;

int main() {
    const int totalNumbers = 10000;
    const int percentage = 10;
    const int rangeStart = 1;
    const int rangeEnd = 10000;
    
    int numElements = totalNumbers * percentage / 100;
    long seed = 2105032;
    mt19937 gen(seed);
    
    uniform_int_distribution<> dis(rangeStart, rangeEnd);
    unordered_map<int, int> mp;
    
    for (int i = 0; i < numElements; ++i) {
        int randomNumber = dis(gen);
        mp.insert({randomNumber, i});
    }
    cout << "Size of the map: " << mp.size() << endl;

    while(mp.size()<numElements){
        int randomNumber = dis(gen);
        mp.insert({randomNumber, -1});
    }
    cout << "Size of the map: " << mp.size() << endl;

    for(auto it : mp)
    {
        cout << it.first << " " << endl;
    }
    return 0;
}
