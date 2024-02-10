#include "ResourceManager.h"

#include "Logger.h"

std::map<std::string, sf::Image*> ResourceManager::Images;
std::map<std::string, Animation*> ResourceManager::Animations;

void ResourceManager::loadImage(const std::string& name, const std::string& filepath)
{
    // Test if the key exists
    if(Images.find(name) == Images.end())
    {
        Images[name] = new sf::Image();
        if(!Images[name]->LoadFromFile(filepath))
            Logger::log("Error Loading Image: " + name + " at filepath: " + filepath, LOGTYPE_ERROR);
        else
            Logger::log("Loaded image " + name, LOGTYPE_EVENT);

        Images[name]->CreateMaskFromColor(sf::Color(255, 255, 255), 0);
    }
    else
    {
        Logger::log("Attempt to re-load image " + name + " aborting load", LOGTYPE_ERROR);
    }
}

void ResourceManager::loadAnimation(const std::string& name, const std::string& filepath, int frW, int frH, const float tbf, const int maxFrames, bool loop)
{
    loadImage(name, filepath);
    Animations[name] = new Animation(getImage(name), frW, frH, tbf, maxFrames, loop);
}

const sf::Image& ResourceManager::getImage(const std::string& name)
{
    // Test if the key exists
    if(Images.find(name) == Images.end())
    {
        Logger::log("Image " + name + " does not exist, a blank image will be returned", LOGTYPE_ERROR);
    }

    return *Images[name];
}

Animation* ResourceManager::getAnimation(const std::string& name)
{
    if(Animations.find(name) == Animations.end())
    {
        Logger::log("Animation " + name + " does not exist, an invalid pointer will be returned", LOGTYPE_ERROR);
    }

    Animation* tempAnim = new Animation(*Animations[name]);
    return tempAnim;
}
