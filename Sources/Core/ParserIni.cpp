#include "ParserIni.hpp"

namespace oe
{

ParserIni::ParserIni()
	: mValues()
	, mFilename("")
{
}

ParserIni::ParserIni(const std::string& filename)
	: mValues()
	, mFilename("")
{
}

bool ParserIni::loadFromFile(const std::string& filename)
{
	IFile file(filename);
	if (file)
	{
		mFilename = filename;
		std::string currentSection = "";
		std::string line;
		while (file.read(line))
		{
			if (line.size() > 0 && line[0] == '[' && line.back() == ']')
			{
				currentSection = line.substr(1, line.size() - 2);
			}
			else
			{
				std::string index;
				std::string value;
				U32 found = line.find_first_of('=');
				if (found != std::string::npos)
				{
					index = line.substr(0, found);
					value = line.substr(found + 1);
					if (!currentSection.empty())
					{
						index.insert(0, 1, ':');
						index.insert(0, currentSection);
					}
					mValues[index] = value;
				}
			}
		}
		file.close();
		return true;
	}
	return false;
}

bool ParserIni::saveToFile(const std::string& filename)
{
	OFile file((!filename.empty()) ? filename : mFilename);
	if (file)
	{
		std::string currentSection("");
		for (auto itr = mValues.begin(); itr != mValues.end(); itr++)
		{
			U32 found(itr->first.find_first_of(':'));
			if (found != std::string::npos)
			{
				std::string section(itr->first.substr(0, found));
				std::string index(itr->first.substr(found + 1));
				if (section != currentSection)
				{
					file << '\n' << '[' << section << ']' << '\n';
					file << index << '=' << itr->second << '\n';
					currentSection = section;
				}
				else
				{
					file << index << '=' << itr->second << '\n';
				}
			}
			else
			{
				file << itr->first << '=' << itr->second << '\n';
			}
		}
		file.close();
		return true;
	}
	return false;
}

void ParserIni::set(const std::string& index, const std::string& value, const std::string& section)
{
	if (!section.empty())
	{
		mValues[index] = value;
	}
	else
	{
		mValues[section + ':' + index] = value;
	}
}

std::string ParserIni::get(const std::string& index, const std::string& section)
{
	if (!section.empty())
	{
		return mValues[index];
	}
	else
	{
		return mValues[section + ':' + index];
	}
}

std::string ParserIni::getKey(U32 index)
{
	U32 i = 0;
	for (auto itr = mValues.begin(); itr != mValues.end(); itr++)
	{
		if (i == index)
		{
			return itr->first;
		}
		i++;
	}
	return "";
}

std::string ParserIni::getValue(U32 index)
{
	U32 i = 0;
	for (auto itr = mValues.begin(); itr != mValues.end(); itr++)
	{
		if (i == index)
		{
			return itr->second;
		}
		i++;
	}
	return "";
}

U32 ParserIni::getSize() const
{
	return mValues.size();
}

const std::string& ParserIni::getFilename() const
{
	return mFilename;
}

} // namespace oe