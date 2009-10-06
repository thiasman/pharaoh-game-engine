
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
#include "PgeBaseWindowListener.h"
#include "PgeArchiveManager.h"
#include "PgeTextureManager.h"
#include "PgeFontManager.h"
//#include "PgeLogFileManager.h"
//#include "PgeTileMap.h"
//#include "PgeStringUtil.h"

#include "PgePoint2D.h"
#include "PgeMatrix2D.h"
#include "PgeMath.h"

#include "cmd/StringUtil.h"
using cmd::StringUtil;
namespace PGE
{
    BaseApplication::BaseApplication( PlatformFactory* factory )
        : mPlatformFactory( factory ),
          mTextureManager( 0 ),
          mArchiveManager( 0 ),
          //mTileManager( 0 ),
          mFontManager( 0 )
          //mLogFileManager( 0 )
    {
        //ctor
        //mLogFileManager = new LogFileManager();
    }

    BaseApplication::~BaseApplication()
    {
        //dtor
        mTextureManager.SetNull();
        mArchiveManager.SetNull();
        mFontManager.SetNull();
        mOverlayManager.SetNull();
    }

    //Init----------------------------------------------------------------------
    void BaseApplication::Init()
    {
        // Create the window:
        _createWindow();

        // Get the window ID
        mWindow->GetCustomAttribute( "WINDOW", &mWindowHandle );
        //BaseInputListener::Init( mWindowHandle );

        OIS::ParamList pl;
//        String hndStr = StringUtil::ToString( mWindowHandle );
        String hndStr = StringUtil::toString( mWindowHandle );
        pl.insert( std::make_pair( String( "WINDOW" ), hndStr ) );
#if PGE_PLATFORM == PGE_PLATFORM_WIN32
        pl.insert( std::make_pair( String( "w32_mouse" ), String( "DISCL_FOREGROUND" ) ) );
        pl.insert( std::make_pair( String( "w32_mouse" ), String( "DISCL_NONEXCLUSIVE" ) ) );
#endif

        // Initialize the input manager:
        InputManager* inputMgr = InputManager::getSingletonPtr();
        inputMgr->Init( pl );

        // Initialize the managers:
        //mTileManager    = new TileManager();
        mArchiveManager = ArchiveManagerPtr( new ArchiveManager() );
        mTextureManager = TextureManagerPtr( new TextureManager() );
        mFontManager    = FontManagerPtr( new FontManager() );
        mOverlayManager = OverlayManagerPtr( new OverlayManager() );

        // Perform additional initialization:
        AdditionalInit();
    }

    //_createWindow-------------------------------------------------------------
    void BaseApplication::_createWindow()
    {
        try
        {
            assert( !mPlatformFactory.IsNull() );

            mWindow.SetNull();
            mWindow = SharedPtr< BaseWindowSystem >( mPlatformFactory->CreateWindowSystem() );
            assert( !mWindow.IsNull() );

            // Add the window listener:
            mWindow->AddWindowListener( this );
            mWindow->Init();
        }
        catch ( std::exception& e )
        {
//            lfm << e.what() << std::endl;
        }
    }

    void BaseApplication::Run()
    {
/*
        try
        {
            assert( !mWindow.IsNull() );

            mGameManager.Init();

            // Get the window ID
            size_t winHnd = 0;
            mWindow->GetCustomAttribute( "WINDOW", &winHnd );

            //PGE::TileEngine engine;
            mWindow->SetTitle( "Loading..." );

            std::string title = std::string( "Welcome to Pharaoh Game Engine - " ) + AutoVersion::FULLVERSION_STRING;
            mWindow->SetTitle( title );

            mWindow->Run();

            while ( !mWindow->IsClosed() )
            {
                // Run the window message pump:
                mWindow->MessagePump();

                // Update the logic:
                //DoLogic();
                mGameManager.PrepareFrame();

                // Lock the surface before rendering:
                mWindow->LockSurface();

                // Update the display:
                //DoRender();
                mGameManager.RenderFrame();

                // Unlock the surface before rendering:
                mWindow->UnlockSurface();

                //mWindow->RenderFrame();
            }
            mWindow->Shutdown();

            mWindow->SetTitle( "Goodbye." );

        }
        catch ( std::exception& e )
        {
            lfm << e.what() << std::endl;
        }
*/
    }

    //WindowSizeChanged---------------------------------------------------------
    void BaseApplication::WindowSizeChanged( BaseWindowSystem* win )
    {
        // Get the window metrics:
        int x, y, z, width, height;
        win->GetMetrics( x, y, z, width, height );
    }

    //WindowClosed--------------------------------------------------------------
    void BaseApplication::WindowClosed( BaseWindowSystem* win )
    {
    }

    //WindowFocusChanged--------------------------------------------------------
    void BaseApplication::WindowFocusChanged( BaseWindowSystem* win )
    {
/*
        LogFileManager& lfm = LogFileManager::GetSingleton();
        LogFileSection sect( lfm.GetDefaultLog(), "BaseApplication::WindowFocusChanged(...)" );

        if ( win->IsActive() )
            lfm << "Window activated\n";
        else
            lfm << "Window deactivated\n";
*/
    }

} // namespace PGE
