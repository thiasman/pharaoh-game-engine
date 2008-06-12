
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

    //IsSeekable
    bool AudioManager::IsSeekable( int index ) const
    {
        assert( !mAudioSystem.IsNull() );
        return mAudioSystem->IsSeekable( index );
    }

    //GetSoundLength
    float AudioManager::GetSoundLength( int index )
    {
        assert( !mAudioSystem.IsNull() );
        return mAudioSystem->GetSoundLength( index );
    }

    //GetPosition
    float AudioManager::GetPosition( int index ) const
    {
        assert( !mAudioSystem.IsNull() );
        return mAudioSystem->GetPosition( index );
    }

    //SetPosition
    void AudioManager::SetPosition( int index, float pos )
    {
        assert( !mAudioSystem.IsNull() );
        mAudioSystem->SetPosition( index, pos );
    }

    //Restart
    void AudioManager::Restart( int index )
    {
        assert( !mAudioSystem.IsNull() );
        mAudioSystem->Restart( index );
    }

    //SetRepeat
    void AudioManager::SetRepeat( int index, bool repeat )
    {
        assert( !mAudioSystem.IsNull() );
        mAudioSystem->SetRepeat( index, repeat );
    }

    //GetRepeat
    bool AudioManager::GetRepeat( int index ) const
    {
        assert( !mAudioSystem.IsNull() );
        return mAudioSystem->GetRepeat( index );
    }

    //SetVolume
    void AudioManager::SetVolume( int index, float volume )
    {
        assert( !mAudioSystem.IsNull() );
        mAudioSystem->SetVolume( index, volume );
    }

    //GetVolume
    float AudioManager::GetVolume( int index )
    {
        assert( !mAudioSystem.IsNull() );
        return mAudioSystem->GetVolume( index );
    }

    //SetVolume
    void AudioManager::SetVolume( float volume )
    {
        assert( !mAudioSystem.IsNull() );
        mAudioSystem->SetVolume( volume );
    }

    //MultiplyVolume
    void AudioManager::MultiplyVolume( int index, float ratio )
    {
        assert( !mAudioSystem.IsNull() );
        mAudioSystem->MultiplyVolume( index, ratio );
    }

    //MultiplyVolume
    void AudioManager::MultiplyVolume( float ratio )
    {
        assert( !mAudioSystem.IsNull() );
        mAudioSystem->MultiplyVolume( ratio );
    }

    //SetPan
    void AudioManager::SetPan( int index, float pan )
    {
        assert( !mAudioSystem.IsNull() );
        mAudioSystem->SetPan( index, pan );
    }

    //GetPan
    float AudioManager::GetPan( int index ) const
    {
        assert( !mAudioSystem.IsNull() );
        return mAudioSystem->GetPan( index );
    }

    //SetPitchOffset
    void AudioManager::SetPitchOffset( int index, float pitch )
    {
        assert( !mAudioSystem.IsNull() );
        mAudioSystem->SetPitchOffset( index, pitch );
    }

    //GetPitchOffset
    float AudioManager::GetPitchOffset( int index ) const
    {
        assert( !mAudioSystem.IsNull() );
        return mAudioSystem->GetPitchOffset( index );
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

    //Play
    void BaseAudioSystem::Play( int index, int& channelIndex, const Point3Df& pos )
    {
        // Get the instance:
        SoundInstance* instance = GetSoundInstance( index );
        assert( instance );
        instance->Play();
    }

    //IsPlaying
    bool BaseAudioSystem::IsPlaying( int index ) const
    {
        // Get the instance:
        SoundInstance* instance = mSoundInstances.at( index ).Get();
        //SoundInstance* instance = GetSoundInstance( index );
        assert( instance );
        return instance->IsPlaying();
    }

    //Stop
    void BaseAudioSystem::Stop( int channelIndex )
    {
        // Get the instance:
        SoundInstance* instance = GetSoundInstance( channelIndex );
        assert( instance );
        instance->Stop();
    }

    //IsSeekable
    bool BaseAudioSystem::IsSeekable( int index ) const
    {
        // Get the instance:
        SoundInstance* instance = mSoundInstances.at( index ).Get();
        assert( instance );
        return instance->IsSeekable();
    }

    //GetSoundLength
    float BaseAudioSystem::GetSoundLength( int index )
    {
        // Get the instance:
        SoundInstance* instance = GetSoundInstance( index );
        assert( instance );
        return instance->Length();
    }

    //GetPosition
    float BaseAudioSystem::GetPosition( int index ) const
    {
        // Get the instance:
        SoundInstance* instance = mSoundInstances.at( index ).Get();
        assert( instance );
        return instance->GetPosition();
    }

    //SetPosition
    void BaseAudioSystem::SetPosition( int index, float pos )
    {
        // Get the instance:
        SoundInstance* instance = GetSoundInstance( index );
        assert( instance );
        instance->SetPosition( pos );
    }

    //Restart
    void BaseAudioSystem::Restart( int index )
    {
        // Get the instance:
        SoundInstance* instance = GetSoundInstance( index );
        assert( instance );
        instance->Restart();
    }

    //SetRepeat
    void BaseAudioSystem::SetRepeat( int index, bool repeat )
    {
        // Get the instance:
        SoundInstance* instance = GetSoundInstance( index );
        assert( instance );
        instance->SetRepeat( repeat );
    }

    //GetRepeat
    bool BaseAudioSystem::GetRepeat( int index ) const
    {
        // Get the instance:
        SoundInstance* instance = mSoundInstances.at( index ).Get();
        assert( instance );
        return instance->GetRepeat();
    }

    //SetVolume
    void BaseAudioSystem::SetVolume( int index, float volume )
    {
        // Get the instance:
        SoundInstance* instance = GetSoundInstance( index );
        assert( instance );
        instance->SetVolume( volume );
    }

    //GetVolume
    float BaseAudioSystem::GetVolume( int index )
    {
        // Get the instance:
        SoundInstance* instance = GetSoundInstance( index );
        assert( instance );
        return instance->GetVolume();
    }

    //SetVolume
    void BaseAudioSystem::SetVolume( float volume )
    {
        // Iterate over the sounds and set the volume
        SoundInstanceVector::iterator iter = mSoundInstances.begin();
        while ( iter != mSoundInstances.end() )
        {
            (*iter)->SetVolume( volume );
            ++iter;
        }
    }

    //MultiplyVolume
    void BaseAudioSystem::MultiplyVolume( int index, float ratio )
    {
        // Get the instance:
        SoundInstance* instance = GetSoundInstance( index );
        assert( instance );
        instance->MultiplyVolume( ratio );
    }

    //MultiplyVolume
    void BaseAudioSystem::MultiplyVolume( float ratio )
    {
        // Iterate over the sounds and multiply the volume
        SoundInstanceVector::iterator iter = mSoundInstances.begin();
        while ( iter != mSoundInstances.end() )
        {
            (*iter)->MultiplyVolume( ratio );
            ++iter;
        }
    }

    //SetPan
    void BaseAudioSystem::SetPan( int index, float pan )
    {
        // Get the instance:
        SoundInstance* instance = GetSoundInstance( index );
        assert( instance );
        instance->SetPan( pan );
    }

    //GetPan
    float BaseAudioSystem::GetPan( int index ) const
    {
        // Get the instance:
        SoundInstance* instance = mSoundInstances.at( index ).Get();
        assert( instance );
        instance->GetPan();
    }

    //SetPitchOffset
    void BaseAudioSystem::SetPitchOffset( int index, float pitch )
    {
        // Get the instance:
        SoundInstance* instance = GetSoundInstance( index );
        assert( instance );
        instance->SetPitchOffset( pitch );
    }

    //GetPitchOffset
    float BaseAudioSystem::GetPitchOffset( int index ) const
    {
        // Get the instance:
        SoundInstance* instance = mSoundInstances.at( index ).Get();
        assert( instance );
        instance->GetPitchOffset();
    }

} // namespace PGE
