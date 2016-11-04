#include "piece.hpp"

std::array<std::vector<piece*>, 4> piece::checkNearbySquares(glm::ivec2 myLocation)
{
	std::array<std::vector<piece*>, 4> emptySquares;
	for (int x = 0; x < 4; x++) {
		if (x == Directions::NORTH) {
			myLocation.y++;
		}
		if (x == Directions::EAST) {
			myLocation.x++;
			myLocation.y--;
		}
		if (x == Directions::SOUTH) {
			myLocation.y--;
			myLocation.x--;
		}
		if (x == Directions::WEST) {
			myLocation.y++;
			myLocation.x--;
		}
		auto thingsAtPlace = m_grid->get_actors_from_coord({myLocation.x, myLocation.y, 2});
		emptySquares[x] = thingsAtPlace;
	}
	return emptySquares;
}
