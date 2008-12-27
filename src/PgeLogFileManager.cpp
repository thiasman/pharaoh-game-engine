
/*! $Id$
 *  @file   PgeLogFile.cpp
 *  @author Chad M. Draper
 *  @date   December 15, 2008
 *
 */
#include "PgeLogFileManager.h"

namespace PGE
{

    ////////////////////////////////////////////////////////////////////////////
    // LogFileManager
    ////////////////////////////////////////////////////////////////////////////

    // Instantiate the singleton instance
    template<> LogFileManager* Singleton< LogFileManager >::mInstance = 0;

    //Constructor
    LogFileManager::LogFileManager()
    {
        mDefaultLog = 0;
    }

    //Destructor
    LogFileManager::~LogFileManager()
    {
        // Delete the log files
        LogList::iterator iter;
        for ( iter = mLogs.begin(); iter != mLogs.end(); iter++ )
        {
            delete iter->second;
        }
        mLogs.clear();
        mDefaultLog = 0;
    }

    //GetSingleton
    LogFileManager& LogFileManager::GetSingleton()
    {
        assert( mInstance );
        return *( static_cast< LogFileManager* >( mInstance ) );
    }

    //GetSingletonPtr
    LogFileManager* LogFileManager::GetSingletonPtr()
    {
        return static_cast< LogFileManager* >( mInstance );
    }

    //CreateLog
    LogFile* LogFileManager::CreateLog( const std::string& name,
                        bool isDefault,
                        LogFile::LoggingLevel logLevel,
                        std::ios_base::openmode mode,
                        std::ostream* stream )
    {
        // See if the log file has already been created
        LogList::iterator iter = mLogs.find( name );
        if ( iter == mLogs.end() )
        {
            // Create the log file:
            LogFile* log = new LogFile( name, logLevel, mode, stream );

            // If this is the first log file, or it is marked as default, set
            // the default log file pointer:
            if ( !mDefaultLog || isDefault )
                mDefaultLog = log;

            // Add the log to the list:
            mLogs.insert( LogList::value_type( name, log ) );

            // Return the new log file:
            return log;
        }
        else
            return iter->second;
    }

    //GetLog
    LogFile* LogFileManager::GetLog( const std::string& name )
    {
        // Look through the list.  If the named log file is found, return
        // it's pointer.  If the file is not found, return null.
        LogList::iterator iter = mLogs.find( name );
        if ( iter != mLogs.end() )
            return iter->second;
        return 0;
    }

    //GetDefaultLog
    LogFile* LogFileManager::GetDefaultLog() const
    {
        return mDefaultLog;
    }

    //SetDefaultLog
    void LogFileManager::SetDefaultLog( LogFile* log )
    {
        mDefaultLog = log;
    }

    //SetLoggingLevel
    void LogFileManager::SetLoggingLevel( LogFile::LoggingLevel lvl )
    {
        if ( mDefaultLog )
            mDefaultLog->SetLoggingLevel( lvl );
    }

    //lead_in
    std::string LogFileManager::lead_in( LogFile::ErrorCode errCode )
    {
        if ( GetDefaultLog() )
            return GetDefaultLog()->lead_in( errCode );
        return "";
    }

    //LogMessage
    void LogFileManager::LogMessage( const std::string& msg, LogFile::ErrorCode errCode, bool appendNewline )
    {
        if ( GetDefaultLog() )
            GetDefaultLog()->LogMessage( msg, errCode, appendNewline );
    }

    //PushSection
    void LogFileManager::PushSection( const std::string& name )
    {
        if ( GetDefaultLog() )
            GetDefaultLog()->PushSection( name );
    }

    //PopSection
    void LogFileManager::PopSection()
    {
        if ( GetDefaultLog() )
            GetDefaultLog()->PopSection();
    }

} // namespace PGE
