#ifndef OE_PARSERINI_HPP
#define OE_PARSERINI_HPP

#include "Prerequisites.hpp"
#include "File.hpp"
#include <map>

namespace oe
{

class ParserIni
{
	public:
		ParserIni();
		ParserIni(const std::string& filename);

		bool loadFromFile(const std::string& filename);
		bool saveToFile(const std::string& filename = "");
		
		void set(const std::string& index, const std::string& value, const std::string& section = "");
		std::string get(const std::string& index, const std::string& section = "");

		std::string getKey(U32 index);
		std::string getValue(U32 index);
		U32 getSize() const;

		const std::string& getFilename() const;

	private:
		std::map<std::string, std::string> mValues;
		std::string mFilename;
};

} // namespace oe

#endif // OE_PARSERINI_HPP
