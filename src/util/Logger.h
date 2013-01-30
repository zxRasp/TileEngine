#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <string>
#include <fstream>

class Logger
{
public:
    static Logger* getInstance();

    void Shutdown();

    void logInfo    (const std::string& msg);
    void logDebug   (const std::string& msg);
    void logWarning (const std::string& msg);
    void logError   (const std::string& msg);

    void logMessage (const std::string& tag, const std::string& msg);

private:
    Logger();

    const std::string getCurrTime();

    std::ofstream*   m_pLogStream;
    static Logger*   s_Instance;
};

#endif // _LOGGER_H_
