#ifndef OE_SFMLRESOURCES_HPP
#define OE_SFMLRESOURCES_HPP

#include "ResourceHolder.hpp"

#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

namespace oe
{

class Image : public sf::Image
{
	public:
		Image() = default;
		Image(const std::string& filename);
};

class Texture : public sf::Texture
{
	public:
		Texture() = default;
		Texture(const std::string& filename);
};

class Font : public sf::Font
{
	public:
		Font() = default;
		Font(const std::string& filename);
};

class Shader : public sf::Shader
{
	public:
		Shader() = default;
		Shader(const std::string& filename, sf::Shader::Type type);
		Shader(const std::string& vertexShaderFilename, const std::string& fragmentShaderFilename);
		Shader(const std::string& vertexShaderFilename, const std::string& geometryShaderFilename, const std::string& fragmentShaderFilename);
};

class SoundBuffer : public sf::SoundBuffer
{
	public:
		SoundBuffer() = default;
		SoundBuffer(const std::string& filename);
};

using ImageHolder = ResourceHolder<Image>;
using TextureHolder = ResourceHolder<Texture>;
using FontHolder = ResourceHolder<Font>;
using ShaderHolder = ResourceHolder<Shader>;
using SoundHolder = ResourceHolder<SoundBuffer>;

} // namespace oe

#endif // OE_SFMLRESOURCES_HPP
