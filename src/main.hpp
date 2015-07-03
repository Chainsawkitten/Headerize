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

/// Write header.
/**
 * @param outFile File stream to write to.
 * @param inputName Input file name.
 */
void writeHeader(std::ofstream& outFile, const std::string& inputName);

/// Write data.
/**
 * @param outFile File stream to write to.
 */
void writeData(std::ofstream& outFile, const std::string& inputName, const char* fileContents, unsigned int fileLength);

/// Write footer.
/**
 * @param outFile File stream to write to.
 */
void writeFooter(std::ofstream& outFile);

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

/// Convert char to hex-string.
/**
 * @param character The char to convert.
 * @return Hex-string with the value of the char
 */
std::string charToHex(char character);

#endif
