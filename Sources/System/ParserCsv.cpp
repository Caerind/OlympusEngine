#include "ParserCsv.hpp"

namespace oe
{

ParserCsv::ParserCsv(const U32 elementsPerLine)
	: mFilename("")
	, mElementsPerLine(elementsPerLine)
{
}

ParserCsv::ParserCsv(const U32 elementsPerLine, const std::string& filename)
	: mFilename("")
	, mElementsPerLine(elementsPerLine)
{
	loadFromFile(filename);
}

bool ParserCsv::loadFromFile(const std::string& filename)
{
	IFile file(filename);
	if (file)
	{
		mFilename = filename;
		std::string line;
		while (file.read(line))
		{
			std::stringstream ss(line);
			std::string value;
			while (std::getline(ss, value, ';'))
			{
				ss >> value;
				addValue(value);
			}
		}
		file.close();
		return true;
	}
	return false;
}

bool ParserCsv::saveToFile(const std::string& filename)
{
	OFile file((!filename.empty()) ? filename : mFilename);
	if (file)
	{
		for (U32 i = 0; i < mValues.size(); i++)
		{
			if (i != 0 && (i % mElementsPerLine) == 0)
			{
				file << '\n';
			}
			file << mValues[i] << ';';
		}
		file.close();
		return true;
	}
	return false;
}

void ParserCsv::addValue(const std::string& value)
{
	mValues.emplace_back(value);
}

void ParserCsv::setValue(U32 index, const std::string& value)
{
	mValues[index] = value;
}

const std::string& ParserCsv::getValue(U32 index) const
{
	return mValues[index];
}

U32 ParserCsv::getSize() const
{
	return mValues.size();
}

U32 ParserCsv::getElementsPerLine() const
{
	return mElementsPerLine;
}

const std::string& ParserCsv::getFilename() const
{
	return mFilename;
}

} // namespace oe