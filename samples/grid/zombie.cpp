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
	{
		rotate(get_direction_to(glm::ivec2(get_grid_location().x, get_grid_location().y), myLocation));
		set_grid_location(glm::ivec3{ myLocation.x, myLocation.y, m_level });
	}
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
		rotate(get_direction_to(glm::ivec2(get_grid_location().x,get_grid_location().y), myLocation));
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
	case Directions::NORTH: myLocation.y++; break;
	case Directions::EAST: myLocation.x++; break;
	case Directions::SOUTH: myLocation.y--; break;
	case Directions::WEST: myLocation.x--;
	};
	rotate(get_direction_to(glm::ivec2(get_grid_location().x, get_grid_location().y), myLocation));
	set_grid_location(glm::ivec3{myLocation.x, myLocation.y, m_level});
	return;
}
void zombie::move_off_spawner()
{
	glm::ivec2 myLocation = get_grid_location();
	if (myLocation.x == -1)
	{
		if (myLocation.y == -1)
		{
			set_grid_location(glm::ivec3{ myLocation.x, myLocation.y+1, m_level });
			return;
		}
		if (myLocation.y == 12)
		{
			set_grid_location(glm::ivec3{ myLocation.x+1, myLocation.y, m_level });
			return;
		}
		std::vector<piece *> pvec = m_grid->get_actors_from_coord(glm::ivec3{ myLocation.x + 1,myLocation.y, m_level });
		if (pvec.size() == 0)
		{
			set_grid_location(glm::ivec3{ myLocation.x + 1,myLocation.y, m_level });
			return;
		}
	}
	if (myLocation.x == 12)
	{
		if (myLocation.y == -1)
		{
			set_grid_location(glm::ivec3{ myLocation.x-1, myLocation.y, m_level });
			return;
		}
		if (myLocation.y == 12)
		{
			set_grid_location(glm::ivec3{ myLocation.x, myLocation.y-1, m_level });
			return;
		}
		std::vector<piece *> pvec = m_grid->get_actors_from_coord(glm::ivec3{ myLocation.x - 1,myLocation.y, m_level });
		if (pvec.size() == 0)
		{
			set_grid_location(glm::ivec3{ myLocation.x - 1,myLocation.y, m_level });
			return;
		}
		if (myLocation.y == -1)
		{
			std::vector<piece *> pvec = m_grid->get_actors_from_coord(glm::ivec3{ myLocation.x,myLocation.y+1, m_level });
			if (pvec.size() == 0)
			{
				set_grid_location(glm::ivec3{ myLocation.x,myLocation.y+1, m_level });
				return;
			}
		}
		if (myLocation.y == 12)
		{
			std::vector<piece *> pvec = m_grid->get_actors_from_coord(glm::ivec3{ myLocation.x,myLocation.y - 1, m_level });
			if (pvec.size() == 0)
			{
				set_grid_location(glm::ivec3{ myLocation.x,myLocation.y - 1, m_level });
			}
		}
		std::cout << "Zombie on spawner not moved"<<'\n'; 
	}
}
void zombie::tick_grid()
{
	glm::ivec2 myLocation = get_grid_location();
	glm::ivec2 gridCenter = get_grid_center();
	int totalDistance = std::abs(myLocation.x - gridCenter.x) + std::abs(myLocation.y -
	gridCenter.y);
	std::vector <piece*> actors_at_my_location = m_grid->get_actors_from_coord(get_grid_location());
	for (int x = 0; x < actors_at_my_location.size(); x++)
	{
		if (typeid(*actors_at_my_location[x]) == typeid(zombiespawner))
		{
			move_off_spawner();
		}
	}
	if (m_grid->get_random(0, totalDistance) > 3)
		move_closer_to_center();
	else
		move_random();
}
