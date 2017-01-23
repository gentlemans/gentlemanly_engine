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
	auto thingsAtPlace = m_grid->get_actors_from_coord({myLocation.x, myLocation.y, m_level});
	if (thingsAtPlace.size() == 0)
	{
		rotate(get_direction_to(glm::ivec2(get_grid_location().x, get_grid_location().y), myLocation));
		set_grid_location(glm::ivec3{ myLocation.x, myLocation.y, m_level });
	}
	else
	{
		glm::ivec3 TrueLocation= get_grid_location();
		damage_in_direction(get_direction_to(glm::ivec2(TrueLocation.x, TrueLocation.y), glm::ivec2(myLocation.x, myLocation.y)));
	}
}

void zombie::move_random()
{
	glm::ivec2 myLocation = get_grid_location();
	std::array<std::vector<piece*>, 4> nearbySquares = checkNearbySquares(myLocation);
	std::vector<int> empties;
	for (int x = 0; x < 4; x++)
	{
		if (nearbySquares[x].size() == 0) 
		{
			empties.push_back(x);
		}
		else
		{
			empties.push_back(x);
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
	if (m_grid->get_actors_from_coord(glm::ivec3(myLocation.x, myLocation.y, 2)).size() == 0)
		set_grid_location(glm::ivec3{ myLocation.x, myLocation.y, m_level });
	else
		damage_in_direction(my_direction);
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
		if (myLocation.y == 11)
		{
			set_grid_location(glm::ivec3{ myLocation.x+1, myLocation.y, m_level });
			return;
		}
		std::vector<piece *> pvec = m_grid->get_actors_from_coord(glm::ivec3{ myLocation.x + 1,myLocation.y, 2 });
		if (pvec.size() == 0)
		{
			set_grid_location(glm::ivec3{ myLocation.x + 1,myLocation.y, m_level });
			return;
		}
		else
		{
			set_grid_location(glm::ivec3{ myLocation.x,myLocation.y+1, m_level });
			return;
		}
	}
	if (myLocation.x == 11)
	{
		if (myLocation.y == -1)
		{
			set_grid_location(glm::ivec3{ myLocation.x - 1, myLocation.y, m_level });
			return;
		}
		if (myLocation.y == 11)
		{
			set_grid_location(glm::ivec3{ myLocation.x, myLocation.y - 1, m_level });
			return;
		}
		std::vector<piece *> pvec = m_grid->get_actors_from_coord(glm::ivec3{ myLocation.x - 1,myLocation.y, 2 });
		if (pvec.size() == 0)
		{
			set_grid_location(glm::ivec3{ myLocation.x - 1,myLocation.y, m_level });
			return;
		}
		else
		{
			set_grid_location(glm::ivec3{ myLocation.x,myLocation.y - 1, m_level });
			return;
		}
	}
		if (myLocation.y == -1)
		{
			std::vector<piece *> pvec = m_grid->get_actors_from_coord(glm::ivec3{ myLocation.x,myLocation.y+1, 2 });
			if (pvec.size() == 0)
			{
				set_grid_location(glm::ivec3{ myLocation.x,myLocation.y+1, m_level });
				return;
			}
			else
			{
				set_grid_location(glm::ivec3{ myLocation.x - 1,myLocation.y, m_level });
				return;
			}
		}
		if (myLocation.y == 11)
		{
			std::vector<piece *> pvec = m_grid->get_actors_from_coord(glm::ivec3{ myLocation.x,myLocation.y - 1, 2 });
			if (pvec.size() == 0)
			{
				set_grid_location(glm::ivec3{ myLocation.x,myLocation.y - 1, m_level });
				return;
			}
			else
			{
				set_grid_location(glm::ivec3{ myLocation.x+1,myLocation.y, m_level });
				return;
			}
		}
		std::cout << "Zombie on spawner not moved"<<'\n'; 
}
void zombie::damage_in_direction(Directions d)
{
	glm::ivec2 target = get_location_from_direction(get_grid_location(), d, 1);
	std::vector<piece*> p = m_grid->get_actors_from_coord(glm::ivec3(target.x, target.y, 2));
	if (p.size() < 1)
	{
		move_random();
		return;
	}
	rotate(d);
	attacking = true;
	p[0]->sig_moved.connect([this](piece*) {
		attacking = false;
	});
	p[0]->damage(now.damage);
}
void zombie::tick_grid()
{
	glm::ivec2 myLocation = get_grid_location();
	glm::ivec2 gridCenter = get_grid_center();
	std::vector <piece*> actors_at_my_location = m_grid->get_actors_from_coord(get_grid_location());
	for (int x = 0; x < actors_at_my_location.size(); x++)
	{
		auto& act = *actors_at_my_location[x];
		if (typeid(act) == typeid(zombiespawner))
		{
			move_off_spawner();
			return;
		}
	}
	int totalDistance = std::abs(myLocation.x - gridCenter.x) + std::abs(myLocation.y - gridCenter.y);
	if (m_grid->get_random(0, totalDistance) > 3)
	{
		move_closer_to_center();
		return;
	}
	else
	{
		move_random();
		return;
	}
}
