
//#include "PgePlatform.h"
#include "include/PgeBaseApplication.h"
#include "include/SDL/PgeSDLPlatformFactory.h"

#include "Demos/BasicTest/DemoApp.h"

#include "cmd/LogFileManager.h"
cmd::LogFileManager cmd::LogFileManager::mInstance;

int main ( int argc, char** argv )
{
    cmd::LogFileManager& lfm = cmd::LogFileManager::getInstance();
    lfm.CreateLog( "Pharaoh.log", true, cmd::LogFile::Everything );

    //PGE::BaseApplication app( new PGE::SDLPlatformFactory() );
    DemoApp app( new PGE::SDLPlatformFactory() );
    app.Init();
    app.Run();

    return 0;
}
