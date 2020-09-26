#include "Logger.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <sstream>

std::fstream file;
bool usable = false;

void Logger::SetFile(const std::string &path)
{
    file.open(path.c_str(), std::ios::out);
    usable = file.is_open();
}

void Logger::Write(const std::string &message)
{
    if (!usable) {
        std::cout << "Attempted to write to logger in unusable state!" << std::endl;
        exit(1);
    }

    file << message << std::endl;
}
