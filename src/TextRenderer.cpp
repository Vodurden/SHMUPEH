#include "TextRenderer.h"

#include "Logger.h"

Text::Text(const float X, const float Y, const char* str, sf::Font* Font, const float DTime, const sf::Color c)
{
    font = Font;
    sf::String tempS(str, *Font, Font->GetCharacterSize());
    originalMessage = str;
    string = tempS;
    string.SetPosition(X, Y);
    string.SetColor(c);
    col = c;
    dieTime = DTime;
}

void Text::draw(sf::RenderWindow& game)
{
    game.Draw(string);
}

int TextRenderer::gameW = 0;
int TextRenderer::gameH = 0;

TextRenderer::TextRenderer(const char* Fontpath, const unsigned int Fontsize, const sf::Color c)
{
    if(!font.LoadFromFile(Fontpath, Fontsize))
        Logger::log("Unable to load font " + std::string(Fontpath), LOGTYPE_ERROR);

    textQueues.reserve(9);
    fontsize = Fontsize;
    textColor = c;

    //Initialize the queue array
    for(int i = 0; i < 9; i++)
    {
        std::vector<Text*> a;
        textQueues.push_back(a);
    }
}

TextRenderer::~TextRenderer()
{
    for(std::vector<Text*>::iterator mIter = delayTexts.begin(); mIter != delayTexts.end(); mIter++)
        delete *mIter;

    for(std::vector<Text*>::iterator mIter = staticTexts.begin(); mIter != delayTexts.end(); mIter++)
        delete *mIter;
}

void TextRenderer::addStaticText(std::string message, float x, float y)
{
    staticTexts.push_back(new Text(x, y, message.c_str(), &font, -1, textColor));
    Logger::log("New static text added: " + message, LOGTYPE_EVENT);
}

void TextRenderer::addStaticTextWatch(std::string message, float x, float y, const float* watch)
{
    staticTextWatchesFloat.push_back(new Text(x, y, message.c_str(), &font, -1, textColor));
    staticTextValuesFloat.push_back(watch);
    Logger::log("New float static text watch added: " + message, LOGTYPE_EVENT);
}

void TextRenderer::addStaticTextWatch(std::string message, float x, float y, const int* watch)
{
    staticTextWatchesInt.push_back(new Text(x, y, message.c_str(), &font, -1, textColor));
    staticTextValuesInt.push_back(watch);
    Logger::log("New int static text watch added: " + message, LOGTYPE_EVENT);
}

void TextRenderer::addText(std::string message, int position, float dieTime)
{
    float LEFT = fontsize;
    float CENTER = (gameW / 2) - ((message.length() * (fontsize)) / 2);
    float RIGHT = gameW - (message.length() * (fontsize));
    float TOP = fontsize;
    float BOTTOM = gameH - fontsize * 2;
    float MID = (gameH / 2);

    float X = 0;
    float Y = 0;

    float DieTime = 0;
    std::string Message = message;

    switch(position)
    {
        case TOPLEFT:
            X = LEFT;
            Y = TOP;
            break;

        case TOPCENTER:
            X = CENTER;
            Y = TOP;
            break;

        case TOPRIGHT:
            X = RIGHT;
            Y = TOP;
            break;

        case MIDLEFT:
            X = LEFT;
            Y = MID;
            break;

        case MIDCENTER:
           X = CENTER;
           Y = MID;
           break;

        case MIDRIGHT:
            X = RIGHT;
            Y = MID;
            break;

        case BOTTOMLEFT:
            X = LEFT;
            Y = BOTTOM;
            break;

        case BOTTOMCENTER:
            X = CENTER;
            Y = BOTTOM;
            break;

        case BOTTOMRIGHT:
            X = RIGHT;
            Y = BOTTOM;
            break;

        default:
            X = CENTER;
            Y = MID;
            Message = "ERROR! Invalid Position";
            Logger::log("Text " + message + " is at an invalid position", LOGTYPE_ERROR);
            break;
    }

    for(std::vector<Text*>::iterator mIter = textQueues.at(position).begin();mIter != textQueues.at(position).end();mIter++)
    {
        DieTime = (*mIter)->getTimeLeft();
    }

    DieTime += dieTime;
    Text* temp = new Text(X, Y, Message.c_str(), &font, DieTime, textColor);
    temp->setMessage(Message.c_str());
    textQueues.at(position).push_back(temp);
    Logger::log("Text '" + Message + "' created, set to die in " +  std::to_string(dieTime) + "ms", LOGTYPE_TRIVIAL);
}

void TextRenderer::addDelayText(std::string message, float x, float y, float dieTime)
{
    delayTexts.push_back(new Text(x, y, message.c_str(), &font, dieTime, textColor));
}

void TextRenderer::think()
{
    //Delete dead messages
    for(std::vector<std::vector<Text*> >::iterator tIter = textQueues.begin(); tIter != textQueues.end(); tIter++)
    {
        for(std::vector<Text*>::iterator mIter = tIter->begin(); mIter != tIter->end();)
        {
            if((*mIter)->getTimeLeft() < 0)
            {
                mIter = tIter->erase(mIter);
            }
            else
            {
                mIter++;
            }
        }
    }

    for(std::vector<Text*>::iterator mIter = delayTexts.begin(); mIter != delayTexts.end();)
    {
        if((*mIter)->getTimeLeft() < 0)
        {
            mIter = delayTexts.erase(mIter);
        }
        else
        {
            mIter++;
        }
    }

    //Update Static Text Watches
    for(unsigned int z = 0; z < staticTextWatchesFloat.size(); z++)
    {
        staticTextWatchesFloat.at(z)->setMessage(staticTextWatchesFloat.at(z)->getOriginalMessage() + std::to_string(*staticTextValuesFloat.at(z)));
    }

    for(unsigned int z = 0; z < staticTextWatchesInt.size(); z++)
    {
        staticTextWatchesInt.at(z)->setMessage(staticTextWatchesInt.at(z)->getOriginalMessage() + std::to_string(*staticTextValuesInt.at(z)));
    }
}

void TextRenderer::draw(sf::RenderWindow& game)
{
    for(std::vector<std::vector<Text*> >::iterator mIter = textQueues.begin(); mIter != textQueues.end(); mIter++)
    {
        if( mIter->empty() == false)
            (*mIter).at(0)->draw(game); //Draw the first message in the queue
    }

    for(std::vector<Text*>::iterator mIter = staticTexts.begin(); mIter != staticTexts.end(); mIter++)
    {
        (*mIter)->draw(game);
    }

    for(std::vector<Text*>::iterator dIter = staticTextWatchesFloat.begin(); dIter != staticTextWatchesFloat.end(); dIter++)
    {
        (*dIter)->draw(game);
    }

    for(std::vector<Text*>::iterator mIter = staticTextWatchesInt.begin(); mIter != staticTextWatchesInt.end(); mIter++)
    {
        (*mIter)->draw(game);
    }

    for(std::vector<Text*>::iterator mIter = delayTexts.begin(); mIter != delayTexts.end(); mIter++)
    {
        (*mIter)->draw(game);
    }
}
