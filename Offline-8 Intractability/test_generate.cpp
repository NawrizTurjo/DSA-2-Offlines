#include <iostream>
#include <fstream>
#include <random>

int main()
{
    int n = 100;  // Number of items
    int W = 2200; // Maximum weight capacity

    std::random_device rd;
    std::mt19937 gen(rd());

    // Value range and weight range
    std::uniform_int_distribution<long long> val_dist(23012, 24035);
    std::uniform_int_distribution<long long> weight_dist(780, 880);

    std::ofstream outFile("test3.txt");
    if (!outFile.is_open())
    {
        std::cerr << "Unable to create file!" << std::endl;
        return 1;
    }

    // Write n and W to file
    outFile << n << std::endl;
    outFile << W << std::endl;

    // Generate and write n lines with random vi and wi values
    for (int i = 0; i < n; ++i)
    {
        int vi = val_dist(gen);
        int wi = weight_dist(gen);
        outFile << vi << " " << wi << std::endl;
    }

    outFile.close();
    std::cout << "Test case generated and saved to test_case.txt" << std::endl;

    return 0;
}