
//#include "PgePlatform.h"
#include "include/PgeBaseApplication.h"
#include "include/SDL/PgeSDLPlatformFactory.h"

#include "Demos/BasicTest/DemoApp.h"

#include "cmd/LogFileManager.h"
using cmd::LogFileManager;
using cmd::LogFileSection;
using cmd::LogFile;

cmd::LogFileManager cmd::LogFileManager::mInstance;

//#include "PgeLogFileManager.h"

int main ( int argc, char** argv )
{
    //PGE::LogFileManager* mLogFileManager;    ///< Instantiation of the log file manager
    //mLogFileManager = new PGE::LogFileManager();

    cmd::LogFileManager& lfm = cmd::LogFileManager::getInstance();
    //LogFileManager& lfm = LogFileManager::GetSingleton();
    lfm.CreateLog( "Pharaoh.log", true, cmd::LogFile::Everything );

    //PGE::BaseApplication app( new PGE::SDLPlatformFactory() );
    DemoApp app( new PGE::SDLPlatformFactory() );
    app.Init();

    app.Run();
//    delete mLogFileManager;

    return 0;
}
