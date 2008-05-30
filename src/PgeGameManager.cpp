
/*! $Id$
 *  @file   PgeGameManager.cpp
 *  @author Chad M. Draper
 *  @date   May 14, 2008
 *
 */

#include "PgeGameManager.h"

namespace PGE
{
    GameManager::GameManager()
    {
        //ctor
    }

    GameManager::~GameManager()
    {
        //dtor
    }

    //Init----------------------------------------------------------------------
    void GameManager::Init()
    {
        mTileEngine.Init();
    }

    //PrepareFrame--------------------------------------------------------------
    void GameManager::PrepareFrame()
    {
        mTileEngine.PrepareFrame();
    }

    //RenderFrame---------------------------------------------------------------
    void GameManager::RenderFrame()
    {
        mTileEngine.RenderFrame();
    }

} // namespace PGE
