
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

        /** Stop playing the instance */
        void    Stop();

        /** Get the length of the sound */
        float   Length();

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

        /** Play a sound with a given index, using the specified channels.  For
            3D Sounds, this will also set the initial position of the sound.
        */
        virtual void Play( int index, int& channelIndex, const Point3Df& pos = Point3Df::ZERO );

        /** Stop a song at a given index */
        virtual void Stop( int channelIndex );

        /** Get the length of a sound */
        virtual float GetSoundLength( int index );

    protected:
    private:
        audiere::AudioDevicePtr    mDevice;

    }; // class AudiereAudioSystem

} // namespace PGE

#endif // PGEAUDIEREAUDIOSYSTEM_H
