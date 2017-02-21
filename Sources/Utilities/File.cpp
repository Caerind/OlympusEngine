#include "File.hpp"

#include "../ExtLibs/dirent.h"

namespace oe
{

bool Path::isDirectory(std::string path)
{
	return extractName(path);
}

std::string Path::getDirectoryName(std::string path)
{
	return (extractName(path)) ? path : "";
}

std::vector<std::string> Path::getDirectoryList(std::string path)
{
	std::vector<std::string> ret;
	unify(path);
	DIR* dir = opendir(path.c_str());
	if (dir != nullptr)
	{
		std::string name;
		dirent* file = nullptr;
		while ((file = readdir(dir)) != nullptr)
		{
			ret.push_back(file->d_name);
		}
	}
	return ret;
}

bool Path::isFile(std::string path)
{
	return !isDirectory(path);
}

std::string Path::getFileName(std::string path)
{
	if (!extractName(path))
	{
		if (path.size() > 0 && path[0] == '.')
		{
			path.erase(0, 1);
		}
		std::size_t found = path.find_first_of('.');
		return (found != std::string::npos) ? path.substr(0, found) : path;
	}
	return false;
}

std::string Path::getExtesionName(std::string path)
{
	if (!extractName(path))
	{
		if (path.size() > 0 && path[0] == '.')
		{
			path.erase(0, 1);
		}
		std::size_t found = path.find_first_of('.');
		return (found != std::string::npos) ? path.substr(found + 1) : "";
	}
	return false;
}

void Path::unify(std::string& path)
{
	if (path.size() == 0)
	{
		return;
	}

	std::size_t found;

	// Remove Windows two backslashes
	do
	{
		found = path.find('\\');
		if (found != std::string::npos)
		{
			path[found] = '/';
		}
	} while (found != std::string::npos);

	// Remove Apple colon
	do
	{
		found = path.find(':');
		if (found != std::string::npos)
		{
			path[found] = '/';
		}
	} while (found != std::string::npos);
	// Detect if we removed a Windows disk
	if (path.size() >= 2 && path[1] == '/' && (path[0] == 'C' || path[0] == 'D'))
	{
		path.insert(1, 1, ':');
	}

	removeDouble(path);
	removeCurrent(path);
	removeBack(path);
	removeEnd(path);
}

std::string Path::getUnified(std::string path)
{
	unify(path);
	return path;
}

bool Path::extractName(std::string& path)
{
	unify(path);
	std::size_t found = path.find_last_of('/');
	if (found != std::string::npos)
	{
		path.erase(0, found + 1);
	}
	return (path.find('.') == std::string::npos);
}

void Path::removeDouble(std::string& path)
{
	std::size_t found;
	do
	{
		found = path.find("//");
		if (found != std::string::npos)
		{
			path.erase(found, 1);
		}
	} while (found != std::string::npos);
}

void Path::removeCurrent(std::string& path)
{
	std::size_t found;
	do
	{
		found = path.find("/./");
		if (found != std::string::npos)
		{
			path.erase(found + 1, 2);
		}
	} while (found != std::string::npos);
	if (path.size() > 1 && path[0] == '.' && path[1] == '/')
	{
		path.erase(0, 2);
	}
	if (path.size() > 1 && path.back() == '.' && path[path.size() - 2] == '/')
	{
		path.pop_back();
	}
	if (path.size() == 1 && path[0] == '.')
	{
		path = "";
	}
}

void Path::removeBack(std::string& path)
{
	bool changed;
	do
	{
		changed = false;
		for (std::size_t i = path.size() - 3; i > 1 && path.size() > 4; i--)
		{
			if (path[i - 1] == '/' && path[i] == '.' && path[i + 1] == '.' && path[i + 2] == '/')
			{
				if (path[i - 2] == ':')
				{
					// case C:/../ : handle
					path.erase(i, 3);
					changed = true;
				}
				else if (path[i - 2] == '.' && path[i - 3] == '.')
				{
					// case ../../ : ignore
				}
				else
				{
					// case ab/../ : erase
					i--;
					path.erase(i, 4);
					i--;
					while (path[i] != '/' && i > 0)
					{
						path.erase(i, 1);
						i--;
					}
					if (i == 0 && path[0] != '/')
					{
						path.erase(0, 1);
					}
					changed = true;
					i++;
				}
			}
		}
	} while (changed);
	if (path.size() >= 3 && path.back() == '.' && path[path.size() - 2] == '.' && path[path.size() - 3] == '/')
	{
		char c = path[path.size() - 4];
		if (path.size() >= 4 && path[path.size() - 4] == ':')
		{
			// case C:/.. : handle
			path.pop_back();
			path.pop_back();
		}
		else if (path.size() >= 5 && path[path.size() - 4] == '.' && path[path.size() - 5] == '.')
		{
			// case ../.. : ignore
		}
		else if (path.size() == 3)
		{
			// case /.. : handle
			path.pop_back();
			path.pop_back();
		}
		else
		{
			// case ab/.. : erase
			std::size_t i = path.size() - 3;
			path.erase(i, 4);
			i--;
			while (path[i] != '/' && i > 0)
			{
				path.erase(i, 1);
				i--;
			}
			if (i == 0 && path[0] != '/')
			{
				path.erase(0, 1);
			}
		}
	}
}

void Path::removeEnd(std::string& path)
{
	if (path.size() >= 2 && path.back() == '/' && path[path.size() - 2] == ':')
	{
		// Do nothing : handle C:/ D:/
	}
	else if (path.size() >= 1 && path.back() == '/')
	{
		path.pop_back(); // remove '/'
	}
}

bool File::exists(const std::string& filename)
{
	std::ifstream file(filename);
	if (file) 
	{
		file.close();
		return true;
	}
	return false;
}

bool File::remove(const std::string& filename)
{
	return std::remove(filename.c_str()) == 0;
}

bool File::rename(const std::string& oldFilename, const std::string& newFilename)
{
	return std::rename(oldFilename.c_str(), newFilename.c_str()) == 0;
}

IFile::IFile()
{
}

IFile::IFile(const std::string& filename)
{
	open(filename);
}

IFile::~IFile()
{
	mFile.close();
}

bool IFile::open(const std::string& filename)
{
	if (mFile.is_open())
	{
		mFile.close();
	}
	mFile.open(filename);
	if (mFile.is_open())
	{
		mFilename = filename;
		return true;
	}
	return false;
}

bool IFile::isOpen() const
{
	return mFile.is_open();
}

IFile::operator bool() const
{
	return isOpen();
}

void IFile::close()
{
	mFile.close();
	mFilename = "";
}

const std::string& IFile::getFilename() const
{
	return mFilename;
}

bool IFile::read(std::string& line)
{
	if (mFile.is_open())
	{
		return static_cast<bool>(std::getline(mFile, line));
	}
	return false;
}

OFile::OFile()
{
}

OFile::OFile(const std::string& filename, bool erase)
{
	open(filename, erase);
}

OFile::~OFile()
{
	mFile.close();
}

bool OFile::open(const std::string& filename, bool erase)
{
	if (mFile.is_open())
	{
		mFile.close();
	}
	mFile.open(filename, (erase) ? std::ios::trunc : std::ios::app);
	if (mFile.is_open())
	{
		mFilename = filename;
		return true;
	}
	return false;
}

bool OFile::isOpen() const
{
	return mFile.is_open();
}

OFile::operator bool() const
{
	return isOpen();
}

void OFile::close()
{
	mFile.close();
	mFilename = "";
}

const std::string& OFile::getFilename() const
{
	return mFilename;
}

} // namespace oe