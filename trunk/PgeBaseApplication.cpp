
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
        assert( !mPlatformFactory.IsNull() );

        cmd::LogFileManager& lfm = cmd::LogFileManager::getInstance();
        lfm.CreateLog( "Pharaoh.log", true, cmd::LogFile::Everything );
        cmd::LogFileSection sect( lfm.GetDefaultLog(), "main(...)" );

        SharedPtr< BaseWindowSystem > engine( mPlatformFactory->CreateWindowSystem() );
        assert( !engine.IsNull() );
        //PGE::TileEngine engine;
        engine->SetTitle( "Loading..." );
        engine->Init();

        std::string title = std::string( "Welcome to Pharaoh Game Engine - " ) + AutoVersion::FULLVERSION_STRING;
        engine->SetTitle( title );

        engine->Run();

        engine->SetTitle( "Goodbye." );
    }

} // namespace PGE
