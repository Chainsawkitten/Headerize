#include "main.hpp"

#include <cstring>
#include <iostream>
#include <sstream>
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
    ifstream inFile(inputName.c_str(), ios::binary | ios::ate);
    char* buffer;
    unsigned int size;
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
        writeData(outFile, inputName, buffer, size);
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

void writeData(ofstream& outFile, const string& inputName, const char* fileContents, unsigned int fileLength) {
    outFile << "const char " << variableName(inputName) << "[] = { ";
    
    for (unsigned int i=0; i<fileLength; i++) {
        outFile << charToHex(fileContents[i]);
        if (i < fileLength-1)
            outFile << ", ";
    }
    
    outFile << " };" << endl
            << "const unsigned int " << variableName(inputName) << "_LENGTH = " << fileLength << ";" << endl;
}

void writeFooter(ofstream& outFile) {
    outFile << endl << "#endif" << endl;
}

string variableName(string inputName) {
    // Get base filename.
    std::size_t found = inputName.find_last_of("/\\");
    inputName = inputName.substr(found+1);
    
    // Convert to upper case and replace . with _.
    for (string::size_type i=0; i<inputName.length(); i++) {
        inputName[i] = toupper(inputName[i]);
        if (inputName[i] == '.')
            inputName[i] = '_';
    }
    
    return inputName;
}

string includeGuard(string inputName) {
    return variableName(inputName) + "_HZZ";
}

string charToHex(char character) {
    string result = "0x";
    ostringstream convert;
    convert << std::hex << static_cast<int>(character);
    return result + convert.str();
}
