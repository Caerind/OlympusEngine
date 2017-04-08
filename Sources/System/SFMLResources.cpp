#include "SFMLResources.hpp"

namespace oe
{

Image::Image(const std::string& filename)
{
	loadFromFile(filename);
}

Texture::Texture(const std::string& filename)
{
	loadFromFile(filename);
}

Font::Font(const std::string& filename)
{
	loadFromFile(filename);
}

Shader::Shader(const std::string& filename, sf::Shader::Type type)
{
	loadFromFile(filename, type);
}

Shader::Shader(const std::string& vertexShaderFilename, const std::string& fragmentShaderFilename)
{
	loadFromFile(vertexShaderFilename, fragmentShaderFilename);
}

Shader::Shader(const std::string& vertexShaderFilename, const std::string& geometryShaderFilename, const std::string& fragmentShaderFilename)
{
	loadFromFile(vertexShaderFilename, geometryShaderFilename, fragmentShaderFilename);
}

SoundBuffer::SoundBuffer(const std::string& filename)
{
	loadFromFile(filename);
}

} // namespace oe