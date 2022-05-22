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
			// avltree(T value): _root(nullptr), _alloc(allocator_type()), _cmp(key_compare()), _nodecount(0)
			// {
			// 	insert(value);
			// }
			int height()
			{
				if (_root == nullptr)
					return 0;
				return (_root->height);
			}
			int size()
			{
				return (_nodecount);
			}
			bool isEmpty()  
			{
				return (_nodecount == 0);
			}
			bool contains(T value)
			{
				return contains(_root, value);
			}
			ptr_node	&getelm(T value)
			{
				return (getelm(value, _root));
			}
			void insert(T value) {
				if (!_root)
					length = 0;
				this->_root = insert(this->_root, value, this->_end);
				_nodecount++;
				if (length < getLenght(value.first))
					length = getLenght(value.first);
			}
			bool remove(T elem)
			{
				if (contains(_root, elem))
				{
					_root = remove(_root, elem);
					_nodecount--;
					return true;
				}
				return false;
			}
			int		getLenght(int data)
			{
				return (std::to_string(data).length());
			}
			int		getLenght(std::string data)
			{
				return (data.length());
			}
			void	print()
			{
				if (!_root)
					return ;
				std::cout << "| number of nodes : " << _nodecount << " | tree height: " << _root->height << " |\n";
				std::cout << "lenght : " << length << " |\n";
				// printing(root);
				levelOrder(_root);
			}
			void	levelOrder(ptr_node node)
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
					repeat = (length - 2) - getLenght(current->elm);
					while (repeat--)
						outfile << " ";
					outfile << current->elm;
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
			ptr_node	&serch(T &node)
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
			ptr_node findMax ()
			{
				ptr_node node = _root;
				if (node == nullptr)
					return nullptr;
				while(node->right != nullptr)
					node = node->right;
				return (node);
			}
			ptr_node findMin ()
			{
				ptr_node node = _root;
				if (node == nullptr)
					return nullptr;
				while(node->left != nullptr)
					node = node->left;
				std::cout << "sdfgsd\n";
				return (node);
			}
		private:
			ptr_node			_root;
			ptr_node			_end;
			allocator_type		_alloc;
			key_compare			_cmp;
			size_type			_nodecount;
			int					length;
			ptr_node	&getelm(T &value, ptr_node &root)
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
			ptr_node insert(ptr_node &node, T &value, ptr_node &prnt)
			{
				if (node == nullptr)
				{
					node = _alloc.allocate(1);
					_alloc.construct(node, value);
					node->parnt = prnt;
					if (_root == node)
						_end->left = _root;
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
			ptr_node balance(ptr_node &node)
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
			ptr_node leftLeftCase (ptr_node &node){
				return rightRotation(node) ;
			}
			ptr_node leftRightCase (ptr_node &node) {
				node->left = leftRotation(node->left);
				return leftLeftCase(node);
			}
			ptr_node rightRightCase (ptr_node &node) {
				return leftRotation(node);
			}
			ptr_node rightLeftCase (ptr_node &node) {
				node->right = rightRotation(node->right);
				return rightRightCase(node);
			}
			ptr_node leftRotation (ptr_node &node)
			{
				ptr_node newParent = node->right;
				node->right = newParent->left;
				newParent->left = node;
				update(node);
				update(newParent);
				return newParent;
			}
			ptr_node rightRotation(ptr_node &node)
			{
				ptr_node newParent = node->left;
				node->left = newParent->right;
				newParent->right = node;
				update(node);
				update(newParent);
				return newParent ;
			}
			ptr_node remove (ptr_node &node, T &elem)
			{
				if (node == nullptr)
					return nullptr;
				if (_cmp(node->elm.first, elem.first))
					node->right = remove(node->right, elem);
				else if (_cmp(elem.first, node->elm.first))
					node->left = remove(node->left, elem) ;
				else
				{
					if (node->right == nullptr)
						return node->left;
					else if (node->left == nullptr)
						return node->right;
					else
					{
						if (node->left->height > node->right->height)
						{
							T successorValue = findMax(node->left);
							node->elm = successorValue;
							node->left = remove(node->left, successorValue) ; ;
						}
						else
						{
							T successorValue = findMin(node->right);
							node->elm = successorValue;
							node->right = remove (node->right, successorValue);
						}
					}
				}
				update(node);
				return balance(node);
			}
			T findMin (ptr_node &node)
			{
				while(node->left != NULL)
					node = node->left;
				return node->elm;
			}
			T findMax (ptr_node &node)
			{
				while (node->right != NULL)
					node = node->right;
				return node->elm;
			}
	};
}

#endif