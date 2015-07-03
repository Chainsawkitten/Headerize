#ifndef MAIN_HPP
#define MAIN_HPP

#include <fstream>

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
 */
void writeHeader(std::ofstream& outFile);

/// Write data.
/**
 * @param outFile File stream to write to.
 */
void writeData(std::ofstream& outFile);

/// Write footer.
/**
 * @param outFile File stream to write to.
 */
void writeFooter(std::ofstream& outFile);

#endif
