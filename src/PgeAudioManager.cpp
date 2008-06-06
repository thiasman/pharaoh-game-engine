
/*! $Id$
 *  @file   PgeBaseAudioSystem.h
 *  @author Chad M. Draper
 *  @date   June 6, 2008
 *
 */

#include "PgeAudioManager.h"

namespace PGE
{
    ////////////////////////////////////////////////////////////////////////////
    // SoundInstance
    ////////////////////////////////////////////////////////////////////////////

    //Clear
    void SoundInstance::Clear()
    {
        mFlags = SoundFlags_Invalid;
    }

    ////////////////////////////////////////////////////////////////////////////
    // AudioManager
    ////////////////////////////////////////////////////////////////////////////

    // Instantiate the audio manager:
    AudioManager* AudioManager::mInstance = 0;

    AudioManager::AudioManager()
        : MaxSoundChannels( 200 ),
          InvalidSoundIndex( 0 ),
          InvalidSoundChannel( -1 )
    {
        //ctor
    }

    AudioManager::~AudioManager()
    {
        //dtor
        delete mInstance;
    }

    //Init
    void AudioManager::Init( BaseAudioSystem* audioSys )
    {
        mAudioSystem = AudioSystemPtr( audioSys );
        assert( !mAudioSystem.IsNull() );
        mAudioSystem->Init();
    }

    //CreateSound2D
    int AudioManager::CreateSound2D( const String& fileName, bool loop )
    {
        SoundFlags flags = SoundFlags_2D_Sound;
        if ( loop )
            flags = (SoundFlags)( flags | SoundFlags_Loopable );
        return CreateSound( fileName, flags );
    }

    //CreateSound3D
    int AudioManager::CreateSound3D( const String& fileName, bool loop )
    {
        SoundFlags flags = SoundFlags_3D_Sound;
        if ( loop )
            flags = (SoundFlags)( flags | SoundFlags_Loopable );
        return CreateSound( fileName, flags );
    }

    //CreateStream2D
    int AudioManager::CreateStream2D( const String& fileName, bool loop )
    {
        SoundFlags flags = SoundFlags_2D_Stream;
        if ( loop )
            flags = (SoundFlags)( flags | SoundFlags_Loopable );
        return CreateSound( fileName, flags );
    }

    //CreateStream2D
    int AudioManager::CreateStream3D( const String& fileName, bool loop )
    {
        SoundFlags flags = SoundFlags_3D_Stream;
        if ( loop )
            flags = (SoundFlags)( flags | SoundFlags_Loopable );
        return CreateSound( fileName, flags );
    }

    //CreateSound
    int AudioManager::CreateSound( const String& fileName, SoundFlags flags )
    {
        assert( !mAudioSystem.IsNull() );
        return mAudioSystem->CreateSound( fileName, flags );
    }

    //Play
    void AudioManager::Play( int index, int& channelIndex, const Point3Df& pos )
    {
        assert( !mAudioSystem.IsNull() );
        mAudioSystem->Play( index, channelIndex, pos );
    }

    //Stop
    void AudioManager::Stop( int channelIndex )
    {
        assert( !mAudioSystem.IsNull() );
        mAudioSystem->Stop( channelIndex );
    }

    //StopAll
    void AudioManager::StopAll()
    {
        assert( !mAudioSystem.IsNull() );
        for ( int i = 0; i < MaxSoundChannels; i++ )
        {
            mAudioSystem->Stop( i );
        }
    }

    //Find
    int AudioManager::Find( const String& fileName, SoundFlags flags )
    {
        assert( !mAudioSystem.IsNull() );
        return mAudioSystem->Find( fileName, flags );
    }

    //Set3DRange
    void AudioManager::Set3DRange( int channelIndex, float minDist, float maxDist )
    {
        assert( !mAudioSystem.IsNull() );
        mAudioSystem->Set3DRange( channelIndex, minDist, maxDist );
    }

    //GetSoundLength
    float AudioManager::GetSoundLength( int index )
    {
        assert( !mAudioSystem.IsNull() );
        return mAudioSystem->GetSoundLength( index );
    }

    //GetSoundInstance
    SoundInstance* AudioManager::GetSoundInstance( int index )
    {
        assert( !mAudioSystem.IsNull() );
        return mAudioSystem->GetSoundInstance( index );
    }

    //GetSoundCount
    int AudioManager::GetSoundCount() const
    {
        assert( !mAudioSystem.IsNull() );
        return mAudioSystem->GetSoundCount();
    }

    //getSingleton
    AudioManager& AudioManager::getSingleton()
    {
        if ( !mInstance )
            mInstance = new AudioManager();
        assert( mInstance );
        return *mInstance;
    }
    //getSingletonPtr
    AudioManager* AudioManager::getSingletonPtr()
    {
        if ( !mInstance )
            mInstance = new AudioManager();
        return mInstance;
    }

    ////////////////////////////////////////////////////////////////////////////
    // BaseAudioSystem
    ////////////////////////////////////////////////////////////////////////////

    // Find
    int BaseAudioSystem::Find( const String& fileName, SoundFlags flags )
    {
        // Find the index of the sound instance with the given filename and flags
        SoundInstanceIter iter = mSoundInstances.begin();
        int index = 0;
        while ( iter != mSoundInstances.end() )
        {
            if ( (*iter)->mFileName == fileName && (*iter)->mFlags == flags )
                return index;
            index++;
            iter++;
        }
        return AudioManager::getSingleton().GetInvalidSoundIndex();
    }

    /** Get a pointer to a sound instance */
    SoundInstance* BaseAudioSystem::GetSoundInstance( int index )
    {
        return mSoundInstances.at( index ).Get();
    }

    /** Get the number of sounds in the system */
    int BaseAudioSystem::GetSoundCount() const
    {
        return mSoundInstances.size();
    }

} // namespace PGE
