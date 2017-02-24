#ifndef OE_FILE_HPP
#define OE_FILE_HPP

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "../Config.hpp"

namespace oe
{

class OE_API Path
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

	private:
		static bool extractName(std::string& path);
		static void removeDouble(std::string& path);
		static void removeCurrent(std::string& path);
		static void removeBack(std::string& path);
		static void removeEnd(std::string& path);
};

class OE_API File
{
	public:
		static bool exists(const std::string& filename);
		static bool remove(const std::string& filename);
		static bool rename(const std::string& oldFilename, const std::string& newFilename);
};

class OE_API IFile
{
	public:
		IFile();
		IFile(const std::string& filename);
		~IFile();

		bool open(const std::string& filename);
		bool isOpen() const;
		operator bool() const;
		void close();
		const std::string& getFilename() const;

		bool read(std::string& line);

	private:
		std::ifstream mFile;
		std::string mFilename;
};

class OE_API OFile
{
	public:
		OFile();
		OFile(const std::string& filename, bool erase = false);
		~OFile();

		bool open(const std::string& filename, bool erase = false);
		bool isOpen() const;
		operator bool() const;
		void close();
		const std::string& getFilename() const;

		template <typename T>
		friend OFile& operator<<(OFile& file, const T& value)
		{
			file.mFile << value;
			return file;
		}

	private:
		std::ofstream mFile;
		std::string mFilename;
};

} // namespace oe

#endif // OE_FILE_HPP
