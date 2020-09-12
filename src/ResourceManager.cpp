#include <fstream>
#include <sstream>
#include "Logger.h"
#include "ResourceManager.h"

// Helper function for resolving arbitrary resource paths.
std::string GetResourcePath(const std::string &id, const std::string &extension)
{
    std::ostringstream sstream;
    sstream << "resources/" << id << "." << extension;

    std::fstream fstream;
    fstream.open(sstream.str());

    if (fstream.fail()) {
        std::ostringstream logstream;
        logstream << "Error in ResourceManager::GetResource(): Cannot find file at path '" << sstream.str() << "'";
        Logger::Write(logstream.str());
        return "";
    }

    return sstream.str();
}

// Returns the path for an image resource.
std::string ResourceManager::GetImagePath(const std::string &id)
{
    return GetResourcePath(id, "bmp");
}

// Returns the path for an audio resource.
std::string ResourceManager::GetAudioPath(const std::string &id)
{
    return GetResourcePath(id, "wav");
}
