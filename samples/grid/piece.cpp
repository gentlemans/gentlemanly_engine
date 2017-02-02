#include "piece.hpp"
#include "grid.hpp"

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
		squares[x]=m_grid->get_actors_from_coord(glm::ivec3(checkLocation.x, checkLocation.y, 2));
	}
	return squares;
}
glm::ivec2 piece::get_location_from_direction(glm::ivec3 myLocation, Directions direction, int Length)
{
	glm::ivec2 finalDirection(myLocation.x, myLocation.y);
	switch (direction)
	{
	case NORTH:finalDirection.y = finalDirection.y + Length;
		break;
	case WEST:finalDirection.x = finalDirection.x - Length;
		break;
	case SOUTH:finalDirection.y = finalDirection.y - Length;
		break;
	case EAST:finalDirection.x = finalDirection.x + Length;
	}
	return finalDirection;
}


void piece::initialize(glm::ivec3 loc)
{
	m_grid = static_cast<grid*>(get_parent());
	set_relative_location({ float(loc.x), float(loc.y) });
	m_level = loc.z;
}


void piece::modify_health(double amount)
{
	now.health = now.health + amount;
	if (now.health > initial.health)
		now.health = initial.health;
	if (now.health < 0)
		now.health = 0;
	if (amount>0)
		sig_damaged(this, amount);
	if (now.health == 0)
	{
		sig_die(this);
	}
}
