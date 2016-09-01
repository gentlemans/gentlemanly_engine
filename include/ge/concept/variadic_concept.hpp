/**
 * \file variadic_concept.hpp
 *
 * \author Russell Greene
 *
 * Defines a concept that lets you apply a concpet for a varaidic conecpt,
 * checking each one.
 *
 *
 */

#ifndef GE_VARIADIC_CONCEPT_HPP
#define GE_VARIADIC_CONCEPT_HPP

#pragma once

#include <boost/concept_check.hpp>

namespace ge
{
namespace concept
{
/**
 * A concept (to be used with BOOST_CONCEPT_ASSERT((...))) that applys a single
 * unary concept to a
 * varaidc template (as many types as you want!!)
 *
 * The first template parameter is actually a template template that takes in a
 * unary concept.
 * The second parameter is a varaidic template that is the types to be checked.
 * This will give a
 * compile error
 * if any of the types in to_check don't comply with Concept.
 */
template <template <typename> typename Concept, typename... to_check>
struct variadic_concept {
};

// this is just an implementation class, don't include this in the
// documentation.
#ifndef DOXYGEN_SHOULD_SKIP_THIS

template <template <typename> typename Concept, typename first, typename... rest>
struct variadic_concept<Concept, first, rest...> : variadic_concept<Concept, rest...> {
	BOOST_CONCEPT_ASSERT((Concept<first>));
};

#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace ge

}  // namespace concept

#endif  // GE_VARIADIC_CONCEPT_HPP
