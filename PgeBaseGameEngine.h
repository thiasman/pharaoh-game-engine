
/*! $Id$
 *  @file   PgeBaseGameEngine.h
 *  @author Chad M. Draper
 *  @date   May 14, 2008
 *  @brief  Provides the base class for the OpenGL rendering system.  This
 *          should be overridden in order to customize the functionality of the
 *          class (for instance, side-scrolling, 3D, etc.)
 *
 */

#ifndef PGEBASERENDERENGINE_H
#define PGEBASERENDERENGINE_H


namespace PGE
{
    /** @class BaseGameEngine
        Provides the base for the rendering engine.  This should be sub-classed
        in order to customize what the engine can do.
    */
    class BaseGameEngine
    {
    public:
        BaseGameEngine();
        virtual ~BaseGameEngine();
    protected:
    private:

    }; // class BaseGameEngine

} // namespace PGE

#endif // PGEBASERENDERENGINE_H
