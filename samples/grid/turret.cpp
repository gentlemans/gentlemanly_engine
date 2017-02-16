#include "turret.hpp"
#include "bullet.hpp"
#include "grid.hpp"
#include "connector.hpp"

void turret::calculate_upgrades()
{
	now = initial;
	now.speed = now.speed - (get_upgrade("Attack Speed Up"));
	if (now.speed < 0) now.speed = 0;
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
	initial.damage = 5;
	initial.health = 100;
	initial.speed = 10;
	initial.regen = 0;
	now = initial;
	set_upgrade("Attack Speed Up", 1);
	// Increases the action speed of the tower
	set_upgrade("Damage Up", 1);
	// Each upgrade adds a stacking 10% damage increase
	set_upgrade("Regen Up", 0);
	// Adds one helth point regenerated per tick, given on peice action
	set_upgrade("Increaded Accuracy", 1);
	// Adds a stacking 10% increase to speed up to a total of 33% for each shot the turret doesn't
	// miss
	calculate_upgrades();
	die_connect = sig_die.connect([](piece* p) { p->set_parent(NULL); });
}

void turret::tick_grid()
{
	modify_health(now.regen);
	if (countdown_to_action > 0) {
		countdown_to_action--;
		return;
	}
	if (active == false)
		return;
	countdown_to_action =+ now.speed;
	shoot();
}

void turret::shoot()
{
	int range = 3;
	glm::ivec3 m_location = get_grid_location();
	bullet* shot_bullet = actor::factory<bullet>(m_grid, glm::ivec2(m_location.x, m_location.y), my_direction, now, range, this).get();
	connect_track(shot_bullet->sig_die, [shot_bullet,this](piece* p) {
		if (shot_bullet->hit)
			hitStreak++;
		else
			hitStreak = 0;
	}, shared(this));
}
