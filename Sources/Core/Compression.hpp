#ifndef OE_COMPRESSION_HPP
#define OE_COMPRESSION_HPP

#include "../Config.hpp"

#include "../ExtLibs/pugixml.hpp"

namespace oe
{

bool encode64(std::string& data);
bool decode64(std::string& data);
bool decompress(std::string& data);
bool compress(std::string& data);

bool compress64(std::string& data);
bool decompress64(std::string& data);

} // namespace oe

#endif // OE_COMPRESSION_HPP
