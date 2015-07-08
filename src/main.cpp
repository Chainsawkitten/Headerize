#include "main.hpp"

#include <cstring>
#include <iostream>
#include <sstream>
#include <locale>

using namespace std;

int main(int argc, const char* argv[]) {
    // Print help
    if (argc == 1 || strcmp(argv[0], "--help") == 0) {
        cout << "Headerize is a tool to convert resource files to headers and source files for inclusion in C++ projects." << endl
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
        outputName = inputName;
    
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
    
    // Write header file.
    ofstream headerFile((outputName + ".hpp").c_str(), ios::trunc);
    if (headerFile.is_open()) {
        writeHeader(headerFile, inputName);
        
        headerFile.close();
    } else {
        cout << "Couldn't open " << outputName << " for writing." << endl;
    }
    
    // Write source file.
    ofstream sourceFile((outputName + ".cpp").c_str(), ios::trunc);
    if (sourceFile.is_open()) {
        writeSource(sourceFile, inputName, outputName, buffer, size);
        
        sourceFile.close();
    } else {
        cout << "Couldn't open " << outputName << " for writing." << endl;
    }
    
    return 0;
}

void writeHeader(ofstream& outFile, const string& inputName) {
    outFile << "#ifndef " << includeGuard(inputName) << endl
            << "#define " << includeGuard(inputName) << endl << endl;
    
    outFile << "extern const char " << variableName(inputName) << "[];" << endl;
    outFile << "extern const unsigned int " << variableName(inputName) << "_LENGTH;" << endl;
    
    outFile << endl << "#endif" << endl;
}

void writeSource(ofstream& outFile, const string& inputName, const string& outputName, const char* fileContents, unsigned int fileLength) {
    // Get base filename.
    std::size_t found = outputName.find_last_of("/\\");
    outFile << "#include \"" << outputName.substr(found+1) << ".hpp\"" << endl << endl;
    
    outFile << "const char " << variableName(inputName) << "[] = { ";
    
    for (unsigned int i=0; i<fileLength; i++) {
        outFile << +fileContents[i];
        if (i < fileLength-1)
            outFile << ", ";
    }
    
    outFile << " };" << endl
            << "const unsigned int " << variableName(inputName) << "_LENGTH = " << fileLength << ";" << endl;
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
    return variableName(inputName) + "_HPP";
}
