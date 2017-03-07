#ifndef OE_PARSERPURE_HPP
#define OE_PARSERPURE_HPP

#include "Prerequisites.hpp"
#include "File.hpp"

namespace oe
{

class ParserPure
{
	public:
		ParserPure();
		ParserPure(const std::string& filename);

		bool loadFromFile(const std::string& filename);
		bool saveToFile(const std::string& filename = "");

		void set(const std::string& name, const std::string& value);
		const std::string& get(const std::string& name) const;

		const std::string& getFilename() const;

	private:
		class PureProperty
		{
			public:
				PureProperty();
				PureProperty(const std::string& name);
				PureProperty(const std::string& name, const std::string& value);

				void set(const std::string& name, const std::string& value);
				const std::string& get(const std::string& name) const;

				void write(OFile& file, U32 space) const;

				const std::string& getName() const;
				const std::string& getValue() const;

			protected:
				std::string mName;
				std::string mValue;
				std::vector<PureProperty> mProperties;
		};

		std::vector<PureProperty> mProperties;
		std::string mFilename;
		
		static const std::string mEmpty;
};

} // namespace oe

#endif // OE_PARSERPURE_HPP
