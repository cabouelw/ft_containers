#ifndef MAP_HPP
#define  MAP_HPP
#include <iostream>
#include <string>
#include "Pair.hpp"
#include "avl_tree.hpp"
#include "map_Iterator_traits.hpp"
#include "Reverse_iterator.hpp"

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
			typedef	Alloc														allocator_type;
			typedef typename allocator_type::reference							reference;
			typedef typename allocator_type::const_reference					const_reference;
			typedef typename allocator_type::pointer							pointer;
			typedef typename allocator_type::const_pointer						const_pointer;
			typedef avltree<value_type, key_compare, allocator_type>			tree;
			typedef	typename tree::ptr_node										ptr_node;
			typedef	ft_iterator_map<pointer, ptr_node>							iterator;
			typedef	ft_iterator_map<const_pointer, ptr_node>					const_iterator;
			typedef ft_reverse_iterator<iterator>								reverse_iterator;
            typedef ft_reverse_iterator<const_iterator>							const_reverse_iterator;
			typedef	typename iterator_traits<iterator>::difference_type			difference_type;
			typedef	size_t														size_type;
		private:
			tree					_tree;
			allocator_type			_alloc;
			key_compare				_cmp;
		public:
			explicit map(const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type()) : _tree(), _alloc(alloc), _cmp(comp) { }
			template <class InputIterator>
			map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) :
				_tree(), _alloc(alloc), _cmp(comp)
			{
				while (first != last)
				{
					_tree.insert(*first);
					first++;
				}
			}
			map (const map& x) : _alloc(x._alloc), _cmp(x._cmp)
			{
				insert(x.begin(), x.end());
			}
			~map() { }
			map& operator= (const map& x)
			{
				this->erase(this->begin(), this->end());
				insert(x.begin(), x.end());
				_cmp = x._cmp;
				_alloc = x._alloc;
				return (*this);
			}
			iterator begin() { return (iterator(_tree.findMin())); }
			const_iterator begin() const { return (const_iterator(_tree.findMin())); }
			reverse_iterator rbegin() { return (reverse_iterator(this->end())); }
			const_reverse_iterator rbegin() const { return (const_reverse_iterator(this->end())); }
			iterator end() { return (iterator(_tree.getEnd())); }
			const_iterator end() const { return (const_iterator(_tree.getEnd())); }
			reverse_iterator rend() { return (reverse_iterator(begin())); }
			const_reverse_iterator rend() const { return (const_reverse_iterator(begin())); }
			bool empty() const { return((_tree.size() == 0)); }
			size_type size() const { return(_tree.size()); }
			size_type max_size() const { return(_tree.max_size()); }
			mapped_type& operator[] (const key_type& k) {
				ft::pair<key_type, mapped_type> tmp = ft::make_pair(k, mapped_type());
				if (!(_tree.contains(tmp)))
					_tree.insert(tmp);
				ptr_node rslt = _tree.getelm(tmp);
				return (rslt->elm.second);
			}
			pair<iterator, bool> insert (const value_type& val)
			{
				if (_tree.contains(val))
					return (ft::make_pair(iterator(_tree.getelm(val)), false));
				_tree.insert(val);
				return (ft::make_pair(iterator(_tree.getelm(val)), true));
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
					_tree.insert(*first);
					first++;
				}
			}
			void erase (iterator position) { _tree.remove(*position, false); }
			size_type erase (const key_type& k)
			{
				ft::pair<key_type, mapped_type> tmp = ft::make_pair(k, mapped_type());
				_tree.remove(tmp, true);
				return(1);
			}
			void erase(iterator first, iterator last)
			{
				iterator tmp;
				while (first != last)
				{
					tmp = first++;
					_tree.remove((*tmp), false);
					if (first == iterator(_tree.getEnd()))
						return ;
				}
			}
			void swap(map& x) { _tree.swap(x._tree); }
			void clear() { this->erase(this->begin(), this->end()); }
			key_compare key_comp() const { return (key_compare()); }
			value_compare value_comp() const { return (value_compare(_cmp)); }
			iterator find (const key_type& k)
			{
				ptr_node tmp = _tree.getelm(ft::make_pair(k, mapped_type()));
				if (tmp == nullptr)
					return (iterator(_tree.getEnd()));
				return (iterator(tmp));
			}
			const_iterator find (const key_type& k) const
			{
				ptr_node tmp = _tree.getelm(ft::make_pair(k, mapped_type()));
				if (tmp == nullptr)
					return (const_iterator(_tree.getEnd()));
				return (const_iterator(tmp));
			}
			size_type count (const key_type& k) const
			{
				if (_tree.contains(ft::make_pair(k, mapped_type())))
					return (1);
				return (0);
			}
			iterator lower_bound (const key_type& k)
			{
				return (iterator(_tree.lower_bound(ft::make_pair(k, mapped_type()))));
			}
			const_iterator lower_bound (const key_type& k) const
			{
				return (const_iterator(_tree.lower_bound(ft::make_pair(k, mapped_type()))));
			}
			iterator upper_bound (const key_type& k)
			{
				return (iterator(_tree.upper_bound(ft::make_pair(k, mapped_type()))));
			}
			const_iterator upper_bound (const key_type& k) const
			{
				return (const_iterator(_tree.upper_bound(ft::make_pair(k, mapped_type()))));
			}
			pair<const_iterator,const_iterator>	equal_range (const key_type& k) const
			{
				return (ft::make_pair(lower_bound(k), upper_bound(k)));
			}
			pair<iterator,iterator>				equal_range (const key_type& k)
			{
				return (ft::make_pair(lower_bound(k), upper_bound(k)));
			}
			allocator_type get_allocator() const
			{
				return(allocator_type());
			}


	};
}

#endif