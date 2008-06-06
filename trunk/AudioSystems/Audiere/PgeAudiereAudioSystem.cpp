
/*! $Id$
 *  @file   PgeAudiereAudioSystem.cpp
 *  @author Chad M. Draper
 *  @date   June 6, 2008
 *
 */

#include "PgeAudiereAudioSystem.h"

namespace PGE
{
    ////////////////////////////////////////////////////////////////////////////
    // AudiereSoundInstance
    ////////////////////////////////////////////////////////////////////////////

    //Clear
    void AudiereSoundInstance::Clear()
    {
        SoundInstance::Clear();
        mStreamPtr = 0;
    }

    //Play
    void AudiereSoundInstance::Play()
    {
        assert( mStreamPtr );
        mStreamPtr->play();
    }

    //Stop
    void AudiereSoundInstance::Stop()
    {
        assert( mStreamPtr );
        mStreamPtr->stop();
    }

    //Length
    float AudiereSoundInstance::Length()
    {
        assert( mStreamPtr );
        return mStreamPtr->getLength();
    }

    ////////////////////////////////////////////////////////////////////////////
    // AudiereAudioSystem
    ////////////////////////////////////////////////////////////////////////////

    AudiereAudioSystem::AudiereAudioSystem()
        : BaseAudioSystem(),
          mDevice( 0 )
    {
        //ctor
    }

    AudiereAudioSystem::~AudiereAudioSystem()
    {
        //dtor
    }

    //Init
    void AudiereAudioSystem::Init()
    {
        mDevice = audiere::AudioDevicePtr( audiere::OpenDevice() );
        assert( mDevice );
    }

    //CreateSound
    int AudiereAudioSystem::CreateSound( const String& fileName, SoundFlags flags )
    {
        assert( mDevice );

        // Make sure the sound has not already been created:
        int index = Find( fileName, flags );
        if ( index != AudioManager::getSingleton().GetInvalidSoundIndex() )
            return index;

        // Create a new sound instance:
        AudiereSoundInstance* instance = new AudiereSoundInstance;
        instance->mFileName = fileName;
        instance->mFlags    = flags;

        // Create the stream:
        bool    isStream = ( flags & SoundFlags_Stream );
        bool    isLoopable = ( flags & SoundFlags_Loopable );
        instance->mStreamPtr = audiere::OutputStreamPtr( audiere::OpenSound( mDevice, fileName.c_str(), isStream ) );
        instance->mStreamPtr->setRepeat( isLoopable );

        // Add the instance to the list:
        mSoundInstances.push_back( SoundInstancePtr( instance ) );
        return mSoundInstances.size() - 1;
    }

    //Play
    void AudiereAudioSystem::Play( int index, int& channelIndex, const Point3Df& pos )
    {
        // Get the instance:
        SoundInstance* instance = GetSoundInstance( index );
        assert( instance );
        instance->Play();
    }

    //Stop
    void AudiereAudioSystem::Stop( int channelIndex )
    {
        // Get the instance:
        SoundInstance* instance = GetSoundInstance( channelIndex );
        assert( instance );
        instance->Stop();
    }

    //GetSoundLength
    float AudiereAudioSystem::GetSoundLength( int index )
    {
        // Get the instance:
        SoundInstance* instance = GetSoundInstance( index );
        assert( instance );
        return instance->Length();
    }

} // namespace PGE
