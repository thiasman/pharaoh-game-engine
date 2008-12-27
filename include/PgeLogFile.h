
/*! $Id$
 *  @file   PgeLogFile.h
 *  @author Chad M. Draper
 *  @date   December 13, 2008
 *  @brief  Directs output to a specified string, allowing logging to be done
 *          via std::cout.
 *
 */
#ifndef PGELOGFILE_H
#define PGELOGFILE_H

#include "PgeTypes.h"

#include <stack>
#include <fstream>
#include <iostream>

namespace PGE
{

    /** @class LogFile
        Provides a class for logging messages, which is also capable of
        redirecting output (such as to std::cout.)
    */
    class _PgeExport LogFile
    {
    public:

        /** Error codes
            @remarks These affect how the error messages are displayed
        */
        enum ErrorCode
            {
                Remark = 1,
                Warning,
                Error,
                SectionStart,
                SectionEnd
            };

        /** Logging level
            @remarks Indicates how verbose the logging should be.  Basically,
                    anything that's an error or higher will always be written
                    (unless logging is disabled.)  Other comments will depend on
                    the current logging level.
        */
        enum LoggingLevel
            {
                Disabled = 0,       /**< All logging is disabled.  Not very useful... */
                Low,                /**< Only Error or higher is logged. */
                Normal,             /**< Warnings and higher are logged. */
                Everything,         /**< All messages are logged. */

                Threshold           /**< If the current logging level + the error
                                         code is >= Threshold, the message is logged. */
            };

    private:
        std::ofstream*  mLogFile;               /**< Output file stream */
        std::ostream*   mOutputStream;          /**< Pointer to the output stream (default is std::cout) */
        std::streambuf* mOrigStreamBuf;         /**< Pointer to the original stream */
        bool            mRedirectStream;        /**< Indicates if the logfile is a
                                                     redirection of a stream (i.e. std::cout) */

        LoggingLevel    mLogLevel;              /**< Current level of detail. */
        std::stack< std::string > mSections;    /**< Stack of the sections in the log file.  Each
                                                     section is indented one level. */

    public:

        /** Constructor
            @param  logFile     Name of the log file
            @param  mode        Indicates the mode in which the file is opened
            @param  stream      If null, the output is not redirected.  Otherwise,
                                this is the stream to which output is directed.
        */
        LogFile( const std::string& logFile, LoggingLevel logLevel = Normal, std::ios_base::openmode mode = std::ios::out, std::ostream* stream = &std::cout );

        /** Destructor
            If output was being redirected, it will be restored to the original
            destination.
        */
        virtual ~LogFile();

        /** Add a new section level */
        void PushSection( const std::string& label );

        /** Remove a section level */
        void PopSection();

        /** Set the logging level to indicate what messages should be logged. */
        void SetLoggingLevel( LoggingLevel lvl );

        /** Close the current stream, and open an new one
            @param  logFile     Name of the log file
            @param  mode        Indicates the mode in which the file is opened
            @param  stream      If null, the output is not redirected.  Otherwise,
                                this is the stream to which output is directed.
        */
        void Reopen( const std::string& logFile, std::ios_base::openmode mode = std::ios::out, std::ostream* stream = &std::cout );

        /** Close the current stream, restoring redirection
        */
        void Close();

        /** Display a section break (80 #'s)
        */
        void LogBreak();

        /** Generate the message lead-in.  This is the message-type indicator,
            the current time, and and indentations.
        */
        std::string lead_in( ErrorCode errCode = Remark ) const;

        /** Write a message to the logfile, including the current date and time.
            @param  msg     Message to be written to the logfile
            @param  errCode Type of message
        */
        void LogMessage( const std::string& msg, ErrorCode errCode = Remark, bool appendNewline = true );

        /** Override the '<<' operator for writing simple messages. */
        template< typename T >
        inline std::ostream& operator<<( const T& val )
        {
            // Make sure the logging level is such that remarks can be logged.
            // Otherwise, write the message to cout.
            // Log the message only if the error code + mLogLevel is >= LoggingLevel::Threshold
            if ( mLogLevel == Disabled || mLogLevel + Remark < Threshold )
                return std::cout << lead_in() << val;

            std::ostream::sentry opfx(*mLogFile);
            if ( !opfx )
                return *mLogFile;

            // This should really only be called once per chain (i.e.
            // lf << "some" << "value") as it gets converted to an ostream,
            // which handles the rest of the chain.  Write the lead_in
            // before the value.
            *mLogFile << lead_in() << val;

            // Flush the stream to make sure the log was written
            mLogFile->flush();

            return *mLogFile;
        }

    }; // class LogFile

    /** @class LogFileSection
        @remarks
        Section group in a log file.  This is essentially a helper class for
        creating a new section which will "pop" itself when it goes out of scope.

        @remarks
        This works well for automatically closing the section when going out of
        scope.  However, it should be noted that if there is a system crash, the
        stack will get released, but the heap may be orphaned.  This means that
        the LogFileSection's destructor will be called while the log file is
        open, thereby closing the section.  Just be aware of this if using the
        class.
    */
    class _PgeExport LogFileSection
    {
    private:
        LogFile*    mLogFile;               /**< Pointer to the log file containing this section */

    public:
        /** Constructor */
        LogFileSection( LogFile* lf, std::string sectName );

        /** Destructor */
        ~LogFileSection();

    }; // class LogFileSection

} // namespace PGE

#endif // PGELOGFILE_H
