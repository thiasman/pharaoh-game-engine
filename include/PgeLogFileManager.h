
/*! $Id$
 *  @file   PgeLogFile.h
 *  @author Chad M. Draper
 *  @date   December 15, 2008
 *  @brief  Manages log files.
 *
 */

#ifndef PGELOGFILEMANAGER_H
#define PGELOGFILEMANAGER_H

#include <map>
#include "PgeTypes.h"
#include "PgeSingleton.h"
#include "PgeLogFile.h"

namespace PGE
{

    /** @brief Manages log files for an application

        An application will typically create a log file name <AppName>.log.
        However, if logging is to occur within libraries used by the application
        (and written to <AppName>.log, it is necessary to have a way to retrieve
        the appropriate log file without knowing the name.  The log file manager
        is a singleton, and there is only one manager per application instance.
        The manager should be used to create all log files, and will allow the
        application to set the default log file.  The manager can handle
        multiple log files, which can be retrieved by name, but the default file
        can be retrieved anywhere.
    */
    class _PgeExport LogFileManager : public Singleton< LogFileManager >
    {
    private:
        typedef std::map< std::string, LogFile*, std::less< std::string > > LogList;
        LogList mLogs;                  // All logs maintained by the manager
        LogFile* mDefaultLog;           // Pointer to the default log file

    public:

        /** Constructor */
        LogFileManager();

        /** Destructor */
        ~LogFileManager();

        /** Override singleton retrieval to avoid link errors */
        static LogFileManager& GetSingleton();
        /** Override singleton pointer retrieval to avoid link errors */
        static LogFileManager* GetSingletonPtr();

        /** Create a new log file
            @param  name            Name of the log file, also used as an index in the log list
            @param  isDefault       Indicates if this log file is the default log file
            @param  mode        Indicates the mode in which the file is opened
            @param  stream      If null, the output is not redirected.  Otherwise,
                                this is the stream to which output is directed.
        */
        LogFile* CreateLog( const std::string& name,
                            bool isDefault = false,
                            LogFile::LoggingLevel logLevel = LogFile::Normal,
                            std::ios_base::openmode mode = std::ios::out,
                            std::ostream* stream = 0 );

        /** Get a pointer to a specified log file */
        LogFile* GetLog( const std::string& name );

        /** Get the default log file */
        LogFile* GetDefaultLog() const;

        /** Set the default log file */
        void SetDefaultLog( LogFile* log );

        /** Set the logging level of the default log file */
        void SetLoggingLevel( LogFile::LoggingLevel lvl );

        /** Get the lead-in string for the default log file */
        std::string lead_in( LogFile::ErrorCode errCode = LogFile::Remark );

        /** Write a log message to the default log file */
        void LogMessage( const std::string& msg, LogFile::ErrorCode errCode = LogFile::Remark, bool appendNewline = true );

        /** Push a new section onto the stack */
        void PushSection( const std::string& name );

        /** Pop a section from the stack */
        void PopSection();

        /** Allow remarks to be posted using the '<<' operator
            @remarks Whatever is passed to this command WILL be written, and
                    labeled as a remark.
        */
        template< typename T >
        inline std::ostream& operator<<( const T& val )
        {
            if ( GetDefaultLog() )
            {
                return GetDefaultLog()->operator<<( val );
            }
            return std::cerr;
        }

    }; // class LogFileManager

} // namespace PGE
#endif // PGELOGFILEMANAGER_H
