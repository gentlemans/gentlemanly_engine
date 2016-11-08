#include "piece.hpp"

std::array<std::vector<piece*>, 4> piece::checkNearbySquares(glm::ivec2 myLocation)
{
	std::array<std::vector<piece*>, 4> emptySquares;

    emptySquares[NORTH] = m_grid->get_actors_from_coord({myLocation.x, myLocation.y + 1, 2});
    emptySquares[WEST] = m_grid->get_actors_from_coord({myLocation.x - 1, myLocation.y , 2});
    emptySquares[SOUTH] = m_grid->get_actors_from_coord({myLocation.x, myLocation.y - 1, 2});
    emptySquares[EAST] = m_grid->get_actors_from_coord({myLocation.x + 1, myLocation.y, 2});

	return emptySquares;
}

std::vector<std::vector<piece*>> piece::squares_in_direction(glm::ivec2 myLocation, Directions direction, int range)
{
	glm::ivec2 checkLocation = myLocation;
	std::vector<std::vector<piece*>> squares;
	squares.resize(range);
	for (int x = 0; x < range; x++) {
		if (direction == Directions::NORTH)
			checkLocation.y++;
		if (direction == Directions::WEST)
			checkLocation.x--;
		if (direction == Directions::SOUTH)
			checkLocation.y--;
		if (direction == Directions::EAST)
			checkLocation.x++;
		m_grid->get_actors_from_coord(glm::ivec3(checkLocation.x, checkLocation.y, 2));
	}
	//return emptySquares;
}
