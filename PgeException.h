
/*! $Id$
 *  @file   PgeException.h
 *  @author Chad M. Draper
 *  @date   May 1, 2008
 *  @brief  Defines an exception handling class for Pharaoh Game Engine.
 *
 */

#ifndef PGEEXCEPTION_H_INCLUDED
#define PGEEXCEPTION_H_INCLUDED

#include <exception>
#include <string>

namespace PGE
{
    /** @class Exception
        An exception thrown upon errors in Pharaoh Game Engine.  This contains
        a message pertaining to the error that can be logged.
    */
    class Exception : public std::exception
    {
    private:
        std::string mMessage;           /**< String descibing the exception */

    public:
        /** Default constructor */
        Exception() : std::exception(), mMessage( "" )
        {
        }

        /** Initialization constructor */
        Exception( const std::string& msg ) : std::exception(), mMessage( msg )
        {
        }

        /** Destructor */
        virtual ~Exception() throw() { }

        /** Get the exception message */
        virtual const char* what() const throw()
        {
            return mMessage.c_str();
        }

    }; // class Exception
} // namespace PGE

#endif // PGEEXCEPTION_H_INCLUDED
