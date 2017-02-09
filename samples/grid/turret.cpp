#include "turret.hpp"

void turret::calculate_upgrades()
{
	now = initial;
	now.speed = now.speed - (2 * get_upgrade("Attack Speed Up"));
	if (now.speed > 0) now.speed = 0;
	int amount = get_upgrade("Damage Up");
	for (int x = 0; x < amount; x++) {
		now.damage = now.damage * 1.1;
	}
	now.regen = now.regen + (get_upgrade("Regen Up") * 20);
	return;
}

void turret::initialize(glm::uvec2 location, Directions direction)
{
	rotate(direction);
	piece::initialize({location.x, location.y, 2});
	add_interface<turret, gridtick_interface>();
	mesh = ge::actor::factory<ge::mesh_actor>(this, "turret/turret.meshsettings").get();
	initial.damage = 50;
	initial.health = 100;
	initial.speed = 4;
	initial.regen = 0;
	now = initial;
	set_upgrade("Attack Speed Up", 1);
	// Increases the action speed of the tower
	set_upgrade("Damage Up", 1);
	// Each upgrade adds a stacking 10% damage increase
	set_upgrade("Regen Up", 1);
	// Adds one helth point regenerated per tick, given on peice action
	set_upgrade("Increaded Accuracy", 1);
	// Adds a stacking 10% increase to speed up to a total of 33% for each shot the turret doesn't
	// miss
	calculate_upgrades();
	die_connect = sig_die.connect([](piece* p) { p->set_parent(NULL); });
}

void turret::tick_grid()
{
	if (countdown_to_action >= 0) {
		countdown_to_action--;
		return;
	}
	countdown_to_action = now.speed;
	shoot();
	modify_health(now.regen);
}

void turret::shoot()
{
	int range = 3;
	auto squares = squares_in_direction(get_grid_location(), my_direction, range);
	piece* tod;
	for (int x = 0; x < range; x++) {
		if (squares[x].size() != 0) {
			if (hitStreak < 3) hitStreak++;
			tod = squares[x][0];
			break;
		} else if (x == range - 1) {
			hitStreak = 0;
			return;
		}
	}
	double calculated_damage = now.damage * pow(1.1, hitStreak);
	tod->damage(calculated_damage, this);
}
