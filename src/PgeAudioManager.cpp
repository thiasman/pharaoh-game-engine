
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
    void AudioManager::Play( const String& name, int& channelIndex, const Point3Df& pos )
    {
        assert( !mAudioSystem.IsNull() );
        mAudioSystem->Play( name, channelIndex, pos );
    }
/*
    void AudioManager::Play( int index, int& channelIndex, const Point3Df& pos )
    {
        assert( !mAudioSystem.IsNull() );
        mAudioSystem->Play( index, channelIndex, pos );
    }
*/

    //IsPlaying
    bool AudioManager::IsPlaying( const String& name ) const
    {
        assert( !mAudioSystem.IsNull() );
        return mAudioSystem->IsPlaying( name );
    }
/*
    bool AudioManager::IsPlaying( int index ) const
    {
        assert( !mAudioSystem.IsNull() );
        return mAudioSystem->IsPlaying( index );
    }
*/

    //Stop
    void AudioManager::Stop( const String& name )
    {
        assert( !mAudioSystem.IsNull() );
        mAudioSystem->Stop( name );
    }
/*
    void AudioManager::Stop( int index )
    {
        assert( !mAudioSystem.IsNull() );
        mAudioSystem->Stop( index );
    }
*/

    //StopAll
    void AudioManager::StopAll()
    {
        assert( !mAudioSystem.IsNull() );
        mAudioSystem->StopAll();
/*
        for ( int i = 0; i < MaxSoundChannels; i++ )
        {
            mAudioSystem->Stop( i );
        }
*/
    }

/*
    //Find
    int AudioManager::Find( const String& fileName, SoundFlags flags )
    {
        assert( !mAudioSystem.IsNull() );
        return mAudioSystem->Find( fileName, flags );
    }
*/

    //Set3DRange
    void AudioManager::Set3DRange( const String& name, float minDist, float maxDist )
    {
        assert( !mAudioSystem.IsNull() );
        mAudioSystem->Set3DRange( name, minDist, maxDist );
    }
/*
    void AudioManager::Set3DRange( int index, float minDist, float maxDist )
    {
        assert( !mAudioSystem.IsNull() );
        mAudioSystem->Set3DRange( index, minDist, maxDist );
    }
*/

    //IsSeekable
    bool AudioManager::IsSeekable( const String& name ) const
    {
        assert( !mAudioSystem.IsNull() );
        return mAudioSystem->IsSeekable( name );
    }
/*
    bool AudioManager::IsSeekable( int index ) const
    {
        assert( !mAudioSystem.IsNull() );
        return mAudioSystem->IsSeekable( index );
    }
*/

    //GetSoundLength
    float AudioManager::GetSoundLength( const String& name )
    {
        assert( !mAudioSystem.IsNull() );
        return mAudioSystem->GetSoundLength( name );
    }
/*
    float AudioManager::GetSoundLength( int index )
    {
        assert( !mAudioSystem.IsNull() );
        return mAudioSystem->GetSoundLength( index );
    }
*/

    //GetPosition
    float AudioManager::GetPosition( const String& name ) const
    {
        assert( !mAudioSystem.IsNull() );
        return mAudioSystem->GetPosition( name );
    }
/*
    float AudioManager::GetPosition( int index ) const
    {
        assert( !mAudioSystem.IsNull() );
        return mAudioSystem->GetPosition( index );
    }
*/

    //SetPosition
    void AudioManager::SetPosition( const String& name, float pos )
    {
        assert( !mAudioSystem.IsNull() );
        mAudioSystem->SetPosition( name, pos );
    }
/*
    void AudioManager::SetPosition( int index, float pos )
    {
        assert( !mAudioSystem.IsNull() );
        mAudioSystem->SetPosition( index, pos );
    }
*/

    //Restart
    void AudioManager::Restart( const String& name )
    {
        assert( !mAudioSystem.IsNull() );
        mAudioSystem->Restart( name );
    }
/*
    void AudioManager::Restart( int index )
    {
        assert( !mAudioSystem.IsNull() );
        mAudioSystem->Restart( index );
    }
*/

    //SetRepeat
    void AudioManager::SetRepeat( const String& name, bool repeat )
    {
        assert( !mAudioSystem.IsNull() );
        mAudioSystem->SetRepeat( name, repeat );
    }
/*
    void AudioManager::SetRepeat( int index, bool repeat )
    {
        assert( !mAudioSystem.IsNull() );
        mAudioSystem->SetRepeat( index, repeat );
    }
*/

    //GetRepeat
    bool AudioManager::GetRepeat( const String& name ) const
    {
        assert( !mAudioSystem.IsNull() );
        return mAudioSystem->GetRepeat( name );
    }
/*
    bool AudioManager::GetRepeat( int index ) const
    {
        assert( !mAudioSystem.IsNull() );
        return mAudioSystem->GetRepeat( index );
    }
*/

    //SetVolume
    void AudioManager::SetVolume( const String& name, float volume )
    {
        assert( !mAudioSystem.IsNull() );
        mAudioSystem->SetVolume( name, volume );
    }
/*
    void AudioManager::SetVolume( int index, float volume )
    {
        assert( !mAudioSystem.IsNull() );
        mAudioSystem->SetVolume( index, volume );
    }
*/

    //GetVolume
    float AudioManager::GetVolume( const String& name )
    {
        assert( !mAudioSystem.IsNull() );
        return mAudioSystem->GetVolume( name );
    }
/*
    float AudioManager::GetVolume( int index )
    {
        assert( !mAudioSystem.IsNull() );
        return mAudioSystem->GetVolume( index );
    }
*/

    //SetVolume
    void AudioManager::SetVolume( float volume )
    {
        assert( !mAudioSystem.IsNull() );
        mAudioSystem->SetVolume( volume );
    }

    //MultiplyVolume
    void AudioManager::MultiplyVolume( const String& name, float ratio )
    {
        assert( !mAudioSystem.IsNull() );
        mAudioSystem->MultiplyVolume( name, ratio );
    }
/*
    void AudioManager::MultiplyVolume( int index, float ratio )
    {
        assert( !mAudioSystem.IsNull() );
        mAudioSystem->MultiplyVolume( index, ratio );
    }
*/

    //MultiplyVolume
    void AudioManager::MultiplyVolume( float ratio )
    {
        assert( !mAudioSystem.IsNull() );
        mAudioSystem->MultiplyVolume( ratio );
    }

    //SetPan
    void AudioManager::SetPan( const String& name, float pan )
    {
        assert( !mAudioSystem.IsNull() );
        mAudioSystem->SetPan( name, pan );
    }
/*
    void AudioManager::SetPan( int index, float pan )
    {
        assert( !mAudioSystem.IsNull() );
        mAudioSystem->SetPan( index, pan );
    }
*/

    //GetPan
    float AudioManager::GetPan( const String& name ) const
    {
        assert( !mAudioSystem.IsNull() );
        return mAudioSystem->GetPan( name );
    }
/*
    float AudioManager::GetPan( int index ) const
    {
        assert( !mAudioSystem.IsNull() );
        return mAudioSystem->GetPan( index );
    }
*/

    //SetPitchOffset
    void AudioManager::SetPitchOffset( const String& name, float pitch )
    {
        assert( !mAudioSystem.IsNull() );
        mAudioSystem->SetPitchOffset( name, pitch );
    }
/*
    void AudioManager::SetPitchOffset( int index, float pitch )
    {
        assert( !mAudioSystem.IsNull() );
        mAudioSystem->SetPitchOffset( index, pitch );
    }
*/

    //GetPitchOffset
    float AudioManager::GetPitchOffset( const String& name ) const
    {
        assert( !mAudioSystem.IsNull() );
        return mAudioSystem->GetPitchOffset( name );
    }
/*
    float AudioManager::GetPitchOffset( int index ) const
    {
        assert( !mAudioSystem.IsNull() );
        return mAudioSystem->GetPitchOffset( index );
    }
*/

    //GetSoundInstance
    SoundInstance* AudioManager::GetSoundInstance( const String& name )
    {
        assert( !mAudioSystem.IsNull() );
        return mAudioSystem->GetSoundInstance( name );
    }
/*
    SoundInstance* AudioManager::GetSoundInstance( int index )
    {
        assert( !mAudioSystem.IsNull() );
        return mAudioSystem->GetSoundInstance( index );
    }
*/

    //GetSoundInstanceConst
    SoundInstance* AudioManager::GetSoundInstanceConst( const String& name ) const
    {
        assert( !mAudioSystem.IsNull() );
        return mAudioSystem->GetSoundInstanceConst( name );
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
/*
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
return 0;
    }
*/

    //GetSoundInstance
    SoundInstance* BaseAudioSystem::GetSoundInstance( const String& name )
    {
        SoundInstanceIter iter = mSoundInstances.find( name );
        if ( iter == mSoundInstances.end() )
            return 0;
        return iter->second.Get();
    }
/*
    SoundInstance* BaseAudioSystem::GetSoundInstance( int index )
    {
        return mSoundInstances.at( index ).Get();
    }
*/

    //GetSoundInstanceConst
    SoundInstance* BaseAudioSystem::GetSoundInstanceConst( const String& name ) const
    {
        SoundInstanceConstIter iter = mSoundInstances.find( name );
        if ( iter == mSoundInstances.end() )
            return 0;
        return iter->second.Get();
    }

    //GetSoundCount
    int BaseAudioSystem::GetSoundCount() const
    {
        return mSoundInstances.size();
    }

    //Play
    void BaseAudioSystem::Play( const String& name, int& channelIndex, const Point3Df& pos )
    {
        // Get the instance:
        SoundInstance* instance = GetSoundInstance( name );
        if ( instance )
            instance->Play();
    }
/*
    void BaseAudioSystem::Play( int index, int& channelIndex, const Point3Df& pos )
    {
        // Get the instance:
        SoundInstance* instance = GetSoundInstance( index );
        assert( instance );
        instance->Play();
    }
*/

    //IsPlaying
    bool BaseAudioSystem::IsPlaying( const String& name ) const
    {
        // Get the instance:
        SoundInstance* instance = GetSoundInstanceConst( name );
        if ( instance )
            return instance->IsPlaying();
        return false;
    }
/*
    bool BaseAudioSystem::IsPlaying( int index ) const
    {
        // Get the instance:
        SoundInstance* instance = mSoundInstances.at( index ).Get();
        //SoundInstance* instance = GetSoundInstance( index );
        assert( instance );
        return instance->IsPlaying();
    }
*/

    //Stop
    void BaseAudioSystem::Stop( const String& name )
    {
        // Get the instance:
        SoundInstance* instance = GetSoundInstance( name );
        if ( instance )
            instance->Stop();
    }
/*
    void BaseAudioSystem::Stop( int index )
    {
        // Get the instance:
        SoundInstance* instance = GetSoundInstance( index );
        assert( instance );
        instance->Stop();
    }
*/

    //StopAll
    void BaseAudioSystem::StopAll()
    {
        SoundInstanceIter iter = mSoundInstances.begin();
        for ( iter; iter != mSoundInstances.end(); iter++ )
        {
            iter->second->Stop();
        }
    }

    //IsSeekable
    bool BaseAudioSystem::IsSeekable( const String& name ) const
    {
        // Get the instance:
        SoundInstance* instance = GetSoundInstanceConst( name );
        if ( instance )
            return instance->IsSeekable();
        return false;
    }
/*
    bool BaseAudioSystem::IsSeekable( int index ) const
    {
        // Get the instance:
        SoundInstance* instance = mSoundInstances.at( index ).Get();
        assert( instance );
        return instance->IsSeekable();
    }
*/

    //GetSoundLength
    float BaseAudioSystem::GetSoundLength( const String& name )
    {
        // Get the instance:
        SoundInstance* instance = GetSoundInstance( name );
        if ( instance )
            return instance->Length();
        return 0.0;
    }
/*
    float BaseAudioSystem::GetSoundLength( int index )
    {
        // Get the instance:
        SoundInstance* instance = GetSoundInstance( index );
        if ( instance )
            return instance->Length();
        return 0.0;
    }
*/

    //GetPosition
    float BaseAudioSystem::GetPosition( const String& name ) const
    {
        // Get the instance:
        SoundInstance* instance = GetSoundInstanceConst( name );
        if ( instance )
            return instance->GetPosition();
        return 0.0;
    }
/*
    float BaseAudioSystem::GetPosition( int index ) const
    {
        // Get the instance:
        SoundInstance* instance = GetSoundInstance( index );
        if ( instance )
            return instance->GetPosition();
        return 0.0;
    }
*/

    //SetPosition
    void BaseAudioSystem::SetPosition( const String& name, float pos )
    {
        // Get the instance:
        SoundInstance* instance = GetSoundInstance( name );
        if ( instance )
            instance->SetPosition( pos );
    }
/*
    void BaseAudioSystem::SetPosition( int index, float pos )
    {
        // Get the instance:
        SoundInstance* instance = GetSoundInstance( index );
        if ( instance )
            instance->SetPosition( pos );
    }
*/

    //Restart
    void BaseAudioSystem::Restart( const String& name )
    {
        // Get the instance:
        SoundInstance* instance = GetSoundInstance( name );
        if ( instance )
            instance->Restart();
    }
/*
    void BaseAudioSystem::Restart( int index )
    {
        // Get the instance:
        SoundInstance* instance = GetSoundInstance( index );
        if ( instance )
            instance->Restart();
    }
*/

    //SetRepeat
    void BaseAudioSystem::SetRepeat( const String& name, bool repeat )
    {
        // Get the instance:
        SoundInstance* instance = GetSoundInstance( name );
        if ( instance )
            instance->SetRepeat( repeat );
    }
/*
    void BaseAudioSystem::SetRepeat( int index, bool repeat )
    {
        // Get the instance:
        SoundInstance* instance = GetSoundInstance( index );
        if ( instance )
            instance->SetRepeat( repeat );
    }
*/

    //GetRepeat
    bool BaseAudioSystem::GetRepeat( const String& name ) const
    {
        // Get the instance:
        SoundInstance* instance = GetSoundInstanceConst( name );
        if ( instance )
            return instance->GetRepeat();
        return false;
    }
/*
    bool BaseAudioSystem::GetRepeat( int index ) const
    {
        // Get the instance:
        SoundInstance* instance = GetSoundInstance( index );
        if ( instance )
            return instance->GetRepeat();
        return false;
    }
*/

    //SetVolume
    void BaseAudioSystem::SetVolume( const String& name, float volume )
    {
        // Get the instance:
        SoundInstance* instance = GetSoundInstance( name );
        if ( instance )
        instance->SetVolume( volume );
    }
/*
    void BaseAudioSystem::SetVolume( int index, float volume )
    {
        // Get the instance:
        SoundInstance* instance = GetSoundInstance( index );
        if ( instance )
        instance->SetVolume( volume );
    }
*/

    //GetVolume
    float BaseAudioSystem::GetVolume( const String& name )
    {
        // Get the instance:
        SoundInstance* instance = GetSoundInstance( name );
        if ( instance )
            return instance->GetVolume();
        return 0.0;
    }
/*
    float BaseAudioSystem::GetVolume( int index )
    {
        // Get the instance:
        SoundInstance* instance = GetSoundInstance( index );
        if ( instance )
            return instance->GetVolume();
        return 0.0;
    }
*/

    //SetVolume
    void BaseAudioSystem::SetVolume( float volume )
    {
        // Iterate over the sounds and set the volume
        SoundInstanceIter iter = mSoundInstances.begin();
        while ( iter != mSoundInstances.end() )
        {
            iter->second->SetVolume( volume );
            //(*iter)->SetVolume( volume );
            ++iter;
        }
    }

    //MultiplyVolume
    void BaseAudioSystem::MultiplyVolume( const String& name, float ratio )
    {
        // Get the instance:
        SoundInstance* instance = GetSoundInstance( name );
        if ( instance )
            instance->MultiplyVolume( ratio );
    }
/*
    void BaseAudioSystem::MultiplyVolume( int index, float ratio )
    {
        // Get the instance:
        SoundInstance* instance = GetSoundInstance( index );
        if ( instance )
            instance->MultiplyVolume( ratio );
    }
*/

    //MultiplyVolume
    void BaseAudioSystem::MultiplyVolume( float ratio )
    {
        // Iterate over the sounds and multiply the volume
        SoundInstanceIter iter = mSoundInstances.begin();
        while ( iter != mSoundInstances.end() )
        {
            iter->second->MultiplyVolume( ratio );
            //(*iter)->MultiplyVolume( ratio );
            ++iter;
        }
    }

    //SetPan
    void BaseAudioSystem::SetPan( const String& name, float pan )
    {
        // Get the instance:
        SoundInstance* instance = GetSoundInstance( name );
        if ( instance )
            instance->SetPan( pan );
    }
/*
    void BaseAudioSystem::SetPan( int index, float pan )
    {
        // Get the instance:
        SoundInstance* instance = GetSoundInstance( index );
        if ( instance )
        instance->SetPan( pan );
    }
*/

    //GetPan
    float BaseAudioSystem::GetPan( const String& name ) const
    {
        // Get the instance:
        SoundInstance* instance = GetSoundInstanceConst( name );
        if ( instance )
            return instance->GetPan();
        return 0.0;
    }
/*
    float BaseAudioSystem::GetPan( int index ) const
    {
        // Get the instance:
        SoundInstance* instance = GetSoundInstance( index );
        if ( instance )
            return instance->GetPan();
        return 0.0;
    }
*/

    //SetPitchOffset
    void BaseAudioSystem::SetPitchOffset( const String& name, float pitch )
    {
        // Get the instance:
        SoundInstance* instance = GetSoundInstance( name );
        if ( instance )
            instance->SetPitchOffset( pitch );
    }
/*
    void BaseAudioSystem::SetPitchOffset( int index, float pitch )
    {
        // Get the instance:
        SoundInstance* instance = GetSoundInstance( index );
        if ( instance )
            instance->SetPitchOffset( pitch );
    }
*/

    //GetPitchOffset
    float BaseAudioSystem::GetPitchOffset( const String& name ) const
    {
        // Get the instance:
        SoundInstance* instance = GetSoundInstanceConst( name );
        if ( instance )
            return instance->GetPitchOffset();
        return 0.0;
    }
/*
    float BaseAudioSystem::GetPitchOffset( int index ) const
    {
        // Get the instance:
        SoundInstance* instance = GetSoundInstance( index );
        if ( instance )
            return instance->GetPitchOffset();
        return 0.0;
    }
*/

} // namespace PGE
