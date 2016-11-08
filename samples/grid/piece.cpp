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
