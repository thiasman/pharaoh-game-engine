
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
#include <map>

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
    class _PgeExport SoundInstance
    {
    public:
        /** Destructor */
        virtual ~SoundInstance()    { }

        /** Reset the instance */
        virtual void    Clear();

        /** Start playing the instance */
        virtual void    Play()      { }

        /** Check if the sound is playing */
        virtual bool    IsPlaying() const   { return false; }

        /** Stop playing the instance */
        virtual void    Stop()      { }

        /** Check if the stream is seekable */
        virtual bool    IsSeekable() const      { return false; }

        /** Get the length of the sound, returning 0 if the stream is not
            seekable.
        */
        virtual float   Length() const          { return 0.0f; }

        /** Get the current position within the stream, if the stream is
            seekable.
        */
        virtual float   GetPosition() const     { return 0; }

        /** Set the position within the stream, if the stream is seekable.
            Otherwise, does nothing.
        */
        virtual void    SetPosition( float pos )    { }

        /** Reset the sound to the beginning.  On seekable streams, this is
            the same as SetPosition( 0 ).
        */
        virtual void    Restart()                   { }

        /** Set the repeat flag, indicating if the sound should loop. */
        virtual void    SetRepeat( bool repeat )    { }

        /** Get the repeat state of the sound */
        virtual bool    GetRepeat() const           { return false; }

        /** Set the volume of the sound */
        virtual void    SetVolume( float volume )   { }

        /** Multiply the volume by a ratio */
        virtual void    MultiplyVolume( float ratio )   { }

        /** Get the volume of the sound */
        virtual float   GetVolume() const   { return 0.0f; }

        /** Set the pan offset.  -1 = left, 0 = center, 1 = right. */
        virtual void    SetPan( float pan )         { }

        /** Get the pan offset. */
        virtual float   GetPan() const              { return 0.0f; }

        /** Set the pitch offset.  Range typically from 0.5 to 2.0, default=1.0. */
        virtual void    SetPitchOffset( float pitch )   { }

        /** Get the pitch offset. */
        virtual float   GetPitchOffset() const      { return 1.0f; }

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
    class _PgeExport AudioManager
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
        void Play( const String& name, int& channelIndex, const Point3Df& pos = Point3Df::ZERO );
        //void Play( int index, int& channelIndex, const Point3Df& pos = Point3Df::ZERO );

        /** Check whether a sound is currently playing */
        bool IsPlaying( const String& name ) const;
        //bool IsPlaying( int index ) const;

        /** Stop a song at a given index */
        void Stop( const String& name );
        //void Stop( int index );

        /** Stop all sounds/streams */
        void StopAll();

        /** Find a song with a given file name that has specified flags. */
        int Find( const String& fileName, SoundFlags flags );

        /** For 3D sounds, set the min and max distance range */
        void Set3DRange( const String& name, float minDist, float maxDist );
        //void Set3DRange( int index, float minDist, float maxDist );

        /** Check if a stream is seekable */
        bool IsSeekable( const String& name ) const;
        //bool IsSeekable( int index ) const;

        /** Get the length of a sound */
        float GetSoundLength( const String& name );
        //float GetSoundLength( int index );

        /** Get the current position within the stream, if the stream is
            seekable.
        */
        float GetPosition( const String& name ) const;
        //float GetPosition( int index ) const;

        /** Set the position within the stream, if the stream is seekable.
            Otherwise, does nothing.
        */
        void SetPosition( const String& name, float pos );
        //void SetPosition( int index, float pos );

        /** Reset the sound to the beginning.  On seekable streams, this is
            the same as SetPosition( 0 ).
        */
        void Restart( const String& name );
        //void Restart( int index );

        /** Set the repeat flag, indicating if the sound should loop. */
        void SetRepeat( const String& name, bool repeat );
        //void SetRepeat( int index, bool repeat );

        /** Get the repeat state of the sound */
        bool GetRepeat( const String& name ) const;
        //bool GetRepeat( int index ) const;

        /** Set the volume of a specific sound */
        void SetVolume( const String& name, float volume );
        //void SetVolume( int index, float volume );
        /** Get the volume of a sound */
        float GetVolume( const String& name );
        //float GetVolume( int index );
        /** Set the volume of <i>ALL</i> sounds */
        void SetVolume( float volume );
        /** Multiply the volume of a sound by a ratio */
        void MultiplyVolume( const String& name, float ratio );
        //void MultiplyVolume( int index, float ratio );
        /** Multiply the volume of <i>ALL</i> sounds by a ratio */
        void MultiplyVolume( float ratio );

        /** Set the pan offset.  -1 = left, 0 = center, 1 = right. */
        void    SetPan( const String& name, float pan );
        //void    SetPan( int index, float pan );
        /** Get the pan offset. */
        float   GetPan( const String& name ) const;
        //float   GetPan( int index ) const;
        /** Set the pitch offset.  Range typically from 0.5 to 2.0, default=1.0. */
        void    SetPitchOffset( const String& name, float pitch );
        //void    SetPitchOffset( int index, float pitch );
        /** Get the pitch offset. */
        float   GetPitchOffset( const String& name ) const;
        //float   GetPitchOffset( int index ) const;

        /** Get a pointer to a sound instance */
        SoundInstance* GetSoundInstance( const String& name );
        //SoundInstance* GetSoundInstance( int index );

        /** Get a constant pointer to a sound instance */
        SoundInstance* GetSoundInstanceConst( const String& name ) const;

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
    class _PgeExport BaseAudioSystem
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
        void Play( const String& name, int& channelIndex, const Point3Df& pos = Point3Df::ZERO );
        //void Play( int index, int& channelIndex, const Point3Df& pos = Point3Df::ZERO );

        /** Check whether a sound is currently playing */
        bool IsPlaying( const String& name ) const;
        //bool IsPlaying( int index ) const;

        /** Stop a song at a given index */
        void Stop( const String& name );
        //void Stop( int index );

        /** Stop all songs */
        void StopAll();

        /** Find a song with a given file name that has specified flags. */
        //int Find( const String& fileName, SoundFlags flags );

        /** For 3D sounds, set the min and max distance range
            @remarks
                Not all audio libraries support 3D sound, so this does nothing
                by default.  It <B>MUST</B> be overridden in order to be useful
                in 3D audio libraries.
        */
        virtual void Set3DRange( const String& name, float minDist, float maxDist ) { }

        /** Check if a stream is seekable */
        bool IsSeekable( const String& name ) const;
        //bool IsSeekable( int index ) const;

        /** Get the length of a sound */
        float GetSoundLength( const String& name );
        //float GetSoundLength( int index );

        /** Get the current position within the stream, if the stream is
            seekable.
        */
        float GetPosition( const String& name ) const;
        //float GetPosition( int index ) const;

        /** Set the position within the stream, if the stream is seekable.
            Otherwise, does nothing.
        */
        void SetPosition( const String& name, float pos );
        //void SetPosition( int index, float pos );

        /** Reset the sound to the beginning.  On seekable streams, this is
            the same as SetPosition( 0 ).
        */
        void Restart( const String& name );
        //void Restart( int index );

        /** Set the repeat flag, indicating if the sound should loop. */
        void SetRepeat( const String& name, bool repeat );
        //void SetRepeat( int index, bool repeat );

        /** Get the repeat state of the sound */
        bool GetRepeat( const String& name ) const;
        //bool GetRepeat( int index ) const;

        /** Set the volume of a specific sound */
        void SetVolume( const String& name, float volume );
        //void SetVolume( int index, float volume );
        /** Get the volume of a sound */
        float GetVolume( const String& name );
        //float GetVolume( int index );
        /** Set the volume of <i>ALL</i> sounds */
        void SetVolume( float volume );
        /** Multiply the volume of a sound by a ratio */
        void MultiplyVolume( const String& name, float ratio );
        //void MultiplyVolume( int index, float ratio );
        /** Multiply the volume of <i>ALL</i> sounds by a ratio */
        void MultiplyVolume( float ratio );

        /** Set the pan offset.  -1 = left, 0 = center, 1 = right. */
        void    SetPan( const String& name, float pan );
        //void    SetPan( int index, float pan );
        /** Get the pan offset. */
        float   GetPan( const String& name ) const;
        //float   GetPan( int index ) const;
        /** Set the pitch offset.  Range typically from 0.5 to 2.0, default=1.0. */
        void    SetPitchOffset( const String& name, float pitch );
        //void    SetPitchOffset( int index, float pitch );
        /** Get the pitch offset. */
        float   GetPitchOffset( const String& name ) const;
        //float   GetPitchOffset( int index ) const;

        /** Get a pointer to a sound instance */
        SoundInstance* GetSoundInstance( const String& name );
        //SoundInstance* GetSoundInstance( int index );

        /** Get a constant pointer to a sound instance */
        SoundInstance* GetSoundInstanceConst( const String& name ) const;

        /** Get the number of sounds in the system */
        int GetSoundCount() const;

    protected:
        typedef SharedPtr< SoundInstance >          SoundInstancePtr;
        typedef std::vector< SoundInstancePtr >     SoundInstanceVector;
        //typedef SoundInstanceVector::iterator       SoundInstanceIter;
        typedef std::map< String, SoundInstancePtr > SoundInstanceMap;
        typedef SoundInstanceMap::iterator          SoundInstanceIter;
        typedef SoundInstanceMap::const_iterator    SoundInstanceConstIter;

        //SoundInstanceVector     mSoundInstances;
        SoundInstanceMap        mSoundInstances;
        Point3Df                mPrevListenerPos;

    }; // class AudioSystemInterface

} // namespace PGE

#endif // PGEAUDIOMANAGER_H
