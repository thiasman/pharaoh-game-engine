
#include "PgeGameManager.h"
#include "SDL/PgeSDLWindowSystem.h"
//#include "PgeTileEngine.h"
#include "version.h"
#include "dir.h"

#include "PgePoint2D.h"
#include "PgeMatrix2D.h"
#include "PgeMath.h"

#include "cmd/LogFileManager.h"
cmd::LogFileManager cmd::LogFileManager::mInstance;

int main ( int argc, char** argv )
{
    cmd::LogFileManager& lfm = cmd::LogFileManager::getInstance();
    lfm.CreateLog( "Pharaoh.log", true, cmd::LogFile::Everything );
    cmd::LogFileSection sect( lfm.GetDefaultLog(), "main(...)" );

    //PGE::GameManager gameMgr;

    PGE::SDLWindowSystem engine;
    //PGE::TileEngine engine;
    engine.SetTitle( "Loading..." );
    engine.Init();

    std::string title = std::string( "Welcome to Pharaoh Game Engine - " ) + AutoVersion::FULLVERSION_STRING;
    engine.SetTitle( title );

    engine.Run();

    engine.SetTitle( "Goodbye." );

    return 0;
}
