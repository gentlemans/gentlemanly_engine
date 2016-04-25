#pragma once

#include <boost/type_index.hpp>

#include <unordered_map>
#include <type_traits>

#include <boost/mpl/transform.hpp>
#include <boost/mpl/list.hpp>
#include <boost/type_traits/add_pointer.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/find.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/equal.hpp>
#include <boost/mpl/joint_view.hpp>

namespace std {
template<>
struct hash<boost::typeindex::type_index>
{
	size_t operator()(const boost::typeindex::type_index& ti) const
	{
		return ti.hash_code();
	}
};
}

namespace ge {

template<typename... _component_types>
class entity
{
	std::unordered_map<boost::typeindex::type_index, void*> components;
public:
	
	using component_types = 
	
	entity()
	{
		using raw_types = boost::mpl::list<_component_types...>;
		using types_with_ptr = typename boost::mpl::transform<raw_types, boost::add_pointer<boost::mpl::placeholders::_1>>::type;
		
		boost::mpl::for_each<types_with_ptr>([this](auto ptr_t)
		{
			using type = std::remove_pointer_t<decltype(ptr_t)>;
			
			components[boost::typeindex::type_id<type>()] = type{};
			
			using deps = typename type::dependencies;
			
			
			
		});
		
	}
	
	template<typename T>
	T& get_component()
	{
		auto index = boost::typeindex::type_id<T>();
		
		auto iter = components.find(index);
		if(iter == components.end())
		{
			throw std::out_of_range("Could not find component " + boost::typeindex::type_id<T>().pretty_name() + " in entity");
		}
		
		return *static_cast<T*>(iter);
	}
};


} // namespace ge
