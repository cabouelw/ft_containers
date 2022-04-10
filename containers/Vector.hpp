/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 14:06:41 by cabouelw          #+#    #+#             */
/*   Updated: 2022/04/10 13:29:35 by cabouelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define  VECTOR_HPP
#include <iostream>
#include <string>
#include "iterator.hpp"
#include "reverse_iterator.hpp"

namespace ft
{
	template < class T, class Alloc = std::allocator<T> >
	class vector
	{
		public:
			typedef	T													value_type;
			typedef	Alloc												allocator_type;
			typedef typename allocator_type::pointer					pointer;
			typedef typename allocator_type::const_pointer				const_pointer;
			typedef ft::ft_iterator<pointer>							iterator;
			typedef ft::ft_iterator<const_pointer>						const_iterator;
			typedef ft::ft_reverse_iterator<iterator>					reverse_iterator;
			typedef ft::ft_reverse_iterator<const_iterator>				const_reverse_iterator;
			typedef	typename allocator_type::reference					reference;
			typedef typename allocator_type::const_reference			const_reference;
			typedef typename allocator_type::difference_type			difference_type;
			typedef	typename allocator_type::size_type					size_type;

		private:
			pointer			_arry;
			unsigned long	_size_type;
			size_t			_capacity;
			Alloc			_alloc;
		public:
			explicit vector (const allocator_type& alloc = allocator_type()): _arry(nullptr), _size_type(0), _capacity(0), _alloc(alloc) {}
			explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
				: _size_type(n), _capacity(n), _alloc(alloc)
			{
				_arry = _alloc.allocate(_capacity);
				for (size_t i = 0; i < _size_type; i++)
					_arry[i] = val;
			}
			template <class InputIterator>
			vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
				: _alloc(alloc)
			{
				this->_size_type = last - first;
				this->_capacity = this->_size_type;
				this->_arry = this->_alloc.allocate(this->_capacity);
				for (size_t i = 0; i < this->_size_type; i++)
				{
					this->_arry[i] = *first;
					first++;
				}
			}
			vector (const vector& x) { *this = x; }
			vector& operator= (const vector& x) {
				if (this == &x)
					return (*this);
				if (this->_capacity)
					this->_alloc.deallocate(this->_arry, this->_capacity);
				this->_arry = this->_alloc.allocate(x._capacity);
				this->_size_type = x._size_type;
				this->_capacity = x._capacity;
				for(size_type i = 0; i < _size_type; i++)
                        _arry[i] = x[i];
				return *this;
			}
			~vector() {
				this->_alloc.deallocate(this->_arry, this->_capacity);
				this->_size_type = 0;
				this->_capacity = 0;
			}
			iterator begin() {
				return (iterator(_arry));
			}
			const_iterator begin() const {
				return (const_iterator(_arry));
			}
			iterator end() {
				return (iterator(_arry + _size_type));
			}
			const_iterator end() const {
				return (const_iterator(_arry + _size_type));
			}
			reverse_iterator rbegin() {
				return (reverse_iterator(iterator(_arry + _size_type)));
			}
			reverse_iterator rend() {
				return (reverse_iterator(iterator(_arry)));
			}
			const_reverse_iterator rbegin() const {
				return (const_reverse_iterator(const_iterator(_arry + _size_type)));
			}
			const_reverse_iterator rend() const {
				return (const_reverse_iterator(const_iterator(_arry)));
			}
			reference operator[] (size_type n) {
				return (_arry[n]);
			}
			const_reference operator[] (size_type n) const {
				return (_arry[n]);
			}
			size_type size() const {
				return (this->_size_type);
			}
			size_type max_size() const {
				return (_alloc.max_size());
			}
			void resize (size_type n, value_type val = value_type()) {
				if (n < this->_size_type)
					this->_size_type = n;
				else if (n > this->_size_type)
				{
					pointer tmp = _arry;
					size_t tmp_capacity = _capacity;
					if (_capacity < n)
					{
						if (n > (_capacity * 2))
							_arry = _alloc.allocate(n);
						else
							_arry = _alloc.allocate((_capacity * 2));
						_capacity = (n > (_capacity * 2)) ? n : (_capacity * 2);
					}
					size_type tn = 0;
					while (tn <= n)
					{
						if (tn < _size_type)
							_arry[tn] = tmp[tn];
						else
							_arry[tn] = val;
						tn++;
					}
					if (tmp_capacity != _capacity)
						_alloc.deallocate(tmp, tmp_capacity);
					_size_type = n;
				}
			}
			size_type capacity() const {
				return (this->_capacity);
			}
			bool empty() const {
				return (this->_size_type == 0);
			}
			void reserve (size_type n) {
				if (n > this->_capacity)
				{
					size_t tmp_capacity = this->_capacity;
					if (n > (this->_capacity * 2))
						_capacity  = n;
					else
						_capacity  *= 2;
					pointer tmp = _arry;
					_arry = _alloc.allocate(_capacity);
					for (size_t i = 0; i < _size_type; i++)
						_arry[i] = tmp[i];
					_alloc.deallocate(tmp, tmp_capacity);
				}
			}
			reference at (size_type n) {
				if (n >= this->_size_type)
					throw std::out_of_range("vector");
				return (_arry[n]);
			}
			const_reference at (size_type n) const {
				if (n >= this->_size_type)
					throw std::out_of_range("vector");
				return (_arry[n]);
			}
			reference front() {
				return (*_arry);
			}
			const_reference front() const {
				return (*_arry);
			}
			reference back() {
				return (_arry[_size_type - 1]);
			}
			const_reference back() const {
				return (_arry[_size_type - 1]);
			}
			template <class InputIterator>
			void assign (InputIterator first, InputIterator last) {
				size_type tmp_size = last - first;
				if (tmp_size > this->_capacity)
				{
					pointer tmp_arry = this->_arry;
					this->_arry = _alloc.allocate(tmp_size);
					for (size_t i = 0; i < this->_size_type; i++)
						this->_arry[i] = tmp_arry[i];
					this->_alloc.deallocate(tmp_arry, this->_capacity);
					this->_capacity = tmp_size;
				}
				for (size_t i = 0; i < tmp_size; i++)
				{
					this->_arry[i] = *first;
					++first;
				}
				this->_size_type = tmp_size;
			}
			void assign (size_type n, const value_type& val) {
				if (n > this->_capacity)
				{
					pointer tmp_arry = this->_arry;
					this->_arry = _alloc.allocate(n);
					for (size_t i = 0; i < this->_size_type; i++)
						this->_arry[i] = tmp_arry[i];
					this->_alloc.deallocate(tmp_arry, this->_capacity);
					this->_capacity = n;
				}
				for (size_t i = 0; i < n; i++)
					this->_arry[i] = val;
				this->_size_type = n;
			}
			void push_back (const value_type& val) {
				if (this->_size_type == this->_capacity)
				{
					pointer tmp_arry = this->_arry;
					this->_arry = _alloc.allocate((this->_capacity * 2));
					for (size_t i = 0; i < this->_size_type; i++)
						this->_arry[i] = tmp_arry[i];
					this->_alloc.deallocate(tmp_arry, this->_capacity);
					this->_capacity = (this->_capacity) ? (this->_capacity * 2) : 1;
				}
				this->_arry[this->_size_type] = val;
				this->_size_type++;
			}
			void pop_back() {
				// if (this->_size_type)
					this->_size_type--;
			}
			iterator insert (iterator position, const value_type& val) {
				size_type pos = ((position - this->begin()) < 0) ? 0 : (position - this->begin());
				int insrt = (position - this->begin());
				pointer tmp_arry = this->_arry;
				size_t old_size = this->_size_type;
				size_type i = old_size;
				if (this->_size_type == this->_capacity)
				{
					size_t new_capacity = (this->_capacity * 2);
					this->_arry = _alloc.allocate(new_capacity);
					this->_alloc.deallocate(tmp_arry, this->_capacity);
					this->_capacity = new_capacity;
					this->_size_type = (this->_size_type < pos) ? pos : this->_size_type;
					for (i = 0; i <= old_size; i++)
						this->_arry[i] = tmp_arry[i];
				}
				size_type j = old_size;
				while (i != pos && pos <= old_size)
				{
					this->_arry[i] = tmp_arry[j--];
					if (!i)
						break;
					--i;
				}
				this->_arry[pos] = (insrt >= 0) ? val : 0;
				this->_size_type++;
				return (this->begin() + pos);
			}
			void insert (iterator position, size_type n, const value_type& val) {
				size_type pos = position - this->begin();
				pointer tmp_arry = this->_arry;
				size_t old_size = this->_size_type;
				size_type i = old_size;
				this->_size_type = old_size + n;
				if (this->_size_type > this->_capacity)
				{
					size_t new_capacity = ((this->_capacity * 2) > (this->_size_type + n)) ? (this->_capacity * 2) : (this->_size_type + n);
					this->_arry = _alloc.allocate(new_capacity);
					for (i = 0; i < this->_capacity; i++)
						this->_arry[i] = tmp_arry[i];
					this->_size_type = (pos >= old_size) ? (pos + n) : (old_size + n);
					this->_alloc.deallocate(tmp_arry, this->_capacity);
					this->_capacity = new_capacity;
				}
				i = old_size + n;
				while (i != pos && pos <= old_size)
				{
					this->_arry[i] = this->_arry[i - n];
					if (!i)
						break;
					--i;
				}
				i = 0;
				while (i < n)
				{
					this->_arry[pos + i] = val;
					i++;
				}
			}
			template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last) {
				size_type pos = position - this->begin();
				pointer tmp_arry = this->_arry;
				size_t old_size = this->_size_type;
				size_type i = old_size;
				size_type n = (last - first);
				if ((old_size + n) > this->_capacity)
				{
					size_t new_capacity = ((this->_capacity * 2) > (old_size + n)) ? (this->_capacity * 2) : (old_size + n);
					this->_arry = _alloc.allocate(new_capacity);
					for (i = 0; i < this->_capacity; i++)
						this->_arry[i] = tmp_arry[i];
					old_size = (pos >= old_size) ? (pos) : (old_size);
					this->_alloc.deallocate(tmp_arry, this->_capacity);
					this->_capacity = new_capacity;
				}
				i = old_size + n;
				while (i != pos && pos <= old_size)
				{
					this->_arry[i] = this->_arry[i - n];
					if (!i)
						break;
					--i;
				}
				i = 0;
				for (InputIterator idx = first; idx != last; idx++)
				{
					this->_arry[pos + i] = *idx;
					i++;
				}
				this->_size_type = old_size + n;
			}
			iterator erase (iterator position) {
				size_type pos = position - this->begin();
				this->_size_type -= (this->_size_type > 0) ? 1 : 0;
				for (size_type i = pos; i < (this->size() + 1); i++)
					this->_arry[i] = this->_arry[i + 1];
				return (this->begin() + pos);
			}
			iterator erase (iterator first, iterator last) {
				size_type size = last - first;
				size_type pos = first - this->begin();
				this->_size_type -= (size <= this->_size_type) ? size : this->_size_type;
				if ((pos + size) >= this->size())
					return (this->begin() + pos);
				for (size_type i = pos; i < (this->size() + size); i++)
					this->_arry[i] = this->_arry[i + size];
				return (this->begin() + pos);
			}

			void swap (vector& x) {
				vector<T> tmp;
				tmp = *this;
				*this = x;
				x = tmp;
			}
			void clear() {
				this->_size_type = 0;
			}
			allocator_type get_allocator() const {
				// allocator_type tmp = _alloc;
				return _alloc;
			}
	};
	template <class InputIterator1, class InputIterator2>
	bool equal ( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2 )
	{
		while (first1 != last1) {
			if (*first1 != *first2)
				return false;
			++first1;
			++first2;
		}
		return true;
	}
	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
                                InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || *first2 < *first1)
				return false;
			else if (*first1 < *first2)
				return true;
			++first1;
			++first2;
		}
		return (first2 != last2);
	}
	
	template <class T, class Alloc>
	bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return (equal(lhs.begin(), lhs.end(), rhs.begin()));
	}
	template <class T, class Alloc>
	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return (!(lhs == rhs));
	}
	template <class T, class Alloc>
	bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return (lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}
	template <class T, class Alloc>
	bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return (rhs < lhs);
	}
	template <class T, class Alloc>
	bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return (!(rhs < lhs));
	}
	template <class T, class Alloc>
	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return (!(lhs < rhs));
	}
	template <class T, class Alloc>
	void swap (vector<T,Alloc>& x, vector<T,Alloc>& y) {
		x.swap(y);
	}
}
#endif