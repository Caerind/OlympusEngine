#include "Localization.hpp"

namespace oe
{

template<> Localization* Singleton<Localization>::mSingleton = nullptr;

Localization::Localization()
{
}

Localization& Localization::getSingleton()
{
	ASSERT(mSingleton != nullptr);
	return *mSingleton;
}

Localization* Localization::getSingletonPtr()
{
	return mSingleton;
}

void Localization::addLanguage(Language language, LanguageStrategy loadingStrategy)
{
	bool found = false;
	for (U32 i = 0; i < mLanguages.size(); i++)
	{
		if (mLanguages[i].id == language)
		{
			found = true;
		}
	}
	if (!found && loadingStrategy)
	{
		mLanguages.emplace_back(language, loadingStrategy);
	}
}

bool Localization::useLanguage(Language language)
{
	for (U32 i = 0; i < mLanguages.size(); i++)
	{
		if (mLanguages[i].id == language)
		{
			mTokens.clear();
			mCurrentLanguage = language;
			return mLanguages[i].strategy(mTokens);
		}
	}
	return false;
}

Localization::Language Localization::getCurrentLanguage() const
{
	return mCurrentLanguage;
}

const std::string& Localization::getToken(U32 token)
{
	return StringHash::get(mTokens[token]);
}



Localization::LanguageData::LanguageData(Language index, LanguageStrategy loadingStrategy)
	: id(index)
	, strategy(loadingStrategy)
{
}

} // namespace oe