#ifndef ITERATOR_HPP
#define  ITERATOR_HPP
#include <iostream>
#include <string>
#include "iterator_traits.hpp"

namespace ft
{
	template <class T>
	class ft_iterator
	{
		public:
			typedef T													iterator_type;
			typedef	typename iterator_traits<T>::iterator_category		iterator_category;
			typedef typename iterator_traits<T>::value_type				value_type;
			typedef typename iterator_traits<T>::pointer				pointer;
			typedef typename iterator_traits<T>::reference				reference;
			typedef typename iterator_traits<T>::difference_type		difference_type;
		private:
			iterator_type		_ptr;
		public:
			ft_iterator(): _ptr(nullptr) {}
			explicit ft_iterator (iterator_type it): _ptr(it) {}
			// ft_iterator (iterator_type it): _ptr(it) {}
			template <class Iter>
			ft_iterator (const ft_iterator<Iter>& it): _ptr(it._ptr) {}
			iterator_type base() const { return (_ptr); }
			reference operator*() const { return (*_ptr); }
			ft_iterator operator+ (difference_type n) const { return (ft_iterator(_ptr + n)); }
			ft_iterator& operator++() { ++_ptr; return (*this); }
			ft_iterator  operator++(int)
			{
				ft_iterator it(*this);
				++(*this);
				return (it);
			}
			ft_iterator& operator+= (difference_type n) { _ptr =+ n; return (*this); }
			ft_iterator operator- (difference_type n) const { return (ft_iterator(_ptr - n)); }
			ft_iterator& operator--() { --_ptr; return (*this); }
			ft_iterator  operator--(int)
			{
				ft_iterator it(*this);
				--(*this);
				return (it);
			}
			ft_iterator& operator-= (difference_type n) { _ptr =- n; return (*this); }
			pointer operator->() const { return (_ptr); }
			reference operator[] (difference_type n) const { return( _ptr[n]); }

	};
	template <class Iterator>
	bool operator==(const ft_iterator<Iterator>& lhs, const ft_iterator<Iterator>& rhs)
	{ return (lhs.base() == rhs.base()); }
	template <class Iterator>
	bool operator!= (const ft_iterator<Iterator>& lhs, const ft_iterator<Iterator>& rhs)
	{ return (lhs.base() != rhs.base()); }
	template <class Iterator>
	bool operator< (const ft_iterator<Iterator>& lhs, const ft_iterator<Iterator>& rhs)
	{ return (lhs.base() < rhs.base()); }
	template <class Iterator>
	bool operator<= (const ft_iterator<Iterator>& lhs, const ft_iterator<Iterator>& rhs)
	{ return (lhs.base() <= rhs.base()); }
	template <class Iterator>
	bool operator>  (const ft_iterator<Iterator>& lhs, const ft_iterator<Iterator>& rhs)
	{ return (lhs.base() > rhs.base()); }
	template <class Iterator>
	bool operator>=  (const ft_iterator<Iterator>& lhs, const ft_iterator<Iterator>& rhs)
	{ return (lhs.base() >= rhs.base()); }
	template <class Iterator>
  	ft_iterator<Iterator> operator+ ( typename ft_iterator<Iterator>::difference_type n, const ft_iterator<Iterator>& it)
	{
		return (ft_iterator<Iterator>(it.base() + n));
	}
	template <class Iterator>
	typename ft_iterator<Iterator>::difference_type operator- ( const ft_iterator<Iterator>& lhs, const ft_iterator<Iterator>& rhs)
	{
		return (rhs.base() - lhs.base());
	}
}

#endif