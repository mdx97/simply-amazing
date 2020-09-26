#include <fstream>
#include <sstream>
#include "Logger.h"
#include "ResourceManager.h"

std::string GetResourcePath(const std::string &id, const std::string &extension)
{
    std::ostringstream sstream;
    
    // @TODO: Make this configurable?
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

std::string ResourceManager::GetImagePath(const std::string &id)
{
    return GetResourcePath(id, "bmp");
}

std::string ResourceManager::GetAudioPath(const std::string &id)
{
    return GetResourcePath(id, "wav");
}
