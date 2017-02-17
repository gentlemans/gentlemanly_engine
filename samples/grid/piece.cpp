#include "piece.hpp"
#include "grid.hpp"

void piece::initialize(glm::ivec3 loc)
{
	m_grid = static_cast<grid*>(get_parent());
	set_relative_location({float(loc.x), float(loc.y)});
	m_level = loc.z;
	
	add_interface<piece, gridtick_interface>();
}

void piece::modify_health(double amount)
{
	now.health = now.health + amount;
	if (now.health > initial.health) now.health = initial.health;
	if (now.health < 0) now.health = 0;
	if (amount < 0) sig_damaged(this, amount);
	if (now.health == 0) {
		sig_die(this);
	}
}

piece::Directions piece::get_direction_to(glm::ivec2 initial, glm::ivec2 final)
{
	int changeX = final.x - initial.x;
	int changeY = final.y - initial.y;
	Directions togo = NONE;
	if (changeX != 0 && changeY != 0) togo = NONE;
	if (changeX == 0 && changeY == 0) togo = NONE;
	if (changeY > 0) togo = NORTH;
	if (changeY < 0) togo = SOUTH;
	if (changeX > 0) togo = EAST;
	if (changeX < 0) togo = WEST;
	return togo;
}

void piece::rotate(Directions direction)
{
	if (direction == NONE) return;
	set_relative_rotation(direction * glm::half_pi<float>());
	my_direction = direction;
}

void piece::set_grid_location(glm::ivec3 loc)
{
	glm::ivec3 old = get_grid_location();

	set_relative_location({loc.x, loc.y});
	m_level = loc.z;

	sig_move(this, get_grid_location(), old);
}

void piece::tick_grid() {
	modify_health(now.regen);
	
	if (countdown_to_action > 0) {
		countdown_to_action--;
		return;
	}
	if (active == false)
		return;
	countdown_to_action += now.speed;
	
	action();
}
