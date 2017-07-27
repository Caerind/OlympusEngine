#ifndef OE_MAPUTILITY_HPP
#define OE_MAPUTILITY_HPP

#include "../Math/Vector2.hpp"
#include "../Math/Vector2i.hpp"

namespace oe
{

class MapUtility
{
	public:
		enum Orientation
		{
			Orthogonal,
			Isometric,
			Staggered,
			Hexagonal
		};

		enum StaggerAxis
		{
			X,
			Y
		};

		enum StaggerIndex
		{
			Odd = 0,
			Even = 1
		};

		static std::vector<Vector2i> getNeighboors(const Vector2i& coords, Orientation orientation, bool diag = false, StaggerIndex staggerIndex = StaggerIndex::Odd, StaggerAxis staggerAxis = StaggerAxis::Y);
		static Vector2i worldToCoords(const Vector2& world, Orientation orientation, const Vector2i& tileSize, StaggerIndex staggerIndex = StaggerIndex::Odd, StaggerAxis staggerAxis = StaggerAxis::Y, U32 hexSide = 0);
		static Vector2 coordsToWorld(const Vector2i& coords, Orientation orientation, const Vector2i& tileSize, StaggerIndex staggerIndex = StaggerIndex::Odd, StaggerAxis staggerAxis = StaggerAxis::Y, U32 hexSide = 0);
		static Vector2i getSize(Orientation orientation, const Vector2i& size, const Vector2i& tileSize, StaggerIndex staggerIndex = StaggerIndex::Odd, StaggerAxis staggerAxis = StaggerAxis::Y, U32 hexSide = 0);
};

} // namespace oe

#endif // OE_MAPUTILITY_HPP