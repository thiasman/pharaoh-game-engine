
/*! $Id$
 *  @file   PgeTextureManager.h
 *  @author Chad M. Draper
 *  @date   May 8, 2007
 *  @brief  A class which enables derived classes to be treated as singletons.
 *
 */

#ifndef PGESINGLETON_H
#define PGESINGLETON_H

#include "PgePlatform.h"

#include "cmd/LogFileManager.h"

namespace PGE
{
    /** @class Singleton
        This template class automates the creation of singletons, simplifying
        usage of globally accessible objects.  These singletons still support
        polymorphism.  Further information can be found at
        <a href="http://www.raba.com/~jcstaff/oodev/presents/objcreat/singlet.h">
        http://www.raba.com/~jcstaff/oodev/presents/objcreat/singlet.h</a>.
    */
    template < typename T >
    class _PgeExport Singleton
    {
    protected:
        static T* mInstance;

    public:
        /** Constructor */
        Singleton()
        {
            assert( !mInstance );
            mInstance = static_cast< T* >( this );
        }

        /** Destructor */
        virtual ~Singleton()
        {
            assert( mInstance );
            mInstance = 0;
        }

        /** Get the instance */
        static T& GetSingleton()
        {
            assert( mInstance );
            return *mInstance;
        }

        /** Get a pointer to the instance */
        static T* GetSingletonPtr()
        {
            return mInstance;
        }
    };

    //template < typename T > T* Singleton< T >::mInstance = 0;

} // namespace PGE

#endif // PGESINGLETON_H
