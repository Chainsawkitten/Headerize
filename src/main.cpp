#include "main.hpp"

#include <cstring>
#include <iostream>

using namespace std;

int main(int argc, const char* argv[]) {
    // Print help
    if (argc == 0 || strcmp(argv[0], "--help")) {
        cout << "Headerize is a tool to convert resource files to headers for inclusion in C/C++ projects." << endl
             << "Usage:" << endl
             << "Headerize input output" << endl;
        return 0;
    }
    
    /// @todo: Actual usage
    
    return 0;
}
