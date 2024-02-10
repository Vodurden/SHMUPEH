#ifndef LOGGER_H_
#define LOGGER_H_

#include <sstream>
#include <fstream>
#include <string>

//Closer to the left = higher priority
//For example if LOGTYPE_TRIVIAL is the logLevel, all logs will be displayed
//If LOGTYPE_EVENT is the logLevel, LOGTYPE_TRIVIAL will not be displayed
//If LOGTYPE_ERROR is the logLevel only errors will be displayed
enum {LOGTYPE_ERROR, LOGTYPE_EVENT, LOGTYPE_TRIVIAL};
enum {LINEBREAK_Y, LINEBREAK_N};

class Logger
{
    private:
        static std::ofstream logfile;
        static int logLevel;
        static int errorCount, eventCount, trivialCount;

        static std::string getLogtypeString(int ltype);
    public:
        static void log(const std::string& message, const int logtype, const int linebreak = LINEBREAK_Y);
        static void setLogLevel(const int lLevel) {logLevel = lLevel;}
        static void setLogFile(const char* filename);
};

#endif // LOGGER_H_
