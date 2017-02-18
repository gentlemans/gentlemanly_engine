#ifndef GE_PIECE_HPP
#define GE_PIECE_HPP

#pragma once

#include <boost/signals2.hpp>

#include <ge/actor.hpp>

class grid;

class piece : public ge::actor
{
	/// \name stats stuff
	/// \{
public:
	struct stats {
		stats(double h = 1, double d = 1, double s = 1, double r = 0)
			: health{h}, damage{d}, speed{s}, regen{r}
		{
		}
		double health;
		double damage;
		double speed;
		double regen;
	};

	void modify_health(double amount);
	
	// virtual function children can reimplement to get custom stuff happening when they're damaged 
	// like detract from health
	virtual void damage(double damage, piece* calling){}
	
	boost::signals2::signal<void(piece* p, double amt)> sig_damaged;
	boost::signals2::signal<void(piece* p)> sig_die;
	
protected:
	stats initial;
	stats now;

public:
	
	/// \}
	
	/// \name transformation stuff
	/// \{
	
	enum Directions { NORTH = 0, EAST = 3, SOUTH = 2, WEST = 1, NONE = 5 };

	boost::signals2::signal<void(piece* p)> sig_moved;
	boost::signals2::signal<void(piece* p, glm::ivec3 new_loc, glm::ivec3 old_loc)> sig_move;

	void set_grid_location(glm::ivec3 loc);

	glm::ivec3 get_grid_location() const
	{
		return {int(get_relative_location().x), int(get_relative_location().y), m_level};
	}
	Directions get_direction_to(glm::ivec2 initial, glm::ivec2 final);

	void rotate(Directions direction);

	Directions get_rotation() const { return my_direction; }
	
	int level() const { return m_level; }
	
private:
	int m_level;
	Directions my_direction = NORTH;

public:
	
	/// \}
	
	/// \name action stuff
	/// \{
	
	/// virtual function that's called every `speed` ticks
	virtual void action(){}
	
private:
	
	float countdown_to_action = 0;
	
	/// \}
	
	/// \name Active
	/// \{

public:

	void toggle_active()
	{
		m_active = !m_active;
	}
	void set_active(bool set_to, piece* making_inactive)
	{
		m_active = set_to;
		if (set_to)
			trapping_p = NULL;
		else
			trapping_p = making_inactive;
	}
	bool active() const { return m_active;  }

private:

	bool m_active = true;

	/// \}

public:
	/// \name upgrade functions
	/// \{

public:


	virtual void calculate_upgrades(){};

	bool has_upgrade(const std::string& test) const
	{
		return m_upgrades.find(test) != m_upgrades.end();
	}
	int get_upgrade(const std::string& name) const
	{
		if (has_upgrade(name)) {
			return m_upgrades.find(name)->second;
		}
		return -1;
	}
	void set_upgrade(const std::string& name, int val)
	{
		m_upgrades[name] = val;
		// TODO: signals
	}
	
private:
	
	std::unordered_map<std::string, int> m_upgrades;
	
public:
	
	/// \}

	/// \name trapping
	/// \{

	piece* trapping_p;

	virtual void move_trapped_piece(piece* move_this) 
	{
		std::cout << "please override virtual void move_trapped piece";
	};

	/// \}

	void initialize(glm::ivec3 loc);
	
	void tick_grid();

protected:
	
	grid* m_grid;
	
};

#endif  // GE_PIECE_HPP
