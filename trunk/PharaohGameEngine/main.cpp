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
#include "version.h"
#include "dir.h"

#include "PgePoint2D.h"
#include "PgeMatrix2D.h"
#include "PgeMath.h"

#include <cmd/LogFileManager.h>
cmd::LogFileManager cmd::LogFileManager::mInstance;

int main ( int argc, char** argv )
{
    cmd::LogFileManager& lfm = cmd::LogFileManager::getInstance();
    lfm.CreateLog( "Pharaoh.log", true, cmd::LogFile::Everything );
    cmd::LogFileSection sect( lfm.GetDefaultLog(), "main(...)" );

    PGE::BaseEngine engine;
    engine.SetTitle( "Loading..." );
    engine.Init();

    std::string title = std::string( "Welcome to Pharaoh Game Engine - " ) + AutoVersion::FULLVERSION_STRING;
    engine.SetTitle( title );

    engine.Run();

    engine.SetTitle( "Goodbye." );

    return 0;
}
