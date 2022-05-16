//
// Created by Patrick Tumulty on 5/15/22.
//

#include <iostream>
#include "HeaderFileBuilder.h"
#include "StringUtils.h"
#include "FileUtils.h"
#include "Logger.h"
#include <queue>
#include "cmake-build-debug/text_data_header.h"

void printHelpExample();
void processInputFileArguments(std::queue<std::string> &inputQueue, HeaderFileBuilder &writer);

/**
 * Main
 *
 * @param argc argc
 * @param argv argv
 * @return 0 if successful execution
 */
int main(int argc, char *argv[])
{
    if (argc == 1 || std::string(argv[1]) == "--help") {
        printHelpExample();
        return 0;
    }

    std::queue<std::string> inputQueue;
    for (int i = 0; i < argc; i++)
    {
        inputQueue.push(argv[i]);
    }

    inputQueue.pop(); // remove binary name
    std::string outputFilename = inputQueue.front();
    inputQueue.pop();

    HeaderFileBuilder headerBuilder(outputFilename);
    headerBuilder.appendLine();
    headerBuilder.addInclude("cstdint");
    headerBuilder.appendLine();

    if (inputQueue.size() % 2 != 0)
    {
        std::cout << "Invalid number of arguments" << std::endl;
        return -1;
    }

    processInputFileArguments(inputQueue, headerBuilder);

    headerBuilder.endFile();

    FileUtils::writeStringToFile(headerBuilder.getHeaderFileName(), headerBuilder.getFileContents());

    return 0;
}

/**
 * Process the input file arguments.
 *
 * Process each file and add it to the output header file
 *
 * @param[in] inputQueue argument input queue
 * @param[in] writer header file writer
 */
void processInputFileArguments(std::queue<std::string> &inputQueue, HeaderFileBuilder &writer)
{
    for (int i = 0; i < inputQueue.size(); i++)
    {
        std::string varName = inputQueue.front();
        inputQueue.pop();
        std::string filepath = inputQueue.front();
        inputQueue.pop();

        try
        {
            std::ifstream fileReader(filepath, std::ios::binary);
            unsigned long len = std::filesystem::file_size(filepath);
            char data[len];

            Logger::get().consoleLog("Reading... " + filepath + " : " + std::to_string(len) + " bytes");

            fileReader.read(data, (long) len);
            writer.appendLine();
            writer.writeULongVar(varName + "_length", len);
            writer.writeArray(varName, reinterpret_cast<uint8_t *>(data), len);
            fileReader.close();
        }
        catch (const std::exception& ex)
        {
            Logger::get().logError("Error processing file: " + std::string(ex.what()));
        }
    }
}

/**
 * Print help and example info about this program
 */
void printHelpExample()
{
    std::string example =
            "Resource Header Compiler (rhc)\n\n"
            "\tThe resource header compiler is a simple command line tool used for parsing byte information from\n"
            "\tvarious files into header file defined byte arrays. The resulting header file can then be included\n"
            "\tin any C or C++ project.\n\n"
            "Input Arguments:\n"
            "\t$ rhc <output-filename> [<var-name> <file-path>, ...]\n\n"
            "\toutput-filename               : The name of the output header file.\n"
            "\t[<var-name> <file-path>, ...] : space separated list. The <var-name> is the name that the resulting\n"
            "\t                                byte array will be saved as in the resulting header file. The\n"
            "\t                                <file-path> is the path to read the byte data from.\n"
            "Example:\n"
            "\t$ rhc data_header.h students students.txt picture1 pic.png\n";
    std::cout << example << std::endl;
}
