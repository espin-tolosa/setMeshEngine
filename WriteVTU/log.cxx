#include <iostream>
#include "log.h"

    LogConsole::LogConsole()
    {
        Level m_logLevel = m_LevelWarning;
        std::cout<<"Level error by default is: "<<m_logLevel<<std::endl;
    }

    void LogConsole::SetLogLevelError()
    {
        m_logLevel = m_LevelError;
        std::cout<<"Only Error messages will be promted"<<std::endl;
    }

    void LogConsole::SetLogLevelWarning()
    {
        m_logLevel = m_LevelWarning;
        std::cout<<"Only Error and Warning messages will be promted"<<std::endl;
    }

    void LogConsole::SetLogLevelInfo()
    {
        m_logLevel = m_LevelInfo;
        std::cout<<"All messages: Error, Warning and Info will be promted"<<std::endl;
    }

    void LogConsole::Error(const char* message)
    {
        std::cout<<"[ERROR]: "<<message<<std::endl;
    }

    void LogConsole::Warning(const char* message)
    {
        if (m_logLevel>=m_LevelWarning)
        std::cout<<"[WARNING]: "<<message<<std::endl;
    }

    void LogConsole::Info(const char* message)
    {
        if (m_logLevel>=m_LevelInfo)
        std::cout<<"[INFO]: "<<message<<std::endl;
    }
