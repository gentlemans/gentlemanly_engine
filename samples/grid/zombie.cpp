#include "zombie.hpp"

void zombie::move_closer_to_center()
{
	glm::ivec2 myLocation = get_grid_location();
	glm::ivec2 wayToGo = get_grid_center() - myLocation;
	int rand = m_grid->get_random(0, 1);
	if (rand == 1) {
		if (wayToGo.x < 0) {
			myLocation.x--;
		}
		else if (wayToGo.x > 0) {
			myLocation.x++;
		}
	}
	else
	{
		if (wayToGo.y < 0) {
			myLocation.y--;
		}
		else if (wayToGo.y > 0) {
			myLocation.y++;
		}
	}
	auto thingsAtPlace = m_grid->get_actors_from_coord({ myLocation.x, myLocation.y, 2 });
	if (thingsAtPlace.size() == 0)
		set_grid_location(glm::ivec3{ myLocation.x, myLocation.y, m_level });
	else
	{
		myLocation = get_grid_location();
		if (rand == 0) {
			if (wayToGo.x < 0) {
				myLocation.x--;
			}
			else if (wayToGo.x > 0) {
				myLocation.x++;
			}
		}
		else
		{
			if (wayToGo.y < 0) {
				myLocation.y--;
			}
			else if (wayToGo.y > 0) {
				myLocation.y++;
			}
		}
	}
	thingsAtPlace = m_grid->get_actors_from_coord({ myLocation.x, myLocation.y, 2 });
	if (thingsAtPlace.size() == 0)
		set_grid_location(glm::ivec3{ myLocation.x, myLocation.y, m_level });
}

void zombie::move_random()
{
	glm::ivec2 myLocation = get_grid_location();
	std::vector <glm::ivec2> emptySquares=checkNearbyEmpty(myLocation);
	if (emptySquares.size() == 0)
		return;
	int rand = m_grid->get_random(0, emptySquares.size());
	set_grid_location(glm::ivec3{ emptySquares[rand].x, emptySquares[rand].y, m_level });
	return;

}
