#pragma once

#include <boost/concept_check.hpp>

namespace ge
{
namespace concept
{

template<template <typename> typename Concept, typename... types>
struct variadic_concept {};

template<template <typename> typename Concept, typename first, typename... rest>
struct variadic_concept<Concept, first, rest...> : variadic_concept<Concept, rest...>
{
	BOOST_CONCEPT_ASSERT((Concept<first>));
};

} // namespace ge

} // namespace concept
