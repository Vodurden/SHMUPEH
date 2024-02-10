#ifndef RESOURCEMANAGER_H_
#define RESOURCEMANAGER_H_

#include "Animation.h"

//Loads a static resource (Image or Animation) to be used by other classes
class ResourceManager
{
    private:
        static std::map<std::string, sf::Image*> Images;
        static std::map<std::string, Animation*> Animations;
    public:

        //Images
        static void loadImage(const std::string& name, const std::string& filepath);
        static const sf::Image& getImage(const std::string& name);

        //Animations
        static void loadAnimation(const std::string& name, const std::string& filepath, int frW, int frH, const float tbf, const int maxFrames, bool loop = true);
        static Animation* getAnimation(const std::string& name);
};

#endif // RESOURCEMANAGER_H_
