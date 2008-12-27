
/*! $Id$
 *  @file   PgeLogFile.h
 *  @author Chad M. Draper
 *  @date   December 13, 2008
 *
 */

#include "PgeLogFile.h"
#include "PgeStringUtil.h"

#include <iomanip>

namespace PGE
{
    ////////////////////////////////////////////////////////////////////////////
    // LogFile
    ////////////////////////////////////////////////////////////////////////////

    //Constructor
    LogFile::LogFile( const std::string& logFile, LoggingLevel logLevel, std::ios_base::openmode mode, std::ostream* stream )
        : mLogFile( 0 ),
          mOrigStreamBuf( 0 ),
          mOutputStream( 0 ),
          mRedirectStream( false ),
          mLogLevel( logLevel )
    {
        Reopen( logFile, mode, stream );
    }

    //Deconstructor
    LogFile::~LogFile()
    {
        Close();
    }

    //PushSection
    void LogFile::PushSection( const std::string& label )
    {
        // Write the label
        LogMessage( label, SectionStart );

        // Increment the section level
        mSections.push( label );
    }

    //PopSection
    void LogFile::PopSection()
    {
        // Get the name of the top-most section
        if ( mSections.size() )
        {
            std::string label = mSections.top();

            // Remove the section
            mSections.pop();

            // Write the label:
            LogMessage( label, SectionEnd );
        }
    }

    //SetLoggingLevel
    void LogFile::SetLoggingLevel( LoggingLevel lvl )
    {
        mLogLevel = ( lvl >= Threshold ) ? Threshold : lvl;
    }

    //Reopen
    void LogFile::Reopen( const std::string& logFile, std::ios_base::openmode mode, std::ostream* stream )
    {
        // Close the stream, assuming it is open:
        Close();

        // Make sure the file path exists:
        std::string path, filename;
        StringUtil::SplitFilename( logFile, path, filename );
        StringUtil::CreatePath( path );

        // Create the new log file and direct output to it:
        mLogFile = new std::ofstream;
        mLogFile->open( logFile.c_str(), mode );

        if ( stream )
        {
            mOrigStreamBuf = stream->rdbuf( mLogFile->rdbuf() );
            mOutputStream = stream;

            mRedirectStream = true;
        }
        else
        {
            mOrigStreamBuf = 0;
            mOutputStream  = 0;

            mRedirectStream = false;
        }

        // Write the header
        LogBreak();
        *mLogFile << "### " << logFile << std::endl;

        struct tm *pTime;
        time_t ctTime;
        time(&ctTime);
        pTime = localtime( &ctTime );
        *mLogFile << "### Started " << ctime( &ctTime );

        *mLogFile << "###" << std::endl;
        LogBreak();
        *mLogFile << std::endl;
    }

    //Close
    void LogFile::Close()
    {
        // Redirect output to the original stream:
        if ( mOutputStream )
            mOutputStream->rdbuf( mOrigStreamBuf );

        // Close the log file:
        if ( mLogFile )
            mLogFile->close();
        delete mLogFile;

        // Clear the section stack:
        while ( !mSections.empty() )
            mSections.pop();
    }

    //LogBreak
    void LogFile::LogBreak()
    {
        *mLogFile << "################################################################################\n";
    }

    //lead_in
    std::string LogFile::lead_in( ErrorCode errCode ) const
    {
        std::stringstream leadInStr;
        switch ( errCode )
        {
        case Remark:
            leadInStr << "[*] ";
            break;

        case Warning:
            leadInStr << "[-] ";
            break;

        case Error:
            leadInStr << "[!] ";
            break;

        case SectionStart:
            leadInStr << "[B] ";
            break;

        case SectionEnd:
            leadInStr << "[E] ";
            break;
        }

        // Get the current date and time
        struct tm *pTime;
        time_t ctTime;
        time(&ctTime);
        pTime = localtime( &ctTime );

        leadInStr << std::setw( 2 ) << std::setfill( '0' ) << pTime->tm_hour
                  << ":" << std::setw( 2 ) << std::setfill( '0' ) << pTime->tm_min
                  << ":" << std::setw( 2 ) << std::setfill( '0' ) << pTime->tm_sec;

        // Add the indent
        std::string indentStr = "";
        for ( int indent = 0; indent < mSections.size(); indent++ )
            indentStr += "    ";

        return leadInStr.str() + ": " + indentStr;
    }

    //LogMessage
    void LogFile::LogMessage( const std::string& msg, ErrorCode errCode, bool appendNewline )
    {
        // Log the message only if the error code + mLogLevel is >= LoggingLevel::Threshold
        if ( mLogLevel == Disabled || mLogLevel + errCode < Threshold )
            return;

        std::string leadInStr = lead_in( errCode );
        std::string termChar = appendNewline ? "\n" : "";
        switch ( errCode )
        {
        case Remark:
            *mLogFile << leadInStr << msg << termChar;
            break;

        case Warning:
            *mLogFile << leadInStr << msg << termChar;
            break;

        case Error:
            *mLogFile << leadInStr << msg << termChar;
            break;

        case SectionStart:
            *mLogFile << leadInStr << "Start Section: " << msg << termChar;
            *mLogFile << leadInStr << "{" << termChar;
            break;

        case SectionEnd:
            *mLogFile << leadInStr << "}" << termChar;
            *mLogFile << leadInStr << "End Section: " << msg << termChar;
            break;
        }

        // Flush the stream to make sure the log was written
        mLogFile->flush();
    }


    ////////////////////////////////////////////////////////////////////////////
    // LogFileSection
    ////////////////////////////////////////////////////////////////////////////

    //Constructor
    LogFileSection::LogFileSection( LogFile* lf, std::string sectName ) : mLogFile( lf )
    {
        if ( lf )
            lf->PushSection( sectName );
    }

    //Destructor
    LogFileSection::~LogFileSection()
    {
        if ( mLogFile )
            mLogFile->PopSection();
    }

}
