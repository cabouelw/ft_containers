#ifndef MAP_HPP
#define  MAP_HPP
#include <iostream>
#include <string>
#include "Pair.hpp"
#include "avl_tree.hpp"
#include "map_Iterator_traits.hpp"

namespace ft
{
	template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<pair<const Key,T> > >
	class map
	{
		public:
			typedef Key													key_type;
			typedef T													mapped_type;
			typedef pair<const Key, T>									value_type;
			typedef	Compare												key_compare;
			class value_compare : std::binary_function<value_type, value_type, bool>
			{
				friend class map;
				protected:
					Compare comp;
					value_compare(Compare c) : comp(c)
					{
					}
				public:
					bool operator()(const value_type& x, const value_type& y)
					{
						return comp(x.first, y.first);
					}
			};
			// typedef	typename value_compare								value_compare;
			typedef	Alloc												allocator_type;
			typedef typename allocator_type::reference					reference;
			typedef typename allocator_type::const_reference			const_reference;
			typedef typename allocator_type::pointer					pointer;
			typedef typename allocator_type::const_pointer				const_pointer;
			typedef avltree<value_type, key_compare, allocator_type>	tree;
			typedef	typename tree::ptr_node								ptr_node;
			typedef	ft_iterator_map<pointer, ptr_node>					iterator;
			typedef	ft_iterator_map<const_pointer, ptr_node>			const_iterator;
			// r_iterator;
			typedef	typename iterator_traits<iterator>::difference_type			difference_type;
			typedef	size_t												size_type;
			explicit map(const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type()): _tree(), _alloc(alloc), _cmp(comp) { }
			template <class InputIterator>
			map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) :
				_tree(), _cmp(comp), _alloc(alloc)
			{
				while (first != last)
				{
					_tree.insert(*first);
					first++;
				}
			}
			map (const map& x) : _cmp(x._cmp), _alloc(x._alloc)
			{
				insert(x.begin(), x.end());
			}
			~map() { }
			map& operator= (const map& x)
			{
				insert(x.begin(), x.end());
				_cmp = x._cmp;
				_alloc = x._alloc;
			}
			iterator begin() { return (iterator(_tree.findMin())); }
			const_iterator begin() const { return (const_iterator(_tree.findMin())); }
			iterator end() { return (iterator(_tree.findMax())); }
			const_iterator end() const { return (const_iterator(_tree.findMax())); }
			bool empty() const { return((_tree._nodecount == 0)); }
			size_type size() const { return(_tree._nodecount); }
			size_type max_size() const { return(_tree->_nodecount); }
			mapped_type& operator[] (const key_type& k) {
				if (!(_tree.contains(make_pair(k, mapped_type()))))
					_tree.insert(make_pair(k, mapped_type()));
				ptr_node rslt = _tree.getelm(make_pair(k, mapped_type()));
				return (rslt->elm.second);
			}
			pair<iterator, bool> insert (const value_type& val)
			{
				if (!(_tree.contains(val)))
					_tree.insert(val);
				return (make_pair(iterator(), true));
			}
			iterator insert (iterator position, const value_type& val)
			{
				static_cast<void>(position);
				ptr_node	node;
				node = _tree.getelm(val);
				if (_tree.contains(val))
					return iterator(node);
				_tree.insert(val);
				node = _tree.getelm(val);
				return (iterator(node));
			}
			template <class InputIterator>
			void insert (InputIterator first, InputIterator last)
			{
				while (first != last)
				{
					std::cout  << (*first).first << "|||\n";
					_tree.insert(*first);
					++first;
				}
			}
			// pair<iterator,bool> insert (const value_type& val)
			// {

			// }
			// iterator insert (iterator position, const value_type& val)
			private:
				tree					_tree;
				allocator_type			_alloc;
				key_compare				_cmp;


	};
}

#endif