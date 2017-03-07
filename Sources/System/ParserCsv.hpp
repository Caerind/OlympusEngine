#ifndef OE_PARSERCSV_HPP
#define OE_PARSERCSV_HPP

#include "Prerequisites.hpp"
#include "File.hpp"
#include <vector>

namespace oe
{

class ParserCsv
{
	public:
		ParserCsv(const U32 elementsPerLine);
		ParserCsv(const U32 elementsPerLine, const std::string& filename);

		bool loadFromFile(const std::string& filename);
		bool saveToFile(const std::string& filename = "");

		void addValue(const std::string& value);
		void setValue(U32 index, const std::string& value);
		const std::string& getValue(U32 index) const;
		U32 getSize() const;

		U32 getElementsPerLine() const;

		const std::string& getFilename() const;

	private:
		std::vector<std::string> mValues;
		std::string mFilename;
		const U32 mElementsPerLine;
};

} // namespace oe

#endif // OE_PARSERCSV_HPP
