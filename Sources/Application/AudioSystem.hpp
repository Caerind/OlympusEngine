#ifndef OE_AUDIOSYSTEM_HPP
#define OE_AUDIOSYSTEM_HPP

#include <SFML/Audio.hpp>

#include <map>
#include <memory>
#include <vector>

#include "../System/Prerequisites.hpp"

#include "../Graphics/SFMLResources.hpp"

namespace oe
{

class AudioSystem
{
    public:
        using MusicPtr = std::shared_ptr<sf::Music>;
        using SoundPtr = std::shared_ptr<sf::Sound>;

    public:
        AudioSystem();

		ResourceId createMusic(const std::string& id, const std::string& filename);
		MusicPtr playMusic(ResourceId id, bool loop = true);
		MusicPtr playMusic(const std::string& id, bool loop = true);

		ResourceId createSound(const std::string& id, const std::string& filename);
        SoundPtr playSound(ResourceId id);
		SoundPtr playSound(const std::string& id);

        void play();
        void pause();
        void stop();

        void update();

        void setGlobalVolume(F32 volume);
        void setMusicVolume(F32 volume);
        void setSoundVolume(F32 volume);
        F32 getGlobalVolume() const;
        F32 getMusicVolume() const;
        F32 getSoundVolume() const;

        sf::SoundSource::Status getStatus() const;

    private:
		std::map<ResourceId, std::string> mMusicFilenames;
		SoundManager mSoundBuffers;

		std::vector<MusicPtr> mMusics;
		std::vector<SoundPtr> mSounds;
        sf::SoundSource::Status mStatus;

        F32 mMusicVolume;
        F32 mSoundVolume;

		static const U32 MAX_MUSIC = 16;
		static const U32 MAX_SOUND = 240;
};

} // namespace oe

#endif // OE_AUDIOSYSTEM_HPP
