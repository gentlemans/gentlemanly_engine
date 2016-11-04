#include "zombie.hpp"
void zombie::move_closer_to_center()
{
	glm::ivec2 myLocation = get_grid_location();
	glm::ivec2 wayToGo = get_grid_center() - myLocation;
	int rand = m_grid->get_random(0, 1);
	if (rand == 1) {
		if (wayToGo.x < 0) {
			myLocation.x--;
		} else if (wayToGo.x > 0) {
			myLocation.x++;
		}
	} else {
		if (wayToGo.y < 0) {
			myLocation.y--;
		} else if (wayToGo.y > 0) {
			myLocation.y++;
		}
	}
	auto thingsAtPlace = m_grid->get_actors_from_coord({myLocation.x, myLocation.y, 2});
	if (thingsAtPlace.size() == 0)
		set_grid_location(glm::ivec3{myLocation.x, myLocation.y, m_level});
	else {
		myLocation = get_grid_location();
		if (rand == 0) {
			if (wayToGo.x < 0) {
				myLocation.x--;
			} else if (wayToGo.x > 0) {
				myLocation.x++;
			}
		} else {
			if (wayToGo.y < 0) {
				myLocation.y--;
			} else if (wayToGo.y > 0) {
				myLocation.y++;
			}
		}
	}
	thingsAtPlace = m_grid->get_actors_from_coord({myLocation.x, myLocation.y, 2});
	if (thingsAtPlace.size() == 0)
		set_grid_location(glm::ivec3{myLocation.x, myLocation.y, m_level});
}

void zombie::move_random()
{
	glm::ivec2 myLocation = get_grid_location();
	std::array<std::vector<piece*>, 4> nearbySquares = checkNearbySquares(myLocation);
	std::vector<int> empties;
	for (int x = 0; x < 4; x++) {
		if (nearbySquares[x].size() == 0) {
			empties.push_back(x);
		}
	}
	if (empties.size() == 0) return;
	int rand = m_grid->get_random(0, empties.size() - 1);
	switch (empties[rand]) {
	case 0: myLocation.y++; break;
	case 1: myLocation.x++; break;
	case 2: myLocation.y--; break;
	case 3: myLocation.x--;
	};
	set_grid_location(glm::ivec3{myLocation.x, myLocation.y, m_level});
	return;
}
void zombie::tick_grid()
{
	glm::ivec2 myLocation = get_grid_location();
	glm::ivec2 gridCenter = get_grid_center();
    set_relative_rotation(get_relative_rotation() + 0.01f);
	/*
	int totalDistance = std::abs(myLocation.x - gridCenter.x) + std::abs(myLocation.y -
	gridCenter.y);
	if (m_grid->get_random(0, totalDistance) > 3)
		move_closer_to_center();
	else
		move_random();
		*/
}
