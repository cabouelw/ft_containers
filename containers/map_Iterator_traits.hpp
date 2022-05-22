#ifndef MAP_ITERATOR_TRAITS_HPP
#define  MAP_ITERATOR_TRAITS_HPP
#include <iostream>
#include <string>
#include "Iterator_traits.hpp"
namespace ft
{
	template<class T, class nodeptr>
	class ft_iterator_map
	{
		public:
			typedef T													iterator_type;
			typedef std::bidirectional_iterator_tag						iterator_category;
			typedef typename iterator_traits<T>::value_type				value_type;
			typedef typename iterator_traits<T>::pointer				pointer;
			typedef typename iterator_traits<T>::reference				reference;
			typedef typename iterator_traits<T>::difference_type		difference_type;
			ft_iterator_map(): _ptr(nullptr) {}
			explicit ft_iterator_map (nodeptr it): _ptr(it) {}
			template <class Iter, class ptr_node>
			ft_iterator_map (const ft_iterator_map<Iter, ptr_node>& it): _ptr(it.base()) {}
			nodeptr base() const { return (_ptr); }
			reference operator*() const { return (_ptr->elm); }
			ft_iterator_map& operator++() {
				_ptr = successor();
				return (*this);
			}
			ft_iterator_map  operator++(int)
			{
				ft_iterator_map it(*this);
				++(*this);
				return (it);
			}
			ft_iterator_map& operator--() {
				_ptr = predecessor();
				return (*this);
			}
			ft_iterator_map  operator--(int)
			{
				ft_iterator_map it(*this);
				--(*this);
				return (it);
			}
			pointer operator->() const { return (_ptr->elm); }
			reference operator[] (difference_type n) const { return( _ptr[n]); }
		private:
			nodeptr		_ptr;
			nodeptr    successor()
            {
                nodeptr curr = _ptr;
                if (curr->right != nullptr)
                {
                    curr = curr->right;
                    while (curr->left != nullptr)
                        curr = curr->left;
                    return curr;
                }
                else
                {
                    nodeptr ptr_parent = curr->parnt;
					// std::cout << ptr_parent->elm.first << "daz\n";
                    while (ptr_parent != nullptr && curr == ptr_parent->right)
                    {
                        curr = ptr_parent;
                        ptr_parent = ptr_parent->parnt;
                    }
                    return ptr_parent;
                }
            }
            nodeptr    predecessor()
            {
                nodeptr curr = _ptr;
                if (curr->left != nullptr)
                {
                    curr = curr->left;
                    while (curr->right != nullptr)
                        curr = curr->right;
                    return curr;
                }
                else
                {
                    nodeptr ptr_parent = curr->parnt;
                    while (ptr_parent != nullptr && curr == ptr_parent->left)
                    {
                        curr = ptr_parent;
                        ptr_parent = ptr_parent->parnt;
                    }
                    return ptr_parent;

                }
            }
    };
	template <class Iterator, class nodeptr>
	bool operator==(const ft_iterator_map<Iterator, nodeptr>& lhs, const ft_iterator_map<Iterator, nodeptr>& rhs)
	{ return (lhs.base() == rhs.base()); }
	template <class Iterator, class nodeptr>
	bool operator!= (const ft_iterator_map<Iterator, nodeptr>& lhs, const ft_iterator_map<Iterator, nodeptr>& rhs)
	{ return (lhs.base() != rhs.base()); }
}

#endif