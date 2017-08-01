#include "LayerComponent.hpp"
#include "../../System/Compression.hpp"

namespace oe
{

LayerComponent::LayerComponent(Entity& entity, bool attachedToEntity)
	: RenderableComponent(entity, attachedToEntity)
	, mVertices(sf::Quads)
	, mGeometryUpdated(false)
	, mTileGrid()
	, mName("")
	, mTileset(nullptr)
	, mSize()
	, mTileSize()
	, mOrientation(MapUtility::Orientation::Orthogonal)
	, mStaggerAxis(MapUtility::StaggerAxis::Y)
	, mStaggerIndex(MapUtility::StaggerIndex::Odd)
	, mHexSideLength(0)
	, mOpacity(1.0f)
{
}

std::vector<Vector2i> LayerComponent::getNeighboors(const Vector2i& coords, bool diag)
{
	return MapUtility::getNeighboors(coords, mOrientation, diag, mStaggerIndex, mStaggerAxis);
}

Vector2i LayerComponent::worldToCoords(const Vector2& world)
{
	return MapUtility::worldToCoords(world - getGlobalPosition(), mOrientation, mTileSize, mStaggerIndex, mStaggerAxis, mHexSideLength);
}

Vector2 LayerComponent::coordsToWorld(const Vector2i& coords)
{
	return MapUtility::coordsToWorld(coords, mOrientation, mTileSize, mStaggerIndex, mStaggerAxis, mHexSideLength) + getGlobalPosition();
}

Vector2i LayerComponent::getRealSize()
{
	return MapUtility::getSize(mOrientation, mSize, mTileSize, mStaggerIndex, mStaggerAxis, mHexSideLength);
}

void LayerComponent::create(Tileset* tileset, const Vector2i& size, const Vector2i& tileSize, MapUtility::Orientation orientation, MapUtility::StaggerAxis staggerAxis, MapUtility::StaggerIndex staggerIndex, U32 hexSideLength)
{
	mTileset = tileset;
	mSize = size;
	mTileSize = tileSize;
	mOrientation = orientation;
	mStaggerAxis = staggerAxis;
	mStaggerIndex = staggerIndex;
	mHexSideLength = hexSideLength;

	updateGeometry();
}

std::string LayerComponent::getCode()
{
	std::string data;
	data.reserve(mSize.x * mSize.y * 4);
	ensureUpdateGeometry();
	Vector2i coords;
	for (coords.y = 0; coords.y < mSize.y; coords.y++)
	{
		for (coords.x = 0; coords.x < mSize.x; coords.x++)
		{
			TileId id = mTileGrid[coords.x + coords.y * mSize.x];
			data.push_back((U8)(id));
			data.push_back((U8)(id >> 8));
			data.push_back((U8)(id >> 16));
			data.push_back((U8)(id >> 24));
		}
	}
	if (!Compression::compress64(data))
	{
		return "";
	}
	return data;
}

bool LayerComponent::loadFromCode(const std::string& code)
{
	Vector2i coords;
	const U32 FLIPPED_HORIZONTALLY_FLAG = 0x80000000;
	const U32 FLIPPED_VERTICALLY_FLAG = 0x40000000;
	const U32 FLIPPED_DIAGONALLY_FLAG = 0x20000000;
	std::string data;
	std::stringstream ss;
	ss << code;
	ss >> data;
	if (!Compression::decompress64(data))
	{
		return false;
	}
	std::vector<U8> byteVector;
	byteVector.reserve(mSize.x * mSize.y * 4);
	for (std::string::iterator i = data.begin(); i != data.end(); ++i)
	{
		byteVector.push_back(*i);
	}
	ensureUpdateGeometry();
	for (U32 i = 0; i < byteVector.size() - 3; i += 4)
	{
		TileId gid = byteVector[i] | byteVector[i + 1] << 8 | byteVector[i + 2] << 16 | byteVector[i + 3] << 24;
		gid &= ~(FLIPPED_HORIZONTALLY_FLAG | FLIPPED_VERTICALLY_FLAG | FLIPPED_DIAGONALLY_FLAG);
		
		U32 index(coords.x + coords.y * mSize.x);
		mTileGrid[index] = gid;
		if (mTileset != nullptr)
		{
			sf::Vertex* vertex(&mVertices[index * 4]);
			sf::Vector2f pos(mTileset->toPos(gid));
			Vector2 texSize(mTileset->getTileSize());
			vertex[0].texCoords = pos;
			vertex[1].texCoords = sf::Vector2f(pos.x + texSize.x, pos.y);
			vertex[2].texCoords = sf::Vector2f(pos.x + texSize.x, pos.y + texSize.y);
			vertex[3].texCoords = sf::Vector2f(pos.x, pos.y + texSize.y);
		}
		
		coords.x = (coords.x + 1) % mSize.x;
		if (coords.x == 0)
		{
			coords.y++;
		}
	}
	return true;
}

TileId LayerComponent::getTileId(const Vector2i& coords)
{
	if (0 <= coords.x && 0 <= coords.y && coords.x < mSize.x && coords.y < mSize.y)
	{
		ensureUpdateGeometry();
		U32 index(coords.x + coords.y * mSize.x);
		if (index < mTileGrid.size())
		{
			return mTileGrid[index];
		}
	}
	return 0;
}

void LayerComponent::setTileId(const Vector2i& coords, TileId id)
{
	if (0 <= coords.x && 0 <= coords.y && coords.x < mSize.x && coords.y < mSize.y)
	{
		ensureUpdateGeometry();
		U32 index(coords.x + coords.y * mSize.x);
		mTileGrid[index] = id;
		if (mTileset != nullptr)
		{
			sf::Vertex* vertex(&mVertices[index * 4]);
			sf::Vector2f pos(mTileset->toPos(id));
			Vector2 texSize(mTileset->getTileSize());
			vertex[0].texCoords = pos;
			vertex[1].texCoords = sf::Vector2f(pos.x + texSize.x, pos.y);
			vertex[2].texCoords = sf::Vector2f(pos.x + texSize.x, pos.y + texSize.y);
			vertex[3].texCoords = sf::Vector2f(pos.x, pos.y + texSize.y);
		}
	}
}

const std::string& LayerComponent::getName() const
{
	return mName;
}

void LayerComponent::setName(std::string const& name)
{
	mName = name;
}

const F32& LayerComponent::getOpacity() const
{
	return mOpacity;
}

void LayerComponent::setOpacity(const F32& opacity)
{
	mOpacity = opacity;
	mRenderUpdated = false;
}

Tileset* LayerComponent::getTileset() const
{
	return mTileset;
}

void LayerComponent::setTileset(Tileset* tileset)
{
	if (mTileset != tileset)
	{
		if ((tileset != nullptr && mTileset == nullptr) || (tileset != nullptr && mTileset != nullptr && tileset->getTileSize() != mTileset->getTileSize()))
		{
			mGeometryUpdated = false;
		}
		mTileset = tileset;
	}
}

const Vector2i& LayerComponent::getSize() const
{
	return mSize;
}

void LayerComponent::setSize(const Vector2i& size)
{
	if (mSize != size)
	{
		mSize = size;
		mGeometryUpdated = false;
	}
}

const Vector2i& LayerComponent::getTileSize() const
{
	return mTileSize;
}

void LayerComponent::setTileSize(const Vector2i& tileSize)
{
	if (mTileSize != tileSize)
	{
		mTileSize = tileSize;
		mGeometryUpdated = false;
	}
}

MapUtility::Orientation LayerComponent::getOrientation() const
{
	return mOrientation;
}

void LayerComponent::setOrientation(MapUtility::Orientation orientation)
{
	if (mOrientation != orientation)
	{
		mOrientation = orientation;
		mGeometryUpdated = false;
	}
}

MapUtility::StaggerAxis LayerComponent::getStaggerAxis() const
{
	return mStaggerAxis;
}

void LayerComponent::setStaggerAxis(MapUtility::StaggerAxis axis)
{
	if (mStaggerAxis != axis)
	{
		mStaggerAxis = axis;
		if (mOrientation == MapUtility::Orientation::Hexagonal || mOrientation == MapUtility::Orientation::Staggered)
		{
			mGeometryUpdated = false;
		}
	}
}

MapUtility::StaggerIndex LayerComponent::getStaggerIndex() const
{
	return mStaggerIndex;
}

void LayerComponent::setStaggerIndex(MapUtility::StaggerIndex index)
{
	if (mStaggerIndex != index)
	{
		mStaggerIndex = index;
		if (mOrientation == MapUtility::Orientation::Hexagonal || mOrientation == MapUtility::Orientation::Staggered)
		{
			mGeometryUpdated = false;
		}
	}
}

U32 LayerComponent::getHexSizeLength() const
{
	return mHexSideLength;
}

void LayerComponent::setHexSideLength(U32 hexSideLength)
{
	if (mHexSideLength != hexSideLength)
	{
		mHexSideLength = hexSideLength;
		if (mOrientation == MapUtility::Orientation::Hexagonal)
		{
			mGeometryUpdated = false;
		}
	}
}

void LayerComponent::render(sf::RenderTarget& target)
{
	if (mTileset != nullptr)
	{
		ensureUpdateRender();
		sf::RenderStates states;
		states.texture = &mTileset->getTexture();
		states.transform = getGlobalTransform();
		target.draw(mVertices, states);
	}
}

void LayerComponent::updateGeometry()
{
	if (mTileset == nullptr || mSize.x == 0 || mSize.y == 0 || mTileSize.x == 0 || mTileSize.y == 0)
	{
		return;
	}
	sf::Vector2f texSize(toSF(Vector2(mTileset->getTileSize())));
	mVertices.resize(mSize.x * mSize.y * 4);
	mTileGrid.resize(mSize.x * mSize.y * 4); // TODO : Keep tile id already set in order
	Vector2i coords;
	for (coords.x = 0; coords.x < mSize.x; coords.x++)
	{
		for (coords.y = 0; coords.y < mSize.y; coords.y++)
		{
			// Get the position of the vertex
			Vector2 pos = MapUtility::coordsToWorld(coords, mOrientation, mTileSize, mStaggerIndex, mStaggerAxis, mHexSideLength);
			sf::Vertex* vertex = &mVertices[(coords.x + coords.y * mSize.x) * 4];
			F32 delta = texSize.y - (F32)mTileSize.y;
			vertex[0].position = sf::Vector2f(pos.x, pos.y - delta);
			vertex[1].position = sf::Vector2f(pos.x + mTileSize.x, pos.y - delta);
			vertex[2].position = sf::Vector2f(pos.x + mTileSize.x, pos.y + mTileSize.y);
			vertex[3].position = sf::Vector2f(pos.x, pos.y + mTileSize.y);
		}
	}
	setLocalAABB(Rect(Vector2(), getRealSize().toVector2()));

	mGeometryUpdated = true;
}

bool LayerComponent::isGeometryUpdated() const
{
	return mGeometryUpdated;
}

void LayerComponent::ensureUpdateGeometry()
{
	if (!mGeometryUpdated)
	{
		updateGeometry();
	}
}

void LayerComponent::updateRender()
{
	sf::Color color = sf::Color(255, 255, 255, static_cast<U8>(255.0f * mOpacity));
	U32 size = mVertices.getVertexCount();
	for (U32 i = 0; i < size; i++)
	{
		mVertices[i].color = color;
	}

	mRenderUpdated = true;
}

bool LayerComponent::isRenderUpdated() const
{
	return mRenderUpdated;
}

void LayerComponent::ensureUpdateRender()
{
	ensureUpdateGeometry();
	if (!mRenderUpdated)
	{
		updateRender();
	}
}

} // namespace oe