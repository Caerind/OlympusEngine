#ifndef OE_PATH_HPP
#define OE_PATH_HPP

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "Prerequisites.hpp"

namespace oe
{

class Path
{
	public:
		static bool isDirectory(const std::string& path);
		static std::string getDirectoryName(std::string path);
		static std::vector<std::string> getDirectoryList(std::string path);
		static bool isFile(const std::string& path);
		static std::string getFileName(std::string path);
		static std::string getExtesionName(std::string path);

		static void unify(std::string& path);
		static std::string getUnified(std::string path);
		
		static bool exists(const std::string& filename);
		static bool remove(const std::string& filename);
		static bool rename(const std::string& oldFilename, const std::string& newFilename);

	private:
		static bool extractName(std::string& path);
		static void removeDouble(std::string& path);
		static void removeCurrent(std::string& path);
		static void removeBack(std::string& path);
		static void removeEnd(std::string& path);
};

} // namespace oe

#endif // OE_PATH_HPP
