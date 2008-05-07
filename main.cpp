#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif
#ifdef __APPLE__
#include <SDL/SDL.h>
#else
#include <SDL.h>
#endif

#include "BaseEngine.h"

int main ( int argc, char** argv )
{
    PGE::BaseEngine engine;
    engine.SetTitle( "Loading..." );
    engine.Init();

    engine.SetTitle( "Welcome to Pharaoh Game Engine" );
    engine.Run();

    engine.SetTitle( "Goodbye." );

    return 0;
}
