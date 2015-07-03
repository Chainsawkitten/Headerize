#include "main.hpp"

#include <cstring>
#include <iostream>
#include <locale>

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
    
    // Read input file.
    ifstream inFile(inputName.c_str(), ios::binary);
    char* buffer;
    int size;
    if (inFile.is_open()) {
        size = inFile.tellg();
        buffer = new char[size];
        inFile.seekg(0, ios::beg);
        inFile.read(buffer, size);
        
        inFile.close();
    } else {
        cout << "Couldn't open " << inputName << "." << endl;
        return 1;
    }
    
    // Write output file.
    ofstream outFile(outputName.c_str(), ios::trunc);
    if (outFile.is_open()) {
        writeHeader(outFile, inputName);
        writeData(outFile);
        writeFooter(outFile);
        
        outFile.close();
    } else {
        cout << "Couldn't open " << outputName << " for writing." << endl;
    }
    
    return 0;
}

void writeHeader(ofstream& outFile, const string& inputName) {
    outFile << "#ifndef " << includeGuard(inputName) << endl
            << "#define " << includeGuard(inputName) << endl << endl;
}

void writeData(ofstream& outFile) {
    /// @todo: Write data
}

void writeFooter(ofstream& outFile) {
    outFile << endl << "#endif" << endl;
}

string includeGuard(string inputName) {
    // Convert to upper case and replace . with _.
    for (string::size_type i=0; i<inputName.length(); i++) {
        inputName[i] = toupper(inputName[i]);
        if (inputName[i] == '.')
            inputName[i] = '_';
    }
    
    return inputName + "_HZZ";
}
