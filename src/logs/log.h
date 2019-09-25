#ifndef LOG_H_INCLUDED
#define LOG_H_INCLUDED


class LogConsole
{
    enum Level
    {
        m_LevelError, m_LevelWarning, m_LevelInfo
    };

    Level m_logLevel;

    public:

    LogConsole();
    void SetLogLevelError();
    void SetLogLevelWarning();
    void SetLogLevelInfo();
    void Error(const char* message);
    void Warning(const char* message);
    void Info(const char* message);

};

#endif // LOG_H_INCLUDED
