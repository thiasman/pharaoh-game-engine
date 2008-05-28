
/*! $Id$
 *  @file   PgeBaseApplication.cpp
 *  @author Chad M. Draper
 *  @date   May 22, 2008
 *
 */

#include "PgePlatform.h"
#include "version.h"
#include "PgeTypes.h"
#include "PgeBaseApplication.h"
#include "PgePlatformFactory.h"
#include "PgeBaseWindowSystem.h"

#include "PgePoint2D.h"
#include "PgeMatrix2D.h"
#include "PgeMath.h"

#include "cmd/LogFileManager.h"
cmd::LogFileManager cmd::LogFileManager::mInstance;

namespace PGE
{
    BaseApplication::BaseApplication( PlatformFactory* factory )
        : mPlatformFactory( factory )
    {
        //ctor
    }

    BaseApplication::~BaseApplication()
    {
        //dtor
    }

    void BaseApplication::Run()
    {
        cmd::LogFileManager& lfm = cmd::LogFileManager::getInstance();
        lfm.CreateLog( "Pharaoh.log", true, cmd::LogFile::Everything );
        cmd::LogFileSection sect( lfm.GetDefaultLog(), "main(...)" );

        try
        {
            assert( !mPlatformFactory.IsNull() );

            SharedPtr< BaseWindowSystem > window( mPlatformFactory->CreateWindowSystem() );
            assert( !window.IsNull() );

            size_t winHnd = 0;
            window->GetCustomAttribute( "WINDOW", &winHnd );

            //PGE::TileEngine engine;
            window->SetTitle( "Loading..." );
            window->Init();

            std::string title = std::string( "Welcome to Pharaoh Game Engine - " ) + AutoVersion::FULLVERSION_STRING;
            window->SetTitle( title );

            window->Run();

            while ( !window->IsClosed() )
            {
                window->RenderFrame();
            }
            window->Shutdown();

            window->SetTitle( "Goodbye." );

        }
        catch ( std::exception& e )
        {
            lfm << e.what() << std::endl;
        }
    }

} // namespace PGE
