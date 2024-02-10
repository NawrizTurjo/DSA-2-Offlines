#include <iostream>
#include <cstdlib> // For system function

int main() {
    // File paths to be compared
    const char* file1 = "out.txt";
    const char* file2 = "output.txt";

    // Command to compare files on Windows systems
    #ifdef _WIN32
        const char* cmd = "fc";
    #endif

    // Construct the command string
    std::string command = cmd;
    command += " ";
    command += file1;
    command += " ";
    command += file2;

    // Use system function to execute the command
    int result = system(command.c_str());

    // Check the result of the command
    if (result == 0) {
        std::cout << "Success: Files are identical." << std::endl;
    } else {
        std::cout << "Unsuccessful: Files are different." << std::endl;
    }

    return 0;
}
