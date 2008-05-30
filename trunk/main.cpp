
//#include "PgePlatform.h"
#include "include/PgeBaseApplication.h"
#include "include/SDL/PgeSDLPlatformFactory.h"

int main ( int argc, char** argv )
{
    PGE::BaseApplication app( new PGE::SDLPlatformFactory() );
    app.Run();

    return 0;
}
