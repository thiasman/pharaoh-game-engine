
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

    //IsPlaying
    bool AudiereSoundInstance::IsPlaying() const
    {
        assert( mStreamPtr );
        return mStreamPtr->isPlaying();
    }

    //Stop
    void AudiereSoundInstance::Stop()
    {
        assert( mStreamPtr );
        mStreamPtr->stop();
    }

    //IsSeekable
    bool AudiereSoundInstance::IsSeekable() const
    {
        assert( mStreamPtr );
        return mStreamPtr->isSeekable();
    }

    //Length
    float AudiereSoundInstance::Length() const
    {
        assert( mStreamPtr );
        return mStreamPtr->getLength();
    }

    //GetPosition
    float AudiereSoundInstance::GetPosition() const
    {
        assert( mStreamPtr );
        return mStreamPtr->getPosition();
    }

    //SetPosition
    void AudiereSoundInstance::SetPosition( float pos )
    {
        assert( mStreamPtr );
        return mStreamPtr->setPosition( static_cast<int>(pos) );
    }

    //Restart
    void AudiereSoundInstance::Restart()
    {
        assert( mStreamPtr );
        mStreamPtr->reset();
    }

    //SetRepeat
    void AudiereSoundInstance::SetRepeat( bool repeat )
    {
        assert( mStreamPtr );
        mStreamPtr->setRepeat( repeat );
    }

    //GetRepeat
    bool AudiereSoundInstance::GetRepeat() const
    {
        assert( mStreamPtr );
        return mStreamPtr->getRepeat();
    }

    //SetVolume
    void AudiereSoundInstance::SetVolume( float volume )
    {
        assert( mStreamPtr );
        mStreamPtr->setVolume( volume );
    }

    //MultiplyVolume
    void AudiereSoundInstance::MultiplyVolume( float ratio )
    {
        assert( mStreamPtr );
        mStreamPtr->setVolume( ratio * mStreamPtr->getVolume() );
    }

    //GetVolume
    float AudiereSoundInstance::GetVolume() const
    {
        assert( mStreamPtr );
        return mStreamPtr->getVolume();
    }

    //SetPan
    void AudiereSoundInstance::SetPan( float pan )
    {
        assert( mStreamPtr );
        mStreamPtr->setPan( pan );
    }

    //GetPan
    float AudiereSoundInstance::GetPan() const
    {
        assert( mStreamPtr );
        return mStreamPtr->getPan();
    }

    //SetPitchOffset
    void AudiereSoundInstance::SetPitchOffset( float pitch )
    {
        assert( mStreamPtr );
        mStreamPtr->setPitchShift( pitch );
    }

    //GetPitchOffset
    float AudiereSoundInstance::GetPitchOffset() const
    {
        assert( mStreamPtr );
        return mStreamPtr->getPitchShift();
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
        if ( GetSoundInstanceConst( fileName ) )
            return 0;
/*
        // Make sure the sound has not already been created:
        int index = Find( fileName, flags );
        if ( index != AudioManager::getSingleton().GetInvalidSoundIndex() )
            return index;
*/

        // Create a new sound instance:
        AudiereSoundInstance* instance = new AudiereSoundInstance;
        instance->mFileName = fileName;
        instance->mFlags    = flags;

        // Create the stream:
        bool    isStream = ( flags & SoundFlags_Stream );
        bool    isLoopable = ( flags & SoundFlags_Loopable );
        //instance->mStreamPtr = audiere::OutputStreamPtr( audiere::OpenSound( mDevice, fileName.c_str(), isStream ) );
        //AudiereArchiveFile memFile( fileName );

        // Create and open the memory file:
        MemoryFilePtr memFile;
        MemoryFileMap::iterator fileMapIter = mMemoryFiles.find( fileName );
        if ( fileMapIter == mMemoryFiles.end() )
        {
            memFile = MemoryFilePtr( new AudiereArchiveFile( fileName ) );
            mMemoryFiles[ fileName ] = memFile;
        }
        else
            memFile = fileMapIter->second;
        //mMemFile.Open( fileName );
        //instance->mStreamPtr = audiere::OutputStreamPtr( audiere::OpenSound( mDevice, &memFile, isStream, audiere::FF_OGG ) );
        instance->mStreamPtr = audiere::OutputStreamPtr( audiere::OpenSound( mDevice, memFile.Get(), isStream, audiere::FF_AUTODETECT ) );
        //instance->mStreamPtr = audiere::OutputStreamPtr( audiere::OpenSound( mDevice, &mMemFile, isStream, audiere::FF_OGG ) );
        instance->mStreamPtr->setRepeat( isLoopable );

        // Add the instance to the list:
        mSoundInstances[ fileName ] = SoundInstancePtr( instance );
        return mSoundInstances.size() - 1;
    }

} // namespace PGE
