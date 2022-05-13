#ifndef MAP_HPP
#define  MAP_HPP
#include <iostream>
#include <string>
#include "Pair.hpp"

namespace ft
{
	template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<pair<const Key,T> > >
	class map
	{
		public:
			typedef pair<const Key, T>			value_type;
			typedef Key							key_type;
			typedef T							mapped_type;
			typedef	Compare						key_compare;
			typedef	Alloc						allocator_type;
			typedef value_type&					reference;
			typedef const value_type&			const_reference;




	};
}

#endif