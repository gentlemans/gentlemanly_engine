#pragma once


#include "ge/transform.hpp"

#include <memory>

#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>


#include <boost/container/flat_set.hpp>
#include <boost/signals2.hpp>

namespace ge
{

class actor : public std::enable_shared_from_this<actor>
{
	// no shared_ptr because that would be a cyclic reference
	actor* m_parent = nullptr;

	// set for find -- we don't care much about insertion speed, but iteration is more important.
	boost::container::flat_set<std::shared_ptr<actor>> m_children;

	transform m_transform;
	
protected:
	
	// called from `factory`
	actor(){};
	
	// so we can use make_shared
	
	
public:
	
	/// Creates an actor of type ActorType 
	/// \param parent The parent actor, null for a root actor
	/// \param init_params The initialization paramters, will be passed to ActorType::initialize
	template<typename ActorType = actor, typename... InitParams>
	static std::shared_ptr<ActorType> factory(actor* parent, InitParams&&... init_params) {
		
		static_assert(std::is_base_of<actor, ActorType>::value, "Cannot use actor::factory on non-actor type.");
		
		auto ret = std::shared_ptr<ActorType>(new ActorType());
		
		if(parent) ret->set_parent(parent);
		ret->initialize(std::forward<InitParams>(init_params)...);
		
		return ret;
		
	}

	// no move or copy -- will be in a shared_ptr
	actor(const actor&) = delete;
	actor(actor&&) = delete;
	
	// default version, can be overidden in children
	void initialize(){};

	actor& operator=(const actor&) = delete;
	actor& operator=(actor&&) = delete;

	virtual ~actor();
	
	std::shared_ptr<actor> shared() {
		return shared_from_this();
	}

	// transform transformation functions
	/////////////////////////////////////
	
	/// sets the location relative to the parent, if there is one.
	/// \param new_location the new location
	void set_relative_location(glm::vec2 new_location)
	{
		if (new_location != m_transform.location)
		{
			signal_location_changed(*this);
			signal_transform_changed(*this);
			
			// call those signals on children
			for(auto act : m_children) {
				act->signal_location_changed(*act);
				act->signal_transform_changed(*act);
			}
			
		}
		m_transform.location = new_location;
	}
	/// Gets the location of the actor relative to the parent
	/// \return The relative location
	glm::vec2 get_relative_location() const { return m_transform.location; }
	/// Sets the rotation relative to the parent. 
	/// \param new_rotation the new rotation to apply
	void set_relative_rotation(float new_rotation)
	{
		if (new_rotation != m_transform.rotation)
		{
			signal_rotation_changed(*this);

			signal_transform_changed(*this);
			
			// call those signals on children
			for(auto act : m_children) {
				act->signal_rotation_changed(*act);
				act->signal_transform_changed(*act);
			}
		}
		m_transform.rotation = new_rotation;
	}
	/// Gets the rotation of the actor relative to the parent
	/// \return The relative rotation
	float get_relative_rotation() const { return m_transform.rotation; }
	/// Sets the scale of the actor relative to the parent
	/// \param new_scale The relative scale
	void set_relative_scale(glm::vec2 new_scale)
	{
		if (new_scale != m_transform.scale)
		{
			signal_scale_changed(*this);
			signal_transform_changed(*this);
		}
		m_transform.scale = new_scale;
	}
	/// Gets the scale relative to the parent actor
	/// \return The relative scale
	glm::vec2 get_relative_scale() const { return m_transform.scale; }
	/// Calculates the absolute location of the actor
	/// \return The absolute location
	glm::vec2 calcuate_absolute_location() const {
		
		if (has_parent()) {
			glm::vec2 parent_loc = get_parent()->calcuate_absolute_location();
			float parent_rot = get_parent()->calcuate_absolute_rotation();
			return parent_loc + glm::rotate(get_relative_location() * get_parent()->calcuate_absolute_scale(), glm::radians(parent_rot));
		}
		
		return get_relative_location();
		


	}
	/// Calculates the absolute rotation of the actor
	/// \return The absolute rotation
	float calcuate_absolute_rotation() const {
		if(has_parent()) {
			return get_parent()->calcuate_absolute_rotation() + get_relative_rotation();
		}
		
		return get_relative_rotation();
	}
	/// Calculates the absolute scale of the actor
	/// \return The absolute scale
	glm::vec2 calcuate_absolute_scale() const {
		if(has_parent()) {
			return get_parent()->calcuate_absolute_scale() * get_relative_scale();
		}
		return get_relative_scale();
	}

	/// Calculates the model matrix for the actor
	/// \return The model matrix
	glm::mat3 calculate_model_matrix() const {
		
		glm::mat3 this_model;

		glm::scale(this_model, get_relative_scale());
		glm::translate(this_model, get_relative_location());
		glm::rotate(this_model, get_relative_rotation());

		return has_parent() ? this_model * get_parent()->calculate_model_matrix() : this_model;

	}

	// parent manipulation
	//////////////////////
	
	/// Sets the parent of the actor, unparenting it from the previous parent
	/// \param new_parent The new parent of the actor
	void set_parent(actor* new_parent)
	{
		assert(new_parent);
		
		// unparent from old parent
		if(has_parent()) {
			get_parent()->m_children.erase(shared_from_this());
		}
		
		new_parent->m_children.insert(shared_from_this());
		m_parent = new_parent;
	}
	
	actor* get_parent() const { return m_parent; }
	bool has_parent() const { return m_parent; }
	
	// rendering
	
	void render_all(const glm::mat3& view_projection_matrix) {
		this->render(view_projection_matrix);
		
		for(auto child : m_children) {
			child->render_all(view_projection_matrix);
		}
	}
	
	// SIGNALS
	//////////
	boost::signals2::signal<void(actor& actor_that_changed)> signal_location_changed;
	boost::signals2::signal<void(actor& actor_that_changed)> signal_rotation_changed;
	boost::signals2::signal<void(actor& actor_that_changed)> signal_scale_changed;
	boost::signals2::signal<void(actor& actor_that_changed)> signal_transform_changed;
	
protected:
	
	// override this for custom rendering
	virtual void render(const glm::mat3& view_projection_matrix) {}
	
};

}  // namespace ge
