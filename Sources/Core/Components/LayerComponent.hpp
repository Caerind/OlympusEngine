#ifndef OE_LAYERCOMPONENT_HPP
#define OE_LAYERCOMPONENT_HPP

#include "../RenderableComponent.hpp"

#include "../../Graphics/Tileset.hpp"
#include "../MapUtility.hpp"

#include <SFML/Graphics/VertexArray.hpp>

namespace oe
{

class LayerComponent : public RenderableComponent
{
	public:
		LayerComponent(Entity& entity, bool attachedToEntity = true);

		std::vector<Vector2i> getNeighboors(const Vector2i& coords, bool diag = false);
		Vector2i worldToCoords(const Vector2& world);
		Vector2 coordsToWorld(const Vector2i& coords);
		Vector2i getSize();

		void create(Tileset* tileset = nullptr, const Vector2i& size = Vector2i::zero(), const Vector2i& tileSize = Vector2i::zero(), MapUtility::Orientation orientation = MapUtility::Orientation::Orthogonal, MapUtility::StaggerAxis staggerAxis = MapUtility::StaggerAxis::Y, MapUtility::StaggerIndex staggerIndex = MapUtility::StaggerIndex::Odd, U32 hexSideLength = 0);

		std::string getCode();
		bool loadFromCode(const std::string& code);
		
		TileId getTileId(const Vector2i& coords);
		void setTileId(const Vector2i& coords, TileId id);

		const std::string& getName() const;
		void setName(const std::string& name);
		
		const F32& getOpacity() const;
		void setOpacity(const F32& opacity);
		
		Tileset* getTileset() const;
		void setTileset(Tileset* tileset);

		const Vector2i& getSize() const;
		void setSize(const Vector2i& size);

		const Vector2i& getTileSize() const;
		void setTileSize(const Vector2i& tileSize);

		MapUtility::Orientation getOrientation() const;
		void setOrientation(MapUtility::Orientation orientation);

		MapUtility::StaggerAxis getStaggerAxis() const;
		void setStaggerAxis(MapUtility::StaggerAxis axis);

		MapUtility::StaggerIndex getStaggerIndex() const;
		void setStaggerIndex(MapUtility::StaggerIndex index);

		U32 getHexSizeLength() const;
		void setHexSideLength(U32 hexSideLength);

		virtual void render(sf::RenderTarget& target);

		void updateGeometry();
		bool isGeometryUpdated() const;
		void ensureUpdateGeometry();

		void updateRender();
		bool isRenderUpdated() const;
		void ensureUpdateRender();

	private:
		sf::VertexArray mVertices;

		bool mGeometryUpdated;
		bool mRenderUpdated;

		std::vector<TileId> mTileGrid;

		std::string mName;
		Tileset* mTileset;
		Vector2i mSize;
		Vector2i mTileSize;
		MapUtility::Orientation mOrientation;
		MapUtility::StaggerAxis mStaggerAxis;
		MapUtility::StaggerIndex mStaggerIndex;
		U32 mHexSideLength;
		F32 mOpacity;
};

} // namespace oe

#endif // OE_LAYERCOMPONENT_HPP
