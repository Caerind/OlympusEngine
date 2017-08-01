#ifndef OE_PARSERXML_HPP
#define OE_PARSERXML_HPP

#include "Prerequisites.hpp"
#include "../ExtLibs/pugixml/pugixml.hpp"

namespace oe
{

class ParserXml
{
	public:
		ParserXml();
		ParserXml(const std::string& filename);

		void newFile();
		bool loadFromFile(const std::string& filename);
		bool saveToFile(const std::string& filename = "");

		bool readNode(const std::string& childName);
		bool nextSibling(const std::string& sibling = "");
		void closeNode();

		bool createChild(const std::string& nodeName);
		bool removeChild(const std::string& nodeName);
		
		void setAttribute(const std::string& attributeName, const std::string& value);
		void getAttribute(const std::string& attributeName, std::string& value);
		void getAttribute(const std::string& attributeName, I32& value);
		void getAttribute(const std::string& attributeName, U32& value);
		void getAttribute(const std::string& attributeName, F32& value);
		void createAttribute(const std::string& attributeName);
		void removeAttribute(const std::string& attributeName);

		void setValue(const std::string& value);
		void getValue(std::string& value);

		const std::string getNodeName() const;

		const std::string& getFilename() const;

		pugi::xml_node mCurrentNode; // TODO : Temp LD

	private:
		std::string mFilename;
		pugi::xml_document mDocument;
};

} // namespace oe

#endif // OE_PARSERXML_HPP