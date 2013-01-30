#include <ctime>

#include "Logger.h"

Logger* Logger::s_Instance = 0;

Logger* Logger::getInstance()
{
    if (s_Instance == 0)
        s_Instance = new Logger();

    return s_Instance;
}

Logger::Logger()
{
    m_pLogStream = new std::ofstream("TileEngine.log");
}

void Logger::Shutdown()
{
    m_pLogStream->close();
    delete m_pLogStream;
}

void Logger::logInfo(const std::string& msg)
{
    logMessage("[INFO]", msg);
}

void Logger::logDebug(const std::string& msg)
{
    logMessage("[DEBUG]", msg);
}

void Logger::logWarning(const std::string& msg)
{
    logMessage("[WARNING]", msg);
}

void Logger::logError (const std::string& msg)
{
    logMessage("[ERROR]", msg);
}

void Logger::logMessage(const std::string& tag, const std::string& msg)
{
    (*m_pLogStream) << '[' << getCurrTime() << ']' << tag << ' ' << msg << std::endl;
}

const std::string Logger::getCurrTime()
{
    std::string result;

    time_t currTime = time(0);

    if (currTime < 0)
        return result;

    tm* tp = localtime(&currTime);

    const int strTimeLen = 10;
    char strTime[strTimeLen];

    if (strftime(strTime, strTimeLen, "%H:%M:%S", tp) > 0)
        result.append(strTime);

    return result;
}
