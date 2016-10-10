#ifndef GE_ACTOR_HPP
#define GE_ACTOR_HPP

#pragma once

#include "ge/hash_typeindex.hpp"
#include "ge/transform.hpp"

#include <spdlog/spdlog.h>

#include <memory>

#include <glm/glm.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include <boost/container/flat_map.hpp>
#include <boost/container/flat_set.hpp>


namespace ge
{
struct runtime;
/// The class that represents anything that can be placed in the world.
class actor : public std::enable_shared_from_this<actor>
{
	// no shared_ptr because that would be a cyclic reference
	actor* m_parent = nullptr;

	// set for find -- we don't care much about insertion speed, but iteration is more important.
	boost::container::flat_set<std::shared_ptr<actor>> m_children;

	transform m_transform;

	boost::container::flat_map<boost::typeindex::type_index, std::shared_ptr<void>> m_interfaces;

protected:
	// called from `factory`
	actor() noexcept {};

	// so we can use make_shared

public:
	/// Creates an actor of type ActorType
	/// \param parent The parent actor, null for a root actor
	/// \param init_params The initialization paramters, will be passed to ActorType::initialize
	template <typename ActorType = actor, typename... InitParams>
	static std::shared_ptr<ActorType> factory(actor* parent, InitParams&&... init_params)
	{
		assert(parent);

		static_assert(std::is_base_of<actor, ActorType>::value,
			"Cannot use actor::factory on non-actor type.");

		auto ret = std::shared_ptr<ActorType>(new ActorType());
		assert(ret);

		ret->set_parent(parent);
		ret->m_runtime = parent->m_runtime;
		ret->initialize(std::forward<InitParams>(init_params)...);

		return ret;
	}

	/// Creates a root actor of type ActorType
	/// \param runtime The runtime object to create it under
	/// \param init_params The initialization paramters, will be passed to ActorType::initialize
	template <typename ActorType = actor, typename... InitParams>
	static std::shared_ptr<ActorType> root_factory(runtime* runtime, InitParams&&... init_params)
	{
		assert(runtime);

		static_assert(std::is_base_of<actor, ActorType>::value,
			"Cannot use actor::factory on non-actor type.");

		auto ret = std::shared_ptr<ActorType>(new ActorType());
		assert(ret);

		ret->m_runtime = runtime;
		ret->initialize(std::forward<InitParams>(init_params)...);

		return ret;
	}

	// no move or copy -- will be in a shared_ptr
	actor(const actor&) = delete;
	actor(actor&&) = delete;

	/// initializes that class--create another version of this in child actors with parameters
	void initialize(){};

	actor& operator=(const actor&) = delete;
	actor& operator=(actor&&) = delete;

	virtual ~actor();

	/// Gets a std::shared_ptr<actor> from the actor
	/// \param to_share The actor to turn into a std::shared_ptr
	template <typename ActorType>
	static std::shared_ptr<ActorType> shared(ActorType* to_share) noexcept
	{
		static_assert(std::is_base_of<actor, ActorType>::value,
			"Cannot use actor::shared on a non-actor type");

		return std::static_pointer_cast<ActorType>(to_share->shared_from_this());
	}

	// Interface Interface
	//////////////////////

	/// Adds an iterface to the actor. First template parameter is the actor type, second is the
	/// interface.
	template <typename ActorType, typename Interface>
	void add_interface()
	{
		static_assert(
			std::is_base_of<actor, ActorType>::value, "Must pass an actor type into add_interface");

		m_interfaces.emplace(boost::typeindex::type_id<Interface>(),
			Interface::template gen_interface<ActorType>(static_cast<ActorType*>(this)));
	}

	/// Query if this actor implements a certain interface
	template <typename Interface>
	bool implements_interface() const
	{
		auto iter = m_interfaces.find(boost::typeindex::type_id<Interface>());

		return iter != m_interfaces.end();
	}

	/// Get the storage object for a given interface, nullptr if that interface isn't implemented
	template <typename Interface>
	auto get_interface_storage() -> typename Interface::interface_storage*
	{
		auto iter = m_interfaces.find(boost::typeindex::type_id<Interface>());

		if (iter == m_interfaces.end()) return nullptr;

		return static_cast<typename Interface::interface_storage*>(iter->second.get());
	}

	// transform transformation functions
	/////////////////////////////////////

	/// sets the location relative to the parent, if there is one.
	/// \param new_location the new location
	void set_relative_location(glm::vec2 new_location) noexcept
	{
		m_transform.location = new_location;
	}
	/// Gets the location of the actor relative to the parent
	/// \return The relative location
	glm::vec2 get_relative_location() const noexcept { return m_transform.location; }
	/// Sets the rotation relative to the parent.
	/// \param new_rotation the new rotation to apply
	void set_relative_rotation(float new_rotation) noexcept { m_transform.rotation = new_rotation; }
	/// Gets the rotation of the actor relative to the parent
	/// \return The relative rotation
	float get_relative_rotation() const noexcept { return m_transform.rotation; }
	/// Sets the scale of the actor relative to the parent
	/// \param new_scale The relative scale
	void set_relative_scale(glm::vec2 new_scale) noexcept { m_transform.scale = new_scale; }
	/// Gets the scale relative to the parent actor
	/// \return The relative scale
	glm::vec2 get_relative_scale() const noexcept { return m_transform.scale; }
	/// Calculates the absolute location of the actor
	/// \return The absolute location
	glm::vec2 calcuate_absolute_location() const noexcept
	{
		if (has_parent()) {
			glm::vec2 parent_loc = get_parent()->calcuate_absolute_location();
			float parent_rot = get_parent()->calcuate_absolute_rotation();
			return parent_loc +
				   glm::rotate(get_relative_location() * get_parent()->calcuate_absolute_scale(),
					   glm::radians(parent_rot));
		}

		return get_relative_location();
	}
	/// Calculates the absolute rotation of the actor
	/// \return The absolute rotation
	float calcuate_absolute_rotation() const noexcept
	{
		if (has_parent()) {
			return get_parent()->calcuate_absolute_rotation() + get_relative_rotation();
		}

		return get_relative_rotation();
	}
	/// Calculates the absolute scale of the actor
	/// \return The absolute scale
	glm::vec2 calcuate_absolute_scale() const noexcept
	{
		if (has_parent()) {
			return get_parent()->calcuate_absolute_scale() * get_relative_scale();
		}
		return get_relative_scale();
	}

	/// Calculates the model matrix for the actor
	/// \return The model matrix
	glm::mat3 calculate_model_matrix() const noexcept
	{
		glm::mat3 this_model;

		this_model = glm::scale(this_model, get_relative_scale());
		this_model = glm::translate(this_model, get_relative_location());
		this_model = glm::rotate(this_model, get_relative_rotation());

		return has_parent() ? this_model * get_parent()->calculate_model_matrix() : this_model;
	}

	// parent manipulation
	//////////////////////

	/// Sets the parent of the actor, unparenting it from the previous parent
	/// \param new_parent The new parent of the actor
	void set_parent(actor* new_parent) noexcept
	{
		assert(new_parent);

		// unparent from old parent
		if (has_parent()) {
			get_parent()->m_children.erase(shared_from_this());
		}

		new_parent->m_children.insert(shared_from_this());
		m_parent = new_parent;
	}

	/// Gets the parent actor
	/// \return The parent actor if present, otherwise `nullptr`
	actor* get_parent() const noexcept { return m_parent; }
	/// Gets if the actor has a parent.
	/// \return Has a parent?
	bool has_parent() const noexcept { return m_parent != nullptr; }
	/// Propagates  function to all the children
	/// \param func The function to propagate
	template <typename F>
	void propagate_to_children(F&& func)
	{
		std::forward<F>(func)(*this);

		for (auto child : m_children) {
			child->propagate_to_children(std::forward<F>(func));
		}
	}

	/// The runtime object that was passed down from the parent actor
	runtime* m_runtime;
};

}  // namespace ge

#endif  // GE_ACTOR_HPP
