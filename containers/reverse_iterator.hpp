#ifndef REVERSE_ITERATOR_HPP
#define  REVERSE_ITERATOR_HPP
#include <iostream>
#include <string>
#include "Iterator_traits.hpp"

namespace ft
{
	template <class T>
	class ft_reverse_iterator
	{
		public:
			typedef T													iterator_type;
			typedef	typename iterator_traits<T>::iterator_category		iterator_category;
			typedef typename iterator_traits<T>::value_type				value_type;
			typedef typename iterator_traits<T>::pointer				pointer;
			typedef typename iterator_traits<T>::reference				reference;
			typedef typename iterator_traits<T>::difference_type		difference_type;
		private:
			iterator_type		_it;
		public:
			ft_reverse_iterator(): _it(nullptr) {}
			explicit ft_reverse_iterator (iterator_type it): _it(it) {}
			template <class Iter>
			ft_reverse_iterator (const ft_reverse_iterator<Iter>& it): _it(it._it) {}
			iterator_type base() const { return (_it); }
			reference operator*() const { return (*--(this->base())); }
			ft_reverse_iterator operator+ (difference_type n) const { return (ft_reverse_iterator(this->base() - n)); }
			ft_reverse_iterator& operator++() { --_it; return (*this); }
			ft_reverse_iterator  operator++(int)
			{
				ft_reverse_iterator it(*this);
				++(*this);
				return (it);
			}
			ft_reverse_iterator& operator+= (difference_type n) { this->base() -= n; return (*this); }
			ft_reverse_iterator operator- (difference_type n) const { return (ft_reverse_iterator(this->base() + n)); }
			ft_reverse_iterator& operator--() { ++this->base(); return (*this); }
			ft_reverse_iterator  operator--(int)
			{
				ft_reverse_iterator it(*this);
				--(*this);
				return (it);
			}
			ft_reverse_iterator& operator-= (difference_type n) { this->base() += n; return (*this); }
			pointer operator->() const { return &(operator*()); }
			reference operator[] (difference_type n) const { return( this->base()[-n-1]); }
	};
	template <class Iterator>
	bool operator==(const ft_reverse_iterator<Iterator>& lhs, const ft_reverse_iterator<Iterator>& rhs)
	{ return (lhs.base() == rhs.base()); }
	template <class Iterator>
	bool operator!= (const ft_reverse_iterator<Iterator>& lhs, const ft_reverse_iterator<Iterator>& rhs)
	{ return (lhs.base() != rhs.base()); }
	template <class Iterator>
	bool operator< (const ft_reverse_iterator<Iterator>& lhs, const ft_reverse_iterator<Iterator>& rhs)
	{ return (lhs.base() > rhs.base()); }
	template <class Iterator>
	bool operator<= (const ft_reverse_iterator<Iterator>& lhs, const ft_reverse_iterator<Iterator>& rhs)
	{ return (lhs.base() >= rhs.base()); }
	template <class Iterator>
	bool operator>  (const ft_reverse_iterator<Iterator>& lhs, const ft_reverse_iterator<Iterator>& rhs)
	{ return (lhs.base() < rhs.base()); }
	template <class Iterator>
	bool operator>=  (const ft_reverse_iterator<Iterator>& lhs, const ft_reverse_iterator<Iterator>& rhs)
	{ return (lhs.base() <= rhs.base()); }
	template <class Iterator>
	ft_reverse_iterator<Iterator> operator+ (typename ft_reverse_iterator<Iterator>::difference_type n, const ft_reverse_iterator<Iterator>& rev_it)
	{
		return (ft_reverse_iterator<Iterator>(rev_it + n));
	}
	template <class Iterator>
	typename ft_reverse_iterator<Iterator>::difference_type operator- (const ft_reverse_iterator<Iterator>& lhs, const ft_reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() - rhs.base());
	}
}

#endif