
/*! $Id$
 *  @file   PgeAudiereAudioSystem.h
 *  @author Chad M. Draper
 *  @date   June 6, 2008
 *  @brief  Audio system using the Audiere library (http://audiere.sourceforge.net)
 *
 */

#ifndef PGEAUDIEREAUDIOSYSTEM_H
#define PGEAUDIEREAUDIOSYSTEM_H

#include "PgeAudioManager.h"

#include "audiere.h"

namespace PGE
{
    /** @class AudiereSoundInstance
        A sound instance that contains the Audiere stream pointer.
    */
    class AudiereSoundInstance : public SoundInstance
    {
    public:
        /** Clear the instance */
        void Clear();

        /** Start playing the instance */
        void    Play();

        /** Check if the sound is playing */
        bool    IsPlaying() const;

        /** Stop playing the instance */
        void    Stop();

        /** Check if the stream is seekable */
        bool    IsSeekable() const;

        /** Get the length of the sound, returning 0 if the stream is not
            seekable.
        */
        float   Length() const;

        /** Get the current position within the stream, if the stream is
            seekable.
        */
        float   GetPosition() const;

        /** Set the position within the stream, if the stream is seekable.
            Otherwise, does nothing.
        */
        void    SetPosition( float pos );

        /** Reset the sound to the beginning.  On seekable streams, this is
            the same as SetPosition( 0 ).
        */
        void    Restart();

        /** Set the repeat flag, indicating if the sound should loop. */
        void    SetRepeat( bool repeat );

        /** Get the repeat state of the sound */
        bool    GetRepeat() const;

        /** Set the volume of the sound */
        void    SetVolume( float volume );

        /** Multiply the volume by a ratio */
        void    MultiplyVolume( float ratio );

        /** Get the volume of the sound */
        float   GetVolume() const;

        /** Set the pan offset.  -1 = left, 0 = center, 1 = right. */
        void    SetPan( float pan );

        /** Get the pan offset. */
        float   GetPan() const;

        /** Set the pitch offset.  Range typically from 0.5 to 2.0, default=1.0. */
        void    SetPitchOffset( float pitch );

        /** Get the pitch offset. */
        float   GetPitchOffset() const;

        audiere::OutputStreamPtr    mStreamPtr; /** Pointer to the stream associated with this instance */
    };

    /** @class AudiereAudioSystem
        A custom audio system, derived from BaseAudioSystem, which uses Audiere
        as the audio engine.

        @remarks
            This class should not be used directly after initializing the audio
            manager via <code>AudioManager::getSingletonPtr()->Initialize( new AudiereAudioSystem() );</code>.
    */
    class AudiereAudioSystem : public BaseAudioSystem
    {
    public:
        /** Constructor */
        AudiereAudioSystem();
        /** Destructor */
        virtual ~AudiereAudioSystem();

        /** Initialize the audio system */
        virtual void Init();

        /** Create a sound, using the flags to define what type it is.
            @remarks
                Audiere does not support 3D audio, so using the 3D sound flags
                will still result in 2D audio.
        */
        virtual int CreateSound( const String& fileName, SoundFlags flags );

    protected:
    private:
        audiere::AudioDevicePtr    mDevice;

    }; // class AudiereAudioSystem

} // namespace PGE

#endif // PGEAUDIEREAUDIOSYSTEM_H
