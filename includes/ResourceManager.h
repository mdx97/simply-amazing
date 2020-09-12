#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <string>

namespace ResourceManager {
    std::string GetImagePath(const std::string &id);
    std::string GetAudioPath(const std::string &id);
};

#endif
