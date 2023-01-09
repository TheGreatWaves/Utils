#pragma once

////////////////////////
/// VISITOR PATTERN STRUCT
////////////////////////

/**
* A struct used for inlining basic overloads for a variant type.
*
* Example usage: (Overloading for equalily)
*
*	auto equal = std::visist(Overloaded
*	{
*		 // float overload
*		 [this](double d1, double d2) -> bool
*		 {
*			return d1 == d2;
*		 },
*
*        // int overload
*		 [this](int i1, int i2) -> bool
*        {
*			return i1 == i2;
*        },
*
*        // bool overload
*		 [this](int b1, int b2) -> bool
*        {
*			return b1 == b2;
*        }
*	},
*	std::variant value parameter);
*/
template <class... Ts>
struct Overloaded : Ts...
{
	using Ts::operator()...;
};
