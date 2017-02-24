#include "Localization.hpp"
#include "ParserIni.hpp"

namespace oe
{

template<> Localization* Singleton<Localization>::mSingleton = nullptr;

Localization::Localization()
	: mLanguages()
	, mTokens()
	, mCurrentLanguage(Language::English)
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

bool Localization::useLanguage(Language language, LanguageStrategy loadingStrategy)
{
	mTokens.clear();
	mCurrentLanguage = language;
	for (U32 i = 0; i < mLanguages.size(); i++)
	{
		if (mLanguages[i].id == language)
		{
			return mLanguages[i].strategy(mTokens);
		}
	}
	if (loadingStrategy)
	{
		mLanguages.emplace_back(language, loadingStrategy);
		return mLanguages.back().strategy(mTokens);
	}
	return false;
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
	return StringHash::get(mTokens.at(token));
}

bool Localization::loadLanguageFromFile(LanguageTable& table, const std::string& filename)
{
	ParserIni iniParser;
	if (iniParser.loadFromFile(filename))
	{
		U32 size = iniParser.getSize();
		for (U32 i = 0; i < size; i++)
		{
			table.add(iniParser.getValue(i));
		}
		return true;
	}
	return false;
}

Localization::LanguageData::LanguageData(Language index, LanguageStrategy loadingStrategy)
	: id(index)
	, strategy(loadingStrategy)
{
}

Localization::LanguageTable::LanguageTable()
{
}

void Localization::LanguageTable::add(const std::string& string)
{
	mTable.push_back(StringHash::hash(string));
}

StringId Localization::LanguageTable::at(U32 index) const
{
	return mTable[index];
}

U32 Localization::LanguageTable::size() const
{
	return mTable.size();
}

void Localization::LanguageTable::clear()
{
	mTable.clear();
}

} // namespace oe