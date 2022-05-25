#ifndef AVL_TREE_HPP
#define  AVL_TREE_HPP
#include <iostream>
#include <queue>
#include <fstream>
#include <iomanip>
#include <math.h>

namespace ft
{
	template <class T>
	struct Node
	{
		T		elm;
		Node	*left;
		Node	*right;
		Node	*parnt;
		int		height;
		int		bf;
		Node(const T &value): elm(value), left(nullptr), right(nullptr), parnt(nullptr), height(0), bf(0)
		{
		}
		Node(const T &value, int keep): elm(value)
		{
			keep = 0;
		}
	};
	template <class Type> struct rebind {
		typedef std::allocator<Type> other;
	};
	template <class T, class compare, class Alloc>
	class avltree {
		public:
			typedef T																				value_type;
			typedef Node<T>*																		ptr_node;
			typedef typename Alloc::template rebind<Node<value_type> >::other						allocator_type;
			typedef compare																			key_compare;
			typedef size_t																			size_type;
			avltree(const allocator_type& alloc = allocator_type(), const key_compare& comp = key_compare())
				: _root(nullptr), _alloc(alloc), _cmp(comp), _nodecount(0) {
					_end = _alloc.allocate(1);
					_end->left = _root;
			}
			size_type						height()
			{
				if (_root == nullptr)
					return 0;
				return (_root->height);
			}
			size_type						size() const
			{
				return (_nodecount);
			}
			bool isEmpty()  
			{
				return (_nodecount == 0);
			}
			bool							contains(T value)
			{
				return contains(_root, value);
			}
			ptr_node						&getelm(T value)
			{
				return (getelm(value, _root));
			}
			void							insert(T value) {
				if (!_root)
					length = 0;
				this->_root = insert(this->_root, value, this->_end);
				_nodecount++;
				if (length < getLenght(value.first))
					length = getLenght(value.first);
			}
			bool							remove(T elem, bool key)
			{
				if (contains(_root, elem))
				{
					_root = remove(_root, (!key) ? elem : getelm(elem, _root)->elm);
					_nodecount--;
					return true;
				}
				return false;
			}
			int								getLenght(int data)
			{
				return (std::to_string(data).length());
			}
			int								getLenght(std::string data)
			{
				return (data.length());
			}
			void							print()
			{
				if (!_root)
					return ;
				std::cout << "| number of nodes : " << _nodecount << " | tree height: " << _root->height << " |\n";
				std::cout << "lenght : " << length << " |\n";
				// printing(root);
				levelOrder(_root);
			}
			void							levelOrder(ptr_node node)
			{
				std::ofstream	outfile("outfile");
				std::queue<ptr_node > q;
				ptr_node empty = _alloc.allocate(0);
				int	spaces = 0;
				int	currentSpaces = 0;
				int	level = 0;
				int	childs = 0;
				int	repeat;
				int	height = node->height;
				length += 2;

				q.push(_root);
				while (height >= 0)
				{
					ptr_node current = q.front();
					if (current->left)
						q.push(current->left);
					else
						q.push(empty);
					if (current->right)
						q.push(current->right);
					else
						q.push(empty);
					q.pop();
					currentSpaces = (pow(2, height) * length) - length;
					if (level && (childs == (pow(2, level) - 1)))
					{
						repeat = pow(2, level);
						spaces = currentSpaces;
						while (spaces--)
							outfile << " ";
						while (--repeat)
						{
							if (repeat % 2)
							{
								spaces = (currentSpaces * 2) + (length * 3) - 2;
								outfile << "+";
								while (spaces--)
									outfile << "-";
								outfile << "+";
							}
							else
							{
								spaces = (currentSpaces * 2) + (length * 1);
								while (spaces--)
									outfile << " ";
							}
						}
						outfile << "\n";
					}
					spaces = currentSpaces;
					while (spaces--)
						outfile << " ";
					outfile << "(";
					repeat = (length - 2) - getLenght(current->elm.first);
					while (repeat--)
						outfile << " ";
					outfile << current->elm.first;
					outfile << ")";
					spaces = currentSpaces + length;
					while (childs && spaces--)
						outfile << " ";
					if (!childs)
					{
						height--;
						level++;
						childs = pow(2, level);
						outfile << "\n";
					}
					childs--;
				}
			}
			ptr_node							&serch(T &node)
			{
				ptr_node tmp = _root;
				while (tmp)
				{
					if (_cmp(node, tmp->elm))
						tmp = tmp->left;
					else if (_cmp(tmp->elm, node))
						tmp = tmp->right;
					else
						return (tmp);
				}
				return (tmp);
			}
			ptr_node							findMax () const 
			{
				ptr_node node = _root;
				if (node == nullptr)
					return (_end);
				while(node->right != nullptr)
					node = node->right;
				return (node);
			}
			ptr_node							findMin ()
			{
				ptr_node node = _root;
				if (node == nullptr)
					return (_end);
				while(node->left != nullptr)
					node = node->left;
				return (node);
			}
			const ptr_node						findMin () const
			{
				ptr_node node = _root;
				if (node == nullptr){
					const ptr_node tmp = _end;
					return (tmp);
				}
				while(node->left != nullptr)
					node = node->left;
				return (node);
			}
			ptr_node							getEnd() const {return (_end);}
			void								swap(avltree &swp)
			{
				size_type		nodecount = swp._nodecount;
				key_compare		cmp = swp._cmp;
				allocator_type	alloc = swp._alloc;
				ptr_node		end = swp._end;
				ptr_node		root = swp._root;

				swp._alloc = _alloc;
				_alloc = alloc;
				swp._cmp = _cmp;
				_cmp = cmp;
				swp._end = _end;
				_end = end;
				swp._nodecount = _nodecount;
				_nodecount = nodecount;
				swp._root = _root;
				_root = root;
			}
			ptr_node							increment(ptr_node curr)
			{
				if (curr->right != nullptr)
				{
					curr = curr->right;
					while (curr->left != nullptr)
						curr = curr->left;
					return (curr);
				}
				else
				{
					ptr_node ptr_parnt = curr->parnt;
					while (ptr_parnt != nullptr && curr == ptr_parnt->right)
					{
						curr = ptr_parnt;
						ptr_parnt = ptr_parnt->parnt;
					}
					return (ptr_parnt);
				}
			}
			ptr_node							lower_bound(value_type val)
			{
				ptr_node node = findMin();
				while (node != _end)
				{
					if (!_cmp(node->elm.first, val.first))
						return (node);
					node = increment(node);
				}
				return (_end);
			}
			ptr_node							upper_bound(value_type val)
			{
				ptr_node node = findMax();
				while (node != _end)
				{
					if (_cmp(val.first, node->elm.first))
						return (node);
					node = increment(node);
				}
				return (_end);
			}
			size_type							max_size() const { return (_alloc.max_size()); }
		private:
			ptr_node			_root;
			ptr_node			_end;
			allocator_type		_alloc;
			key_compare			_cmp;
			size_type			_nodecount;
			int					length;
			ptr_node	&getelm(T value, ptr_node &root)
			{
				if (root == nullptr)
					return (root);
				if (_cmp(value.first, root->elm.first))
					return getelm(value, root->left);
				if (_cmp(root->elm.first, value.first))
					return getelm(value, root->right);
				return (root);
			}
			bool contains(ptr_node node,T value)
			{
				if (node == nullptr)
					return (false);
				if (_cmp(value.first, node->elm.first))
					return contains(node->left, value);
				if (_cmp(node->elm.first, value.first))
					return contains(node->right, value);
				return (true);
			}
			ptr_node insert(ptr_node node, T &value, ptr_node &prnt)
			{
				if (node == nullptr)
				{
					node = _alloc.allocate(1);
					_alloc.construct(node, value);
					_end->left = _root;
					node->parnt = prnt;
					// std::cout << "node:" << node->elm.first << "|prnt:" << prnt->elm.first << "\n";
					return (node);
				}
				if (_cmp(value.first, node->elm.first))
					node->left = insert(node->left, value, node);
				else
					node->right = insert(node->right, value, node);
				update(node);
				return balance(node);
			}
			void update(ptr_node &node)
			{
				int	leftheight = (node->left == NULL) ? -1 : node->left->height;
				int	rightheight = (node->right == NULL) ? -1 : node->right->height;

				node->height = 1 + ((leftheight > rightheight) ? leftheight : rightheight);
				node->bf = (rightheight - leftheight);
			}
			ptr_node balance(ptr_node node)
			{
				if (node->bf == -2) {
					if (node->left->bf <= 0)
						return leftLeftCase(node);
					else
						return leftRightCase(node);
				}
				else if (node->bf == 2)
				{
					if (node->right->bf >= 0)
						return rightRightCase(node);
					else
						return rightLeftCase(node);
				}
				return node;
			}
			ptr_node leftLeftCase (ptr_node node){
				return rightRotation(node) ;
			}
			ptr_node leftRightCase (ptr_node node) {
				node->left = leftRotation(node->left);
				return leftLeftCase(node);
			}
			ptr_node rightRightCase (ptr_node node) {
				return leftRotation(node);
			}
			ptr_node rightLeftCase (ptr_node node) {
				node->right = rightRotation(node->right);
				return rightRightCase(node);
			}
			ptr_node leftRotation (ptr_node &node)
			{
				ptr_node	parnt = node->parnt;
				ptr_node	root = node->right;
				node->right = root->left;
				node->parnt = root;
				root->left = node;
				root->parnt = parnt;
				update(node);
				update(root);
				return (root);
			}
			ptr_node rightRotation(ptr_node &node)
			{
				ptr_node	parnt = node->parnt;
				ptr_node	root = node->left;
				node->left = root->right;
				node->parnt = root;
				root->right = node;
				root->parnt = parnt;
				update(node);
				update(root);
				return (root);
			}
			ptr_node remove (ptr_node &node, T &elem)
			{
				if (!node)
					return (nullptr);
				if (elem < node->elm)
					node->left = remove(node->left, elem);
				else if (elem > node->elm)
					node->right = remove(node->right, elem);
				else
				{
					if (node->left == nullptr || node->right == nullptr)
					{
						ptr_node prnt = node->parnt;
						ptr_node tmp = (node->left == nullptr) ? node->right : node->left;
						_alloc.deallocate(node, 1);
						if (tmp)
							tmp->parnt = prnt;
						return (tmp);
					}
					else
					{
						if (node->left->height > node->right->height)
						{
							_alloc.construct(node, findMax(node->left), 1);
							node->left = remove(node->left, node->elm);
						}
						else
						{
							_alloc.construct(node, findMin(node->right), 1);
							node->right = remove(node->right, node->elm);
						}
					}
				}
				update(node);
				return (balance(node));
			}
			T findMin (ptr_node node)
			{
				while(node->left != nullptr)
					node = node->left;
				return node->elm;
			}
			T findMax (ptr_node node)
			{
				while (node->right != nullptr)
					node = node->right;
				return node->elm;
			}
	};
}

#endif