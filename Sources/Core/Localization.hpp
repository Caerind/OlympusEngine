#ifndef OE_LOCALIZATION_HPP
#define OE_LOCALIZATION_HPP

#include "../Config.hpp"
#include "Singleton.hpp"
#include "String.hpp"

#include <functional>
#include <vector>

namespace oe
{

class OE_API Localization : public Singleton<Localization>
{
	public:
		enum class Language : U8
		{
			English = 0,
			French = 1,
		};

		using LanguageTable = std::vector<StringId>;
		using LanguageStrategy = std::function<bool(LanguageTable& table)>;
		
	public:
		Localization();

		static Localization& getSingleton();
		static Localization* getSingletonPtr();

		void addLanguage(Language language, LanguageStrategy loadingStrategy);
		bool useLanguage(Language language);
		
		Language getCurrentLanguage() const;
		const std::string& getToken(U32 token);

		static bool loadLanguageFromFile(LanguageTable& table, const std::string& filename);

	private:
		struct LanguageData
		{
			LanguageData(Language index, LanguageStrategy loadingStrategy);
			Language id;
			LanguageStrategy strategy;
		};
		
	private:
		std::vector<LanguageData> mLanguages;
		LanguageTable mTokens;
		Language mCurrentLanguage;
};

} // namespace oe

#endif // OE_LOCALIZATION_HPP
