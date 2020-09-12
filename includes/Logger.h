#ifndef LOGGER_H
#define LOGGER_H

#include <string>

namespace Logger {
    void SetFile(const std::string &path);
    void Write(const std::string &message);
}

#endif
