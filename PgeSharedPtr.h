
/*! $Id$
 *  @file   PgeSharedPtr.h
 *  @author Chad M. Draper
 *  @date   May 8, 2008
 *  @brief  Defines a shared pointer, which automatic garbage collection.
 *
 */

#ifndef PGESHAREDPTR_H_INCLUDED
#define PGESHAREDPTR_H_INCLUDED

namespace PGE
{
    /** @class SharedPtr
        The SharedPtr is a reference-counted pointer, used where implicit
        destruction is required.
        @remarks
        This is a basic shared pointer that uses a reference count to know
        when to delete a pointer.
    */
    template < typename T >
    class SharedPtr
    {
    protected:
        T*              pData;
        unsigned int*   pUseCount;

    public:
        /** Constructor, creates a null pointer.
            @remarks
            <b>Important!</b> bind() must be called before using SharedPtr.
        */
        SharedPtr() : pData( 0 ), pUseCount( 0 )
        {
        }

        /** Create a shared pointer with given data */
        explicit SharedPtr( T* data ) : pData( data ), pUseCount( new unsigned int( 1 ) )
        {
        }

        /** Copy constructor */
        SharedPtr( const SharedPtr& ptr )
            : pData( 0 ), pUseCount( 0 )
        {
            pData = ptr.pData;
            pUseCount = ptr.pUseCount;
            if ( pUseCount )
                ++( *pUseCount );
        }

        /** Assignment operator */
        SharedPtr& operator=( const SharedPtr& ptr )
        {
            if ( pData == ptr.pData )
                return *this;
            release();

            pData = ptr.pData;
            pUseCount = ptr.pUseCount;
            if ( pUseCount )
                ++( *pUseCount );

            return *this;
        }

        /** Dereference the pointer */
        inline T& operator*() const
        {
            assert( pData );
            return *pData;
        }

        /** Reference the pointer to access its members */
        inline T* operator->() const
        {
            assert( pData );
            return pData;
        }

        /** Get the pointer data */
        inline T* Get() const
        {
            return pData;
        }

        /** Bind the pointer to its data
            @remark
                Assumes the pointer is <B>not</B> initialized.
        */
        void Bind( T* data )
        {
            assert( !pData && !pUseCount );
            pUseCount = new unsigned int( 1 );
            pData = data;
        }

        /** Determine if the pointer is unique
            (use count == 1)
        */
        inline bool IsUnique() const
        {
            assert( pUseCount );
            return *pUseCount == 1;
        }

        /** Get the number of times this point is currently used */
        inline unsigned int UseCount() const
        {
            assert( pUseCount );
            return *pUseCount;
        }

        /** Get the use count pointer */
        inline unsigned int* UseCountPtr() const
        {
            return pUseCount;
        }

        /** Test if the pointer is null */
        inline bool IsNull() const
        {
            return pData == 0;
        }

        /** Clear the pointer and set it to null */
        inline void SetNull()
        {
            if ( pData )
            {
                release();
                pData = 0;
                pUseCount = 0;
            }
        }

    protected:
        /** Release the pointer, removing all uses */
        void release()
        {
            bool destroyThis = false;

            if ( pUseCount )
            {
                // If this was the last use of the pointer, delete the data
                if ( --( *pUseCount ) == 0 )
                {
                    destroyThis = true;
                }
            }

            if ( destroyThis )
            {
                destroy();
            }
        }

        /** Destroy the pointer
            @remark
                <i>If this crashes, there were pointers that were not freed
                prior to shutting down.</i>
        */
        virtual void destroy()
        {
            delete pData;
            pData = 0;
            delete pUseCount;
            pUseCount = 0;
        }

    }; // class SharedPtr

    /** Compare pointers for equality */
    template < class T, class U > inline bool operator==( SharedPtr<T> const& a, SharedPtr<U> const& b )
    {
        return ( a.get() == b.get() );
    }

    /** Compare pointers for inequality */
    template < class T, class U > inline bool operator!=( SharedPtr<T> const& a, SharedPtr<U> const& b )
    {
        return ( a.get() != b.get() );
    }

} // namespace PGE

#endif // PGESHAREDPTR_H_INCLUDED
