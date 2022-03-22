#ifndef ITEARTOR_HPP
#define  ITEARTOR_HPP
#include <iostream>
#include <string>

namespace ft
{
	template <class Iterator>
	class iterator_traits
	{
		public:
			typedef typename Iterator::difference_type			difference_type;
			typedef	typename Iterator::value_type				value_type;
			typedef	typename Iterator::pointer					pointer;
			typedef	typename Iterator::reference				reference;
			typedef	typename Iterator::iterator_category		iterator_category;
	};

	template <class T>
	class iterator_traits<T*>
	{
		public:
			typedef	ptrdiff_t							difference_type;
			typedef T									value_type;
			typedef T*									pointer;
			typedef T&									reference;
			typedef std::random_access_iterator_tag		iterator_category;
	};

	template <class T>
	class iterator_traits<const T*>
	{
		public:
			typedef ptrdiff_t							difference_type;
			typedef T									value_type;
			typedef const T*							pointer;
			typedef const T&							reference;
			typedef std::random_access_iterator_tag		iterator_category;
	};


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
			ft_iterator& operator--() { return (--_ptr); }
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
		return (lhs.base() - rhs.base());
	}

}

#endif