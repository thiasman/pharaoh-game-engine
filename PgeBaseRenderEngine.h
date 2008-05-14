
/*! $Id$
 *  @file   PgeBaseRenderEngine.h
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
    /** @class BaseRenderEngine
        Provides the base for the rendering engine.  This should be sub-classed
        in order to customize what the engine can do.
    */
    class BaseRenderEngine
    {
    public:
        BaseRenderEngine();
        virtual ~BaseRenderEngine();
    protected:
    private:

    }; // class BaseRenderEngine

} // namespace PGE

#endif // PGEBASERENDERENGINE_H
