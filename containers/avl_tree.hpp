#ifndef AVL_TREE_HPP
#define  AVL_TREE_HPP
#include <iostream>

namespace ft
{
	template <class T>
	struct Node
	{
		T		elm;
		Node	*left;
		Node	*right;
		int		height;
	};
	template <class Tn>
	class avltree {
		private:
			Node root;
			int nodecount;
			bool contains(Node node,Tn value)
			{
				if (node == NULL)
					return (false);
				int cmp = value - node.elm;
				if (cmp < 0)
					return contains(*node.left, value);
				if (cmp > 0)
					return contains(*node.right, value);
				return (true);
			}
			bool	insert(Node root, Tn value)
			{
				if (node == NULL)
					return new Node(value);
				int cmp = value - node.elm;
				if (cmp < 0)
					node.left = insert(node.left, value);
				else
					node.right = insert(node.right, value);
				update(node);
				return balance(node);
			}
		public:
			int height()
			{
				if (root == nullptr)
					return 0;
				return (root.height);
			}
			int size()
			{
				return (root.height);
			}
			int isEmpty()
			{
				return (root.height == 0);
			}
			bool contains(Tn value)
			{
				return contains(root, value)
			}
			bool	insert(Tn value) {
				if (value == NULL)
					return false;
				if (!contains(root, value))
				{
					root = insert(root, value);
					nodecount++;
					return true;
				}
				return false;
			}




	};
}

#endif