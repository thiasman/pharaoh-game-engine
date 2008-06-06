
/*! $Id$
 *  @file   PgeBaseAudioSystem.h
 *  @author Chad M. Draper
 *  @date   June 6, 2008
 *  @brief  Audio manager.
 *
 */

#ifndef PGEAUDIOMANAGER_H
#define PGEAUDIOMANAGER_H

#include <vector>

#include "PgePlatform.h"
#include "PgeTypes.h"
#include "PgeSharedPtr.h"
#include "PgePoint3D.h"

namespace PGE
{
    class BaseAudioSystem;
    class AudioSystemFactory;

    /** Sound flags */
    enum SoundFlags
    {
        SoundFlags_Invalid  = 0,
        SoundFlags_Loopable = 0x01, // 00000001
        SoundFlags_Stream   = 0x02, // 00000010
        SoundFlags_2D       = 0x04, // 00000100
        SoundFlags_3D       = 0x08, // 00001000

        SoundFlags_2D_Sound             = SoundFlags_2D,
        SoundFlags_3D_Sound             = SoundFlags_3D,
        SoundFlags_2D_Stream            = SoundFlags_2D | SoundFlags_Stream,
        SoundFlags_3D_Stream            = SoundFlags_3D | SoundFlags_Stream,
        SoundFlags_2D_Sound_Loopable    = SoundFlags_2D | SoundFlags_Loopable,
        SoundFlags_3D_Sound_Loopable    = SoundFlags_3D | SoundFlags_Loopable,
        SoundFlags_2D_Stream_Loopable   = SoundFlags_2D | SoundFlags_Stream | SoundFlags_Loopable,
        SoundFlags_3D_Stream_Loopable   = SoundFlags_3D | SoundFlags_Stream | SoundFlags_Loopable,
    };

    /** @class SoundInstance
        An instance of a created sound; stores the filename, flags, etc.

        @remarks
            Chances are, this class will need to be overridden for the audio
            system, in order to add a pointer to the stream.  This can be used
            to start/stop playback of the stream by overridding the Start and
            Stop methods.
    */
    class SoundInstance
    {
    public:
        /** Destructor */
        virtual ~SoundInstance()    { }

        /** Reset the instance */
        virtual void    Clear();

        /** Start playing the instance */
        virtual void    Play()      { }

        /** Stop playing the instance */
        virtual void    Stop()      { }

        /** Get the length of the sound */
        virtual float   Length()    { return 0.0f; }

        String      mFileName;      /**< Name of the audio file */
        SoundFlags  mFlags;         /**< Flags used to initialize the sound */
    }; // class SoundInstance

    /** @class AudioManager
        The audio manager will take care of playing songs and sounds, using the
        application-defined audio library.

        @remarks
            Songs are defined as background music, which will be streamed, and
            sounds are typically short pieces, such as gunshots, which will be
            played then removed.

        @remarks
            The audio manager is a singleton, as it doesn't make sense to have
            multiple instances within a single application.  It can still be
            possible to play multiple sounds at once, however.

        @remarks
            The audio manager is more of a connector between the user and the
            actual audio system.  The audio system will not be known until
            runtime, so there needs to be something that can take the audio
            system factory and use that to play music and sounds.  The developer
            shouldn't have to access the audio system outside of developing a
            custom system.

            <B>USAGE</B>

            Use the audio system and manager like so:

            <code>
                // Initialize the manager:
                AudioManager* audioMgr = AudioManager::getSingletonPtr();
                audioMgr->Initialize( new AudiereAudioSystem() );

                // Play a song:
                int streamIdx = audioMgr->CreateSound2D( "sample.ogg", true );
                audioMgr->Play( streamIdx, streamIdx );
            </code>
    */
    class AudioManager
    {
    private:
        /** Constructor */
        AudioManager();
        AudioManager( const AudioManager& ) { }
        AudioManager& operator=( const AudioManager& );

    public:
        /** Destructor */
        virtual ~AudioManager();

        /** Initialize the audio manager with the desired audio system */
        void Init( BaseAudioSystem* audioSys );

        /** Create a 2D sound
            @param  fileName        Name of the sound file
            @param  loop            If true, the sound will play until manually stopped.  Otherwise, it will just play once.
            @return Index of the sound instance.  Pass this to play the sound.
        */
        int CreateSound2D( const String& fileName, bool loop = false );

        /** Create a 3D sound
            @param  fileName        Name of the sound file
            @param  loop            If true, the sound will play until manually stopped.  Otherwise, it will just play once.
            @return Index of the sound instance.  Pass this to play the sound.
        */
        int CreateSound3D( const String& fileName, bool loop = false );

        /** Create a 2D stream (typically used for background music)
            @param  fileName        Name of the song file
            @param  loop            If true, the song will play until manually stopped.  Otherwise, it will just play once.
            @return Index of the sound instance.  Pass this to play the song.
        */
        int CreateStream2D( const String& fileName, bool loop = false );

        /** Create a 3D stream (typically used for background music)
            @param  fileName        Name of the song file
            @param  loop            If true, the song will play until manually stopped.  Otherwise, it will just play once.
            @return Index of the sound instance.  Pass this to play the song.
        */
        int CreateStream3D( const String& fileName, bool loop = false );

        /** Create a sound, using the flags to define what type it is */
        int CreateSound( const String& fileName, SoundFlags flags );

        /** Play a sound with a given index, using the specified channels.  For
            3D Sounds, this will also set the initial position of the sound.
        */
        void Play( int index, int& channelIndex, const Point3Df& pos = Point3Df::ZERO );

        /** Stop a song at a given index */
        void Stop( int channelIndex );

        /** Stop all sounds/streams */
        void StopAll();

        /** Find a song with a given file name that has specified flags. */
        int Find( const String& fileName, SoundFlags flags );

        /** For 3D sounds, set the min and max distance range */
        void Set3DRange( int channelIndex, float minDist, float maxDist );

        /** Get the length of a sound */
        float GetSoundLength( int index );

        /** Get a pointer to a sound instance */
        SoundInstance* GetSoundInstance( int index );

        /** Get the number of sounds in the system */
        int GetSoundCount() const;

        /** === Inherited from Singleton === */
        static AudioManager& getSingleton();
        static AudioManager* getSingletonPtr();

        /** Set the maximum number of sound channels */
        void SetMaxSoundChannels( int count )   { MaxSoundChannels = count; }
        /** Get the maximum number of sound channels */
        int  GetMaxSoundChannels() const        { return MaxSoundChannels; }

        /** Set the invalid sound index */
        void SetInvalidSoundIndex( int index )  { InvalidSoundIndex = index; }
        /** Get the invalid sound index */
        int  GetInvalidSoundIndex() const       { return InvalidSoundIndex; }

        /** Set the invalid channel */
        void SetInvalidSoundChannel( int index ){ InvalidSoundChannel = index; }
        /** Get the invalid channel */
        int  GetInvalidSoundChannel() const     { return InvalidSoundChannel; }

    protected:

    private:
        static AudioManager* mInstance;

        typedef SharedPtr< BaseAudioSystem > AudioSystemPtr;
        AudioSystemPtr  mAudioSystem;

        int MaxSoundChannels;
        int InvalidSoundIndex;
        int InvalidSoundChannel;

    }; // class AudioManager

    /** @class BaseAudioSystem
        Defines the interface for the audio system.

        @remarks
            Subclass this interface to add a new audio system to the application.
            For instance, you can use OpenAL, fmod, Audiere, etc. by implementing
            the approptiate methods in a derived class, and providing a factory
            to generate the audio system.
    */
    class BaseAudioSystem
    {
    public:
        /** Constructor */
        BaseAudioSystem()              { }
        /** Destructor */
        virtual ~BaseAudioSystem()     { }

        /** Initialize the audio system */
        virtual void Init() = 0;

        /** Create a sound, using the flags to define what type it is */
        virtual int CreateSound( const String& fileName, SoundFlags flags ) = 0;

        /** Play a sound with a given index, using the specified channels.  For
            3D Sounds, this will also set the initial position of the sound.
        */
        virtual void Play( int index, int& channelIndex, const Point3Df& pos = Point3Df::ZERO ) = 0;

        /** Stop a song at a given index */
        virtual void Stop( int channelIndex ) = 0;

        /** Find a song with a given file name that has specified flags. */
        int Find( const String& fileName, SoundFlags flags );

        /** For 3D sounds, set the min and max distance range
            @remarks
                Not all audio libraries support 3D sound, so this does nothing
                by default.  It <B>MUST</B> be overridden in order to be useful
                in 3D audio libraries.
        */
        virtual void Set3DRange( int channelIndex, float minDist, float maxDist ) { }

        /** Get the length of a sound */
        virtual float GetSoundLength( int index ) = 0;

        /** Get a pointer to a sound instance */
        SoundInstance* GetSoundInstance( int index );

        /** Get the number of sounds in the system */
        int GetSoundCount() const;

    protected:
        typedef SharedPtr< SoundInstance >          SoundInstancePtr;
        typedef std::vector< SoundInstancePtr >     SoundInstanceVector;
        typedef SoundInstanceVector::iterator       SoundInstanceIter;

        SoundInstanceVector     mSoundInstances;
        Point3Df                mPrevListenerPos;

    }; // class AudioSystemInterface

} // namespace PGE

#endif // PGEAUDIOMANAGER_H
