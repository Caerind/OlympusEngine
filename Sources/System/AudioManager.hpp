#ifndef OE_AUDIOMANAGER_HPP
#define OE_AUDIOMANAGER_HPP

#include "Prerequisites.hpp"
#include "SFMLResources.hpp"

#include <SFML/Audio.hpp>

#include <map>
#include <memory>
#include <vector>

namespace oe
{

class AudioManager
{
    public:
        using MusicPtr = std::shared_ptr<sf::Music>;
        using SoundPtr = std::shared_ptr<sf::Sound>;

    public:
        AudioManager();

		ResourceId createMusic(const std::string& id, const std::string& filename);
		MusicPtr playMusic(ResourceId id, bool loop = true);

		ResourceId createSound(const std::string& id, const std::string& filename);
        SoundPtr playSound(ResourceId id);

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
		SoundHolder mSoundBuffers;

		std::vector<MusicPtr> mMusics;
		std::vector<SoundPtr> mSounds;
        sf::SoundSource::Status mStatus;

        F32 mMusicVolume;
        F32 mSoundVolume;

		static const U32 MAX_MUSIC = 16;
		static const U32 MAX_SOUND = 240;
};

} // namespace oe

#endif // OE_AUDIOMANAGER_HPP
