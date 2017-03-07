#include "ParserPure.hpp"

namespace oe
{

const std::string ParserPure::mEmpty("");

ParserPure::ParserPure()
	: mProperties()
	, mFilename("")
{
}

ParserPure::ParserPure(const std::string& filename)
	: mProperties()
	, mFilename("")
{
	loadFromFile(filename);
}

bool ParserPure::loadFromFile(const std::string& filename)
{
	IFile file(filename);
	if (file)
	{
		mFilename = filename;
		std::string line;
		U32 space;
		U32 actualSpace(0);
		std::string actualProperty("");
		while (file.read(line))
		{
			// Remove and count spaces
			space = 0;
			for (U32 i = 0; i < line.size(); ++i)
			{
				if (line[i] == ' ')
				{
					++space;
				}
				else if (line[i] == '\t')
				{
					space += 4;
				}
				else
				{
					break;
				}
			}
			line = line.substr(space);

			// Ignore if empty or comment
			if (line.size() == 0 || line[0] == '#')
			{
				continue;
			}

			// Handle specific case
			if (space == 0)
			{
				actualProperty.clear();
				actualSpace = 0;
			}

			// Get back on the chain of properties
			while (space <= actualSpace && actualSpace > 0)
			{
				std::size_t found2(actualProperty.find_last_of('.'));
				if (found2 == std::string::npos)
				{
					actualProperty.clear();
					actualSpace = 0;
				}
				else
				{
					actualProperty = actualProperty.substr(0, found2);
					actualSpace = (actualSpace >= 4) ? actualSpace - 4 : 0;
				}
			}

			// Try to find if the line has a value
			std::size_t found(line.find_first_of(" = "));
			if (found != std::string::npos)
			{
				// If the line has a value
				std::string name(line.substr(0, found));
				std::string value(line.substr(found + 3));
				std::size_t found2(line.find_first_of('.'));
				if (found2 == std::string::npos && !actualProperty.empty()) // Normal case
				{
					set(actualProperty + "." + name, value);
				}
				else // Case with "class.value = 10" or empty actualProperty
				{
					set(name, value);
				}
			}
			else
			{
				// Update the chain property
				actualSpace = space;
				if (actualProperty.size() != 0)
				{
					actualProperty += ".";
				}
				actualProperty += line;
			}
		}

		file.close();
		return true;
	}
	return false;
}

bool ParserPure::saveToFile(const std::string& filename)
{
	OFile file(((!filename.empty()) ? mFilename : filename));
	if (file)
	{
		for (const PureProperty& p : mProperties)
		{
			p.write(file, 0);
			file << '\n';
		}
		file.close();
		return true;
	}
	return false;
}

void ParserPure::set(const std::string& name, const std::string& value)
{
	if (!name.empty())
	{
		std::string pname(name);
		std::string subname("");
		std::size_t found(name.find_first_of('.'));
		if (found != std::string::npos)
		{
			pname = name.substr(0, found);
			subname = name.substr(found + 1);
		}
		bool f = false;
		for (PureProperty& p : mProperties)
		{
			if (!f && p.getName() == pname)
			{
				p.set(subname, value);
				f = true;
			}
		}
		if (!f)
		{
			PureProperty p(pname);
			p.set(subname, value);
			mProperties.push_back(p);
		}
	}
}

const std::string& ParserPure::get(const std::string& name) const
{
	if (!name.empty())
	{
		std::string pname(name);
		std::string subname("");
		std::size_t found(name.find_first_of('.'));
		if (found != std::string::npos)
		{
			pname = name.substr(0, found);
			subname = name.substr(found + 1);
		}
		for (const PureProperty& p : mProperties)
		{
			if (p.getName() == pname)
			{
				return p.get(subname);
			}
		}
	}
	return mEmpty;
}

const std::string& ParserPure::getFilename() const
{
	return mFilename;
}

ParserPure::PureProperty::PureProperty()
	: mName("")
	, mValue("")
{
}

ParserPure::PureProperty::PureProperty(const std::string& name)
	: mName(name)
	, mValue("")
{
}

ParserPure::PureProperty::PureProperty(const std::string& name, const std::string& value)
	: mName(name)
	, mValue(value)
{
}

void ParserPure::PureProperty::set(const std::string& name, const std::string& value)
{
	if (!name.empty())
	{
		std::string pname(name);
		std::string subname("");
		std::size_t found(name.find_first_of('.'));
		if (found != std::string::npos)
		{
			pname = name.substr(0, found);
			subname = name.substr(found + 1);
		}
		bool f = false;
		for (PureProperty& p : mProperties)
		{
			if (!f && p.mName == pname)
			{
				p.set(subname, value);
				f = true;
			}
		}
		if (!f)
		{
			PureProperty p(pname);
			p.set(subname, value);
			mProperties.push_back(p);
		}
	}
	else
	{
		mValue = value;
	}
}

const std::string& ParserPure::PureProperty::get(const std::string& name) const
{
	if (!name.empty())
	{
		std::string pname(name);
		std::string subname("");
		std::size_t found(name.find_first_of('.'));
		if (found != std::string::npos)
		{
			pname = name.substr(0, found);
			subname = name.substr(found + 1);
		}
		for (const PureProperty& p : mProperties)
		{
			if (p.mName == pname)
			{
				return p.get(subname);
			}
		}
	}
	return mValue;
}

void ParserPure::PureProperty::write(OFile& file, U32 space) const
{
	for (U32 i = 0; i < space; ++i)
	{
		file << " ";
	}
	file << mName;
	if (!mValue.empty())
	{
		file << " = " << mValue;
	}
	file << '\n';
	for (const PureProperty& p : mProperties)
	{
		p.write(file, space + 4);
	}
}

const std::string& ParserPure::PureProperty::getName() const
{
	return mName;
}

const std::string& ParserPure::PureProperty::getValue() const
{
	return mValue;
}

} // namespace oe