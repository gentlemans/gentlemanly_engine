#include "piece.hpp"

std::vector <glm::ivec2> piece::checkNearbyEmpty(glm::ivec2 myLocation)
{
	std::vector <glm::ivec2> emptySquares;
	for (int x = 0; x < 4; x++)
	{
		if (x == 0)
		{
			myLocation.x--;
		}
		if (x == 1)
		{
			myLocation.x = myLocation.x + 2;
		}
		if (x == 2)
		{
			myLocation.y--;
		}
		if (x == 3)
		{
			myLocation.y = myLocation.y + 2;
		}
		auto thingsAtPlace = m_grid->get_actors_from_coord({ myLocation.x, myLocation.y, 2 });
		if (thingsAtPlace.size() == 0)
	}
	return emptySquares;
}
