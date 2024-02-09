#include "Logger.h"

std::ofstream Logger::logfile;
int Logger::logLevel = LOGTYPE_TRIVIAL;
int Logger::errorCount = 0, Logger::eventCount = 0, Logger::trivialCount = 0;
void Logger::setLogFile(const char* filename)
{
    logfile.open(filename, std::ios::trunc);
}
std::string Logger::getLogtypeString(int ltype)
{
    switch(ltype) //LOGTYPES are sorted by priority
    {
        case LOGTYPE_ERROR:
            return "ERROR: ";
            errorCount++;
            break;
        case LOGTYPE_EVENT:
            return "EVENT: ";
            eventCount++;
            break;
        case LOGTYPE_TRIVIAL:
            return "TRIVIAL: ";
            trivialCount++;
            break;
        default:
            return "|--LOGTYPE TYPE RETRIEVAL ERROR--| ";
    }
}
//Appends the logtype and then the message to the logfile
void Logger::log(const std::string& message, const int logtype, const int linebreak)
{
    if(logtype <= logLevel)
    {
        logfile << getLogtypeString(logtype) << message;

        if(linebreak == LINEBREAK_Y)
            logfile << std::endl;
    }
}
