#ifndef MAIN_HPP
#define MAIN_HPP

#include <fstream>
#include <string>

/// Main function.
/**
 * @param argc Argument count.
 * @param argv Argument values.
 * @return 0 on success
 */
int main(int argc, const char* argv[]);

/// Write header file.
/**
 * @param outFile File stream to write to.
 * @param inputName Input file name.
 */
void writeHeader(std::ofstream& outFile, const std::string& inputName);

/// Write source file.
/**
 * @param outFile File stream to write to.
 * @param inputName Input file name.
 * @param outputName Output file name.
 * @param fileContents Contents of the file.
 * @param fileLength Length of the file.
 */
void writeSource(std::ofstream& outFile, const std::string& inputName, const std::string& outputName, const char* fileContents, unsigned int fileLength);

/// Get variable name.
/**
 * @param inputName Input file name.
 * @return The variable name
 */
std::string variableName(std::string inputName);

/// Get include guard name.
/**
 * @param inputName Input file name.
 * @return The include guard name for the file
 */
std::string includeGuard(std::string inputName);

#endif
