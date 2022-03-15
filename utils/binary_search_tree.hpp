/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_search_tree.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylee <ylee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 15:32:49 by ylee              #+#    #+#             */
/*   Updated: 2022/03/15 14:50:40 by ylee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINARY_TREE_HPP
# define BINARY_TREE_HPP

# include "./less.hpp"
# include "./BST_iterator.hpp"
# include "./reverse_iterator.hpp"
# include "./pair.hpp"
# include <memory>

namespace   ft
{
	// Node for BST
	// => move to BST_iterator.hpp

	// Binary Search Tree
	
	template<typename T, typename Compare = ft::less<T>, typename Pair_Alloc = std::allocator<T>, typename Node = ft::BST_Node<T> , typename Node_Alloc = std::allocator<Node> >
	class binary_search_tree
	{
	public:
		typedef typename ft::BST_iterator< Node, Compare >					iterator;
		typedef	typename ft::BST_const_iterator< Node, Compare >				const_iterator;
		typedef	typename ft::reverse_iterator<iterator>			reverse_iterator;
		typedef	typename ft::reverse_iterator<const_iterator>	const_reverse_iterator;
		typedef	size_t										size_type;

		Node_Alloc	node_alloc;
		Node*		root;
		Node*		endN;
		Compare		key_comp;
		size_type	len ;

		binary_search_tree(Compare comp = Compare(), Node_Alloc alloc = Node_Alloc())
		: node_alloc(alloc), key_comp(comp), len(0)
		{
			endN = node_alloc.allocate(1);
			node_alloc.construct(endN, Node(T(), endN, endN, endN));
			root = endN ;
		}
		binary_search_tree(const T& val, Compare comp = Compare(), Node_Alloc alloc = Node_Alloc())
		: node_alloc(alloc), key_comp(comp), len(1)
		{
			endN = node_alloc.allocate(1);
			node_alloc.construct(endN, Node(T(), endN, endN, endN));
			root = node_alloc.allocate(1);
			node_alloc.construct(root, Node(val, endN, endN, endN));
		}
		
		binary_search_tree(const binary_search_tree& copy)
		: node_alloc(copy.node_alloc), key_comp(copy.key_comp)
		{
			*this = copy;
		}
		
		~binary_search_tree()
		{
			clear();
			node_alloc.destroy(endN);
			node_alloc.deallocate(endN, 1);
		}
		
		binary_search_tree& operator=(const binary_search_tree& copy)
		{
			root = node_alloc.allocate(1);
			node_alloc.construct(root, *(copy.root));
			endN = node_alloc.allocate(1);
			node_alloc.construct(endN, *(copy.endN));
		}

		Node*		beginNode()
		{
			Node*	tmp = root;
			while (tmp->left != endN)
			{
				// std::cout << "this node : " << *tmp << std::endl;
				tmp = tmp->left;
			}
			return tmp ;
		}
		
		Node*	lastNode()
		{
			Node*	tmp = root;
			while (tmp->right != endN)
			{
				tmp = tmp->right;
			}
			return tmp ;
		}

		Node*	endNode()
		{
			return	endN ;
		}

		iterator	begin()
		{
			return iterator(beginNode(), endN) ;
		}

		const_iterator	begin() const
		{
			return const_iterator(beginNode(), endN) ;
		}

		iterator	end()
		{
			return iterator(endN, endN) ;
		}

		const_iterator	end() const
		{
			return const_iterator(endN, endN) ;
		}
		
		iterator	find(const T& key)
		{
			Node*	i = root ;
			while (i != endN)
			{
				// std::cout << "this Node : " << i->value << "//\n";
				if (key_comp((i->value).first, key.first))
					i = i->right ;
				else if (key_comp(key.first, (i->value).first))
					i = i->left ;
				else
					return iterator(i, endN);
			}
			return iterator(i, endN) ;
		}

		iterator	find(const Node& keyN)
		{
			return	find(*keyN) ;
		}
		
		ft::pair<iterator, bool>	insert(const T& value)
		{
			Node*	tmp = root ;
			Node*	prev = tmp ;
			bool	moveLeft = true ;
			bool	biggest = true ;

			while (tmp != endN)
			{
				if (key_comp((tmp->value).first, value.first)) // value 가 큰 경우
				{
					prev = tmp ;
					tmp = tmp->right ;
					moveLeft = false ;
				}
				else if (key_comp(value.first, (tmp->value).first)) // value 가 작은 경우
				{
					prev = tmp ;
					tmp = tmp->left ;
					moveLeft = true ;
					biggest = false ;
				}
				else // tmp 의 key 와 value 의 key 가 같은 경우
					return ft::pair<iterator, bool>(end(), false) ;
			}
			Node*	newNode = node_alloc.allocate(1);
			node_alloc.construct(newNode, Node(value, prev, endN, endN)) ;
			if (prev != endN)
			{
				if (moveLeft == true)
					prev->left = newNode ;
				else
					prev->right = newNode ;
			}
			else if (prev == endN || biggest)
				endN->parent = newNode ;
			
			if (len == 0)
				root = newNode ;
			len++;
			//insert check
			iterator	i = begin();
			iterator	f = end();
				std::cout << ">>insert " << value << " result <<\n" ;
			while (i!=f)
			{
				std::cout << *i << std::endl;
				i++;
			}
			std::cout << *i << "\t>>end" << std::endl;
			
			return ft::pair<iterator, bool>(iterator(newNode, endN), true) ;
		}

		size_type	size()
		{
			return	len ;
		}

		size_type	max_size()
		{
			return	node_alloc.max_size() ;
		}
		
		void	clear()
		{
			iterator	i = begin() ;
			iterator	tmp = i;
			iterator	f = end() ;
			while (i != f)
			{
				tmp = i++;
				erase(tmp) ;
			}
			erase(i) ;
		}

		void erase( iterator pos )
		{
			if (pos == end())
			 	return ;
			std::cout << "erase node : " << *pos << std::endl;
			Node*	eraseN = pos.base();
			Node*	parentN = eraseN->parent ;
			Node*	replaceN = endN ;
			bool	leftNode = (parentN->left == eraseN) ;
			// 지울 노드가 parent 의 left 였다면 leftNode == true, right 였다면 false
			if (eraseN->left == endN && eraseN->right == endN) // leaf 인 경우
			{
				if (leftNode)
					parentN->left = endN ;
				else
					parentN->right = endN ;
				if (eraseN == root)
					root = endN ;
			}
			else if (eraseN->left != endN && eraseN->right != endN) // 자식 노드가 2개 있는 경우
			{
				replaceN = eraseN->left;
				while (replaceN->right != endN)
					replaceN = replaceN->right ;
				// left 노드 중 가장 큰 노드의 값으로 대체한뒤 가장 큰 left 노드를 제거한다.
				if (replaceN->parent == eraseN)
				{
					eraseN->left = eraseN ;
					replaceN->parent = replaceN ;
				}
				Node	tmp(*replaceN);
				replaceN->copyExceptValue(*eraseN);
				eraseN->copyExceptValue(tmp) ;
				if (eraseN == root)
					root = replaceN ;
				erase(iterator(eraseN, endN));
				return ;
			}
			else // 자식 노드가 1개인 경우
			{
				replaceN = (eraseN->left == endN) ? eraseN->right : eraseN->left ;
				if (leftNode)
				{
					if (parentN != endN)
						parentN->left = replaceN ;
					replaceN->parent = parentN ;
				}
				else
				{
					if (parentN != endN)
						parentN->right = replaceN ;
					replaceN->parent = parentN ;
				}
				if (eraseN == root)
					root = replaceN ;
			}
			node_alloc.destroy(eraseN);
			node_alloc.deallocate(eraseN, 1);
			len--;
			endN->parent = lastNode();
			//정렬
		}
		
		void erase( iterator first, iterator last )
		{
			iterator	tmp = first;
			iterator	next = tmp ;
			while (next != end() && next != last)
			{
				tmp = next++;
				std::cout << "tmp : " << *tmp << " , next : " << *next << std::endl;
				erase(tmp);
			}
		}
		
		size_type erase( const T& key )
		{
			size_type	cnt = 0;
			iterator	findN = find(key) ;
			if (findN != end())
			{
				erase(findN);	
				cnt++;
			}
			return	cnt ;
		}
	};
}

#endif

/*
typedef struct BinTreeNodeType
{
	int key;
	struct BinTreeNodeType	*pParent;
	struct BinTreeNodeType	*pLeftChild;
	struct BinTreeNodeType	*pRightChild;
} BinTreeNode;

typedef struct BinTreeType
{
	struct BinTreeNodeType	*pRootNode;
} BinTree;

BinTree* makeBinTree(BinTreeNode rootNode);
BinTreeNode* getRootNodeBT(BinTree* pBinTree);
BinTreeNode* getLeftChildNodeBT(BinTreeNode* pNode);
BinTreeNode* getRightChildNodeBT(BinTreeNode* pNode);

void	print_preorder(BinTreeNode *pNode);
void	print_inorder(BinTreeNode *pNode);
void	print_postorder(BinTreeNode *pNode);

void  insertNode(BinTreeNode *root, int key)

BinTreeNode *search(BinTree *tree, int key );

BinTreeNode *searchParent(BinTree *tree, int key )

BinTreeNode *findMaxValue(BinTreeNode *root)

BinTreeNode	*deleteNode(BinTreeNode *root, int key)


*/