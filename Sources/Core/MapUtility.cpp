#include "MapUtility.hpp"

namespace oe
{

std::vector<Vector2i> MapUtility::getNeighboors(const Vector2i& coords, Orientation orientation, bool diag, StaggerIndex staggerIndex, StaggerAxis staggerAxis)
{
	std::vector<Vector2i> n;
	if (orientation == Orientation::Orthogonal)
	{
		n.push_back({ coords.x, coords.y - 1 });
		n.push_back({ coords.x, coords.y + 1 });
		n.push_back({ coords.x - 1, coords.y });
		n.push_back({ coords.x + 1, coords.y });
		if (diag)
		{
			n.push_back({ coords.x + 1, coords.y - 1 });
			n.push_back({ coords.x + 1, coords.y + 1 });
			n.push_back({ coords.x - 1, coords.y + 1 });
			n.push_back({ coords.x - 1, coords.y - 1 });
		}
	}
	else if (orientation == Orientation::Isometric)
	{
		n.push_back({ coords.x - 1, coords.y });
		n.push_back({ coords.x, coords.y - 1 });
		n.push_back({ coords.x + 1, coords.y });
		n.push_back({ coords.x, coords.y + 1 });
		if (diag)
		{
			n.push_back({ coords.x - 1, coords.y - 1 });
			n.push_back({ coords.x + 1, coords.y - 1 });
			n.push_back({ coords.x + 1, coords.y + 1 });
			n.push_back({ coords.x - 1, coords.y + 1 });
		}
	}
	else if (orientation == Orientation::Staggered)
	{
		if (coords.y % 2 == 0)
		{
			n.push_back({ coords.x - 1, coords.y - 1 });
			n.push_back({ coords.x, coords.y - 1 });
			n.push_back({ coords.x, coords.y + 1 });
			n.push_back({ coords.x - 1, coords.y + 1 });
		}
		else
		{
			n.push_back({ coords.x, coords.y - 1 });
			n.push_back({ coords.x + 1, coords.y - 1 });
			n.push_back({ coords.x + 1, coords.y + 1 });
			n.push_back({ coords.x, coords.y + 1 });
		}
		if (diag)
		{
			n.push_back({ coords.x, coords.y - 2 });
			n.push_back({ coords.x + 1, coords.y });
			n.push_back({ coords.x, coords.y + 2 });
			n.push_back({ coords.x - 1, coords.y });
		}
	}
	else if (orientation == Orientation::Hexagonal)
	{
		if (staggerAxis == StaggerAxis::Y) // Pointy
		{
			if (coords.y % 2 == (I32)staggerIndex)
			{
				n.push_back({ coords.x - 1, coords.y - 1 });
				n.push_back({ coords.x, coords.y - 1 });
				n.push_back({ coords.x + 1, coords.y });
				n.push_back({ coords.x, coords.y + 1 });
				n.push_back({ coords.x - 1, coords.y + 1 });
				n.push_back({ coords.x - 1, coords.y });
			}
			else
			{
				n.push_back({ coords.x, coords.y - 1 });
				n.push_back({ coords.x + 1, coords.y - 1 });
				n.push_back({ coords.x + 1, coords.y });
				n.push_back({ coords.x + 1, coords.y + 1 });
				n.push_back({ coords.x, coords.y + 1 });
				n.push_back({ coords.x - 1, coords.y });
			}
		}
		else // Flat
		{
			if (coords.x % 2 == (I32)staggerIndex)
			{
				n.push_back({ coords.x - 1, coords.y - 1 });
				n.push_back({ coords.x, coords.y - 1 });
				n.push_back({ coords.x + 1, coords.y - 1 });
				n.push_back({ coords.x + 1, coords.y });
				n.push_back({ coords.x, coords.y + 1 });
				n.push_back({ coords.x - 1, coords.y });
			}
			else
			{
				n.push_back({ coords.x - 1, coords.y });
				n.push_back({ coords.x, coords.y - 1 });
				n.push_back({ coords.x + 1, coords.y });
				n.push_back({ coords.x + 1, coords.y + 1 });
				n.push_back({ coords.x, coords.y + 1 });
				n.push_back({ coords.x - 1, coords.y + 1 });
			}
		}
	}
	return n;
}

Vector2i MapUtility::worldToCoords(const Vector2& world, Orientation orientation, const Vector2i& tileSize, StaggerIndex staggerIndex, StaggerAxis staggerAxis, U32 hexSide)
{
	// TODO : 0 and -0 problem
	Vector2i c;
	if (orientation == Orientation::Orthogonal)
	{
		c.x = ((I32)world.x) / tileSize.x;
		c.y = ((I32)world.y) / tileSize.y;
		return c;
	}
	else if (orientation == Orientation::Isometric)
	{
		c.x = (I32)(((world.x - tileSize.x * 0.5f) / tileSize.x) + (world.y / tileSize.y));
		c.y = (I32)((world.y / tileSize.y) - ((world.x - tileSize.x * 0.5f) / tileSize.x));
		return c;
	}
	else if (orientation == Orientation::Staggered)
	{
		Vector2 halfSize = Vector2(tileSize.x * 0.5f, tileSize.y * 0.5f);
		Vector2 sector = Vector2(floor(world.x / halfSize.x), floor(world.y / halfSize.y));
		Vector2 p = world - Vector2(sector.x * halfSize.x, sector.y * halfSize.y);
		if (staggerAxis == StaggerAxis::Y)
		{
			if (((I32)sector.x + (I32)sector.y) % 2 == (I32)staggerIndex)
			{
				if (p.squaredDistance(Vector2::zero()) > p.squaredDistance(Vector2(halfSize.x, halfSize.y)))
				{
					sector.x--;
					sector.y--;

				}
			}
			else
			{
				if (p.squaredDistance(Vector2(0.0f, halfSize.y)) > p.squaredDistance(Vector2(halfSize.x, 0.0f)))
				{
					sector.y--;
				}
				else
				{
					sector.x--;
				}
			}
			c.x = (I32)floor(sector.x * 0.5f);
			c.y = (I32)sector.y;
			return c;
		}
		else
		{
			// TODO : Maybe need correction cause it is the same as the StaggerAxisY 
			if (((I32)sector.x + (I32)sector.y) % 2 == (I32)staggerIndex)
			{
				if (p.squaredDistance(Vector2::zero()) > p.squaredDistance(Vector2(halfSize.x, halfSize.y)))
				{
					sector.x--;
					sector.y--;
				}
			}
			else
			{
				if (p.squaredDistance(Vector2(0.0f, halfSize.y)) > p.squaredDistance(Vector2(halfSize.x, 0.0f)))
				{
					sector.y--;
				}
				else
				{
					sector.x--;
				}
			}
			c.x = (I32)sector.x;
			c.y = (I32)floor(sector.y * 0.5f);
			return c;
		}
	}
	else if (orientation == Orientation::Hexagonal)
	{
		if (staggerAxis == StaggerAxis::Y) // Pointy
		{
			F32 h = ((F32)(tileSize.y) - (F32)(hexSide)) * 0.5f;
			F32 r = (F32)(tileSize.x) * 0.5f;
			Vector2 sector = Vector2(floor(world.x / (2.0f * r)), floor(world.y / (h + (F32)(hexSide))));
			Vector2 p = world - Vector2(sector.x * (2.0f * r), sector.y * (h + (F32)(hexSide)));
			if ((I32)sector.y % 2 == (I32)staggerIndex) // Zone A
			{
				if (p.y < h) // Zone A top
				{
					if (p.x < r) // Zone A top left
					{
						if (Math::atan2(h - p.y, p.x) > 30.0f)
						{
							sector.x--;
							sector.y--;
						}
					}
					else if (Math::atan2(-p.y, p.x - r) > -30.0f) // Zone A top right
					{
						sector.y--;
					}
				}
			}
			else // Zone B
			{
				if (p.y < h) // Zone B top
				{
					if (p.x < r) // Zone B top left
					{
						(Math::atan2(-p.y, p.x) > -30.0f) ? sector.y-- : sector.x;
					}
					else if (Math::atan2(h - p.y, p.x - r) > 30.0f) // Zone B top right
					{
						sector.y--;
					}
				}
				else if (p.x < r) // Zone B down
				{
					sector.x--;
				}
			}
			c.x = (I32)sector.x;
			c.y = (I32)sector.y;
		}
		else // Flat
		{
			F32 h = ((F32)(tileSize.x) - (F32)(hexSide)) * 0.5f;
			F32 r = (F32)(tileSize.y) * 0.5f;
			Vector2 sector = Vector2(floor(world.x / (h + (F32)(hexSide))), floor(world.y / (2.0f * r)));
			Vector2 p = world - Vector2(sector.x * (h + (F32)(hexSide)), sector.y * (2.0f * r));
			if ((I32)sector.x % 2 == (I32)staggerIndex) // Zone A
			{
				if (p.x < h) // Zone A top
				{
					if (p.y < r) // Zone A top left
					{
						if (Math::atan2(h - p.x, p.y) > 30.0f)
						{
							sector.y--;
							sector.x--;
						}
					}
					else if (Math::atan2(-p.x, p.y - r) > -30.0f) // Zone A top right
					{
						sector.x--;
					}
				}
			}
			else // Zone B
			{
				if (p.x < h) // Zone B top
				{
					if (p.y < r) // Zone B top left
					{
						(Math::atan2(-p.x, p.y) > -30.0f) ? sector.x-- : sector.y;
					}
					else if (Math::atan2(h - p.x, p.y - r) > 30.0f) // Zone B top right
					{
						sector.x--;
					}
				}
				else if (p.y < r) // Zone B down
				{
					sector.y--;
				}
			}
			c.x = (I32)sector.x;
			c.y = (I32)sector.y;
		}
	}
	return c;
}

Vector2 MapUtility::coordsToWorld(const Vector2i& coords, Orientation orientation, const Vector2i& tileSize, StaggerIndex staggerIndex, StaggerAxis staggerAxis, U32 hexSide)
{
	Vector2 p;
	if (orientation == Orientation::Orthogonal)
	{
		p.x = (F32)(coords.x * tileSize.x);
		p.y = (F32)(coords.y * tileSize.y);
		return p;
	}
	else if (orientation == Orientation::Isometric)
	{
		p.x = (F32)((coords.x - coords.y) * (tileSize.x / 2));
		p.y = (F32)((coords.x + coords.y) * (tileSize.y / 2));
		return p;
	}
	else if (orientation == Orientation::Staggered)
	{
		if (staggerAxis == StaggerAxis::Y)
		{
			p.x = (coords.y % 2 == (I32)staggerIndex) ? (F32)coords.x * tileSize.x : (coords.x + 0.5f) * tileSize.x;
			p.y = coords.y * tileSize.y * 0.5f;
			return p;
		}
		else
		{
			p.x = coords.x * tileSize.x * 0.5f;
			p.y = (coords.x % 2 == (I32)staggerIndex) ? (F32)coords.y * tileSize.y : (coords.y + 0.5f) * tileSize.y;
			return p;
		}
	}
	else if (orientation == Orientation::Hexagonal)
	{
		if (staggerAxis == StaggerAxis::Y) // Pointy
		{
			p.x = (coords.y % 2 == (I32)staggerIndex) ? (F32)coords.x * tileSize.x : (coords.x + 0.5f) * tileSize.x;
			p.y = coords.y * (tileSize.y + hexSide) * 0.5f;
			return p;
		}
		else // Flat
		{
			p.x = coords.x * (tileSize.x + hexSide) * 0.5f;
			p.y = (coords.x % 2 == (I32)staggerIndex) ? (F32)coords.y * tileSize.y : (coords.y + 0.5f) * tileSize.y;
			return p;
		}
	}
	return p;
}

Vector2i MapUtility::getSize(Orientation orientation, const Vector2i& size, const Vector2i& tileSize, StaggerIndex staggerIndex, StaggerAxis staggerAxis, U32 hexSide)
{
	if (orientation == MapUtility::Orthogonal)
	{
		return Vector2i(size.x * tileSize.x, size.y * tileSize.y);
	}
	// TODO : Do others, else it wont render !
	return Vector2i();
}

} // namespace ke