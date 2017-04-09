#include "AudioManager.hpp"

namespace oe
{

AudioManager::AudioManager()
	: mStatus(sf::SoundSource::Playing)
	, mMusicVolume(100.0f)
	, mSoundVolume(100.0f)
{
}

ResourceId AudioManager::createMusic(const std::string& id, const std::string& filename)
{
	ResourceId index(StringHash::hash(id));
	if (mMusicFilenames.find(index) == mMusicFilenames.end())
	{
		mMusicFilenames[index] = filename;
	}
	return index;
}

AudioManager::MusicPtr AudioManager::playMusic(ResourceId id, bool loop)
{
    if (mStatus != sf::SoundSource::Stopped && mMusicFilenames.find(id) != mMusicFilenames.end() && mMusics.size() < MAX_MUSIC)
    {
		MusicPtr m(std::make_shared<sf::Music>());
		mMusics.push_back(m);
		m->openFromFile(mMusicFilenames[id]);
        m->setLoop(loop);
        m->setVolume(mMusicVolume);
        m->play();
        if (mStatus == sf::SoundSource::Paused)
        {
            m->pause();
        }
        return m;
    }
    return nullptr;
}

ResourceId AudioManager::createSound(const std::string& id, const std::string& filename)
{
	return mSoundBuffers.create(id, filename);
}

AudioManager::SoundPtr AudioManager::playSound(ResourceId id)
{
    if (mStatus != sf::SoundSource::Stopped && mSoundBuffers.has(id) && mSounds.size() < MAX_SOUND)
    {
		SoundPtr s(std::make_shared<sf::Sound>());
        mSounds.push_back(s);
        s->setBuffer(mSoundBuffers.get(id));
        s->setVolume(mSoundVolume);
        s->play();
        if (mStatus == sf::SoundSource::Paused)
        {
            s->pause();
        }
        return s;
    }
    return nullptr;
}

void AudioManager::play()
{
    if (mStatus == sf::SoundSource::Paused)
    {
        update();
        for (auto itr = mMusics.begin(); itr != mMusics.end(); ++itr)
        {
            (*itr)->play();
        }
        for (auto itr = mSounds.begin(); itr != mSounds.end(); ++itr)
        {
            (*itr)->play();
        }
        mStatus = sf::SoundSource::Playing;
    }
}

void AudioManager::pause()
{
    if (mStatus == sf::SoundSource::Playing)
    {
        update();
        for (auto itr = mMusics.begin(); itr != mMusics.end(); ++itr)
        {
            (*itr)->pause();
        }
        for (auto itr = mSounds.begin(); itr != mSounds.end(); ++itr)
        {
            (*itr)->pause();
        }
        mStatus = sf::SoundSource::Paused;
    }
}

void AudioManager::stop()
{
    if (mStatus != sf::SoundSource::Stopped)
    {
        mMusics.clear();
        mSounds.clear();
    }
}

void AudioManager::update()
{
    for (auto itr = mMusics.begin(); itr != mMusics.end();)
    {
        if (mStatus != sf::SoundSource::Stopped && (*itr)->getStatus() == sf::SoundSource::Stopped)
        {
            itr = mMusics.erase(itr);
        }
        else
        {
            ++itr;
        }
    }
    for (auto itr = mSounds.begin(); itr != mSounds.end();)
    {
        if (mStatus != sf::SoundSource::Stopped && (*itr)->getStatus() == sf::SoundSource::Stopped)
        {
            itr = mSounds.erase(itr);
        }
        else
        {
            ++itr;
        }
    }
}

void AudioManager::setGlobalVolume(F32 volume)
{
    sf::Listener::setGlobalVolume(volume);
}

void AudioManager::setMusicVolume(F32 volume)
{
    mMusicVolume = volume;
    for (auto itr = mMusics.begin(); itr != mMusics.end(); ++itr)
    {
        (*itr)->setVolume(volume);
    }
}

void AudioManager::setSoundVolume(F32 volume)
{
    mSoundVolume = volume;
    for (auto itr = mSounds.begin(); itr != mSounds.end(); ++itr)
    {
        (*itr)->setVolume(volume);
    }
}

F32 AudioManager::getGlobalVolume() const
{
	return sf::Listener::getGlobalVolume();
}

F32 AudioManager::getMusicVolume() const
{
    return mMusicVolume;
}

F32 AudioManager::getSoundVolume() const
{
    return mSoundVolume;
}

sf::SoundSource::Status AudioManager::getStatus() const
{
    return mStatus;
}

} // namespace oe