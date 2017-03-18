#ifndef OE_COMPRESSION_HPP
#define OE_COMPRESSION_HPP

#include "Prerequisites.hpp"

namespace oe
{

class Compression
{
	public:
		static bool encode64(std::string& data);
		static bool decode64(std::string& data);
		static bool compress(std::string& data);
		static bool decompress(std::string& data);

		static bool compress64(std::string& data);
		static bool decompress64(std::string& data);

	private:
		static const std::string mBase64Table;

		static bool isBase64(U8 c);
};

} // namespace oe

#endif // OE_COMPRESSION_HPP
