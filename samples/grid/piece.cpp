#include "piece.hpp"

std::vector <std::vector <piece*> > piece::checkNearbySquares(glm::ivec2 myLocation)
{
	std::vector <std::vector <piece*> > emptySquares;
	emptySquares.resize(4);
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
		if (myLocation.x >= 0 && myLocation.y >= 0 && myLocation.x < m_grid->get_size().x && myLocation.y < m_grid->get_size().y)
		{
			auto thingsAtPlace = m_grid->get_actors_from_coord({ myLocation.x, myLocation.y, 2 });
			emptySquares[x] = thingsAtPlace;
		}
	}
	return emptySquares;
}