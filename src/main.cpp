#include "main.hpp"

#include <cstring>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, const char* argv[]) {
    // Print help
    if (argc == 1 || strcmp(argv[0], "--help") == 0) {
        cout << "Headerize is a tool to convert resource files to headers for inclusion in C/C++ projects." << endl
             << "Usage:" << endl
             << "Headerize input output" << endl;
        return 0;
    }
    
    // Get input and output names.
    string inputName = argv[1];
    string outputName;
    if (argc > 2)
        outputName = argv[2];
    else
        outputName = inputName + ".hzz";
    
    cout << inputName << " " << outputName;
    
    /// @todo: Read and write files
    
    return 0;
}
