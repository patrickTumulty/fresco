//
// Created by Patrick Tumulty on 5/15/22.
//

#include "FileUtils.h"
#include "Logger.h"
#include "ArgProcessor.h"
#include "InputProcessor.h"
#include "FileResourceCompiler.h"

#include <queue>
#include <filesystem>
#include <map>


static std::string outputFilename;
static std::string outputDirectory;
static std::map<std::string, std::string> dataItems;

void printVersion();
int verifyInputs();
const char *getHelperHeaderString();
const char *getHelperFooterString();

std::vector<ArgProcessor> getArgProcessors()
{
    std::vector<ArgProcessor> processors;

    processors.emplace_back("--version",
                            "",
                            "Print fresco version",
                            ARG_PROCESSOR_FLAG,
                            [](const std::vector<std::string>& values)
    {
        printVersion();
        return 0;
    });

    processors.emplace_back("--name",
                            "-n",
                            "Name for the generated .h and .cpp files",
                            1,
                            [](const std::vector<std::string>& values)
    {
        outputFilename = values[0];
        return 0;
    });

    processors.emplace_back("--dir",
                            "-d",
                            "Output directory",
                            1,
                            [](const std::vector<std::string>& values)
    {
        outputDirectory = values[0];

        if (!std::filesystem::exists(outputDirectory))
        {
            Logger::get().consoleLog("Could not access " + outputDirectory);
            return -1;
        }

        return 0;
    });

    processors.emplace_back("--files",
                            "-f",
                            "Input files. This command takes an arbitrary length of space separated pairs. Each pair "
                            "should comprise of a name (left) and a file path (right). See 'Usage' above.",
                            ARG_PROCESSOR_FINAL,
                            [](const std::vector<std::string>& values)
    {
        if (values.size() % 2 != 0)
        {
            Logger::get().consoleLog("Invalid number of arguments");
            return -1;
        }

        for (int i = 0; i < values.size(); i+= 2)
        {
            dataItems.insert({ values[i], values[i + 1] });
        }

        return 0;
    });

    return processors;
}

/**
 * Verify that all necessary inputs have been provided
 *
 * @return 0 if inputs are valid, else -1
 */
int verifyInputs()
{
    if (outputFilename.empty())
    {
        Logger::get().consoleLog("Exiting... No output filename defined");
        return -1;
    }
    else if (outputDirectory.empty())
    {
        Logger::get().consoleLog("Exiting... No output directory specified");
        return -1;
    }
    else if (dataItems.empty())
    {
        Logger::get().consoleLog("Exiting... No files provided");
        return -1;
    }

    return 0;
}

/**
 * Print rhc version
 */
void printVersion()
{
    printf("File Resource Compiler (fresco) %s", FileResourceCompiler::getVersionString().c_str());

    exit(0);
}

/**
 * Main
 *
 * @param argc argc
 * @param argv argv
 * @return 0 if successful execution
 */
int main(int argc, char *argv[])
{
    InputProcessor inputProcessor(getArgProcessors());

    inputProcessor.addDefaultHelpArgProcessor();
    inputProcessor.setHelperHeader(getHelperHeaderString());
    inputProcessor.setHelperFooter(getHelperFooterString());
    inputProcessor.processInputs(argc, argv);

    if (verifyInputs() != 0)
    {
        return -1;
    }

    FileResourceCompiler compiler(outputFilename, dataItems);

    compiler.compile();

    compiler.writeGeneratedResourceFiles(outputDirectory);

    return 0;
}

const char *getHelperFooterString()
{
    return "\n \n"
           "Version  : v1.00.00\n"
           "GitHub   : https://github.com/patrickTumulty/fresco\n";
}

const char *getHelperHeaderString()
{
    return "  ____  ___   ____  __   __   ___ \n"
           " | |_  | |_) | |_  ( (` / /` / / \\\n"
           " |_|   |_| \\ |_|__ _)_) \\_\\_ \\_\\_/\n"
           "\n \n"
           "The file resource compiler (fresco) is a simple command line tool used for parsing "
           "resource files into c++ source file defined byte arrays. Fresco generates one "
           "source(.cpp) file and one header(.h) file. These generated files can then be included "
           "in any c++ project. This program aims to be a simple solution for compiling static"
           " resources into a c++ executable.\n \n"
           "Usage:\n"
           "\t$ fresco -n resource -d . -f file1 file.txt file2 file2.txt\n \n"
           "Options:";
}
