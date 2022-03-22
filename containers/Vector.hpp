/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 14:06:41 by cabouelw          #+#    #+#             */
/*   Updated: 2022/03/22 20:31:07 by cabouelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define  VECTOR_HPP
#include <iostream>
#include <string>
#include "iterator.hpp"

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
			typedef	typename allocator_type::reference					reference;
			typedef typename allocator_type::const_reference			const_reference;
			typedef typename allocator_type::difference_type			difference_type;
			typedef	typename allocator_type::size_type					size_type;

		private:
			pointer	_arry;
			size_t	_size_type;
			size_t	_capacity;
			Alloc	_alloc;
		public:
			explicit vector (const allocator_type& alloc = allocator_type()): _arry(nullptr), _size_type(0), _capacity(0), _alloc(alloc) {}
			explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
				: _alloc(alloc), _size_type(n), _capacity(n)
			{
				_arry = _alloc.allocate(_capacity);
				for (size_t i = 0; i < _size_type; i++)
					_arry[i] = val;
			}
			template <class InputIterator>
			// vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
			// 	: _alloc(alloc), _size_type(0), _capacity(0)
			// {
			// }
			vector (const vector& x) { *this = x; }
			vector& operator= (const vector& x) {
				if (this == &x)
					return (*this);
				this->_capacity = x._capacity;
				this->_size_type = x._size_type;
				_arry = _alloc.allocate(_capacity);
				for(int i = 0; i < _size_type; i++)
                        _arry[i] = x[i];
			}
			~vector() {
				delete [] _arry;
				_size_type = 0;
				_capacity = 0;
			}
			iterator begin() {
				return (iterator(_arry));
			}
			const_iterator cbegin() const {
				return (const_iterator(_arry));
			}
			iterator end() {
				return (iterator(_arry + _size_type));
			}
			const_iterator cend() const {
				return (const_iterator(_arry + _size_type));
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
				return (this->_capacity);
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
				size_t tmp_size = last - first;
				if (tmp_size > this->_capacity)
				{
					pointer tmp_arry = this->_arry;
					this->_arry = _alloc.allocate(tmp_size);
					for (size_t i = 0; i < tmp_size; i++)
						this->_arry[i] = tmp_arry[i];
					std::cout << "hna\n"; // TODO
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
				
			}






			
	};
}
#endif