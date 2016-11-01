#include "piece.hpp"

std::array<std::vector<piece*>, 4> piece::checkNearbySquares(glm::ivec2 myLocation)
{
    std::array<std::vector<piece*>, 4> emptySquares;
	for (int x = 0; x < 4; x++)
	{
		if (x == 0)
		{
			myLocation.y++;
		}
		if (x == 1)
		{
			myLocation.x++;
			myLocation.y--;
		}
		if (x == 2)
		{
			myLocation.y--;
			myLocation.x--;
		}
		if (x == 3)
		{
			myLocation.y++;
			myLocation.x--;
		}
			auto thingsAtPlace = m_grid->get_actors_from_coord({ myLocation.x, myLocation.y, 2 });
			emptySquares[x] = thingsAtPlace;
	}
	return emptySquares;
}
