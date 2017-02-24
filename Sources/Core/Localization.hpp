#ifndef OE_LOCALIZATION_HPP
#define OE_LOCALIZATION_HPP

#include "Prerequisites.hpp"
#include "Singleton.hpp"

#include <functional>
#include <vector>

namespace oe
{

class Localization : public Singleton<Localization>
{
	public:
		enum class Language : U8
		{
			English = 0,
			French = 1,
			Spanish = 2
		};

		class LanguageTable
		{
			public:
				LanguageTable();

				void add(const std::string& string);

				StringId at(U32 index) const;

				U32 size() const;

				void clear();

			private:
				std::vector<StringId> mTable;
		};

		using LanguageStrategy = std::function<bool(LanguageTable& table)>;
		
	public:
		Localization();

		static Localization& getSingleton();
		static Localization* getSingletonPtr();

		void addLanguage(Language language, LanguageStrategy loadingStrategy);
		bool useLanguage(Language language, LanguageStrategy loadingStrategy);
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
