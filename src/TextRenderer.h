#ifndef TEXTRENDERER_H_
#define TEXTRENDERER_H_

enum {TOPLEFT, TOPCENTER, TOPRIGHT, MIDLEFT, MIDCENTER, MIDRIGHT, BOTTOMLEFT, BOTTOMCENTER, BOTTOMRIGHT};
class Text
{
    private:
        sf::String string;
        std::string originalMessage;
        sf::Font* font;
        sf::Color col;
        sf::Clock lifeTimer;
        float dieTime;

    public:
        Text(const float X, const float Y, const char* str, sf::Font* Font, const float DTime, const sf::Color c);
        float getTimeLeft() {return dieTime - lifeTimer.GetElapsedTime();}
        void draw(sf::RenderWindow& game);
        void setMessage(const char* msg) {string.SetText(msg); setColor(col);}
        void setMessage(std::string msg) {string.SetText(msg.c_str()); setColor(col);}
        void setColor(sf::Color c) {string.SetColor(c); col = c;}
        std::string getMessage() {return string.GetText();}
        std::string& getOriginalMessage() {return originalMessage;}

        sf::Clock& getTimer() {return lifeTimer;}
};

// Class to render any text onscreen
class TextRenderer
{
    private:
        static int gameW, gameH;
        unsigned int fontsize;
        sf::Font font;
        sf::Color textColor;

        std::vector<std::vector<Text*> > textQueues;
        std::vector<Text*> delayTexts;
        std::vector<Text*> staticTexts;
        std::vector<Text*> staticTextWatchesFloat;
        std::vector<Text*> staticTextWatchesInt;
        std::vector<const float*> staticTextValuesFloat;
        std::vector<const int*> staticTextValuesInt;

    public:
        TextRenderer(const char* Fontpath, const unsigned int Fontsize, const sf::Color c);
        ~TextRenderer();
        void addDelayText(std::string message, float x, float y, float dieTime);
        void addText(std::string message, int position, float dieTime);
        void addStaticText(std::string message, float x, float y);
        void addStaticTextWatch(std::string message, float x, float y, const int* watch);
        void addStaticTextWatch(std::string message, float x, float y, const float* watch);
        void setTextColor(sf::Color c) {textColor = c;}

        void think();
        void draw(sf::RenderWindow& game);

        static void giveScreenArgs(int w, int h) {gameW = w; gameH = h;}
};

#endif // TEXTRENDERER_H_
