
#include "PgeTileEngine.h"
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

    PGE::TileEngine engine;
    engine.SetTitle( "Loading..." );
    engine.Init();

    std::string title = std::string( "Welcome to Pharaoh Game Engine - " ) + AutoVersion::FULLVERSION_STRING;
    engine.SetTitle( title );
PGE::Int intVal = 48879;
PGE::String hexVal = "deadbeef";
PGE::Int h2iVal = PGE::Math::Hex2Int( hexVal );
PGE::String i2hVal = PGE::Math::Int2Hex( intVal );
lfm << "intVal = " << intVal << " in hex = " << i2hVal << ", hexVal = " << hexVal << " as integer = " << h2iVal << std::endl;

    engine.Run();

    engine.SetTitle( "Goodbye." );

    return 0;
}
