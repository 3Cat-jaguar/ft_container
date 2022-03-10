/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_search_tree.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylee <ylee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 15:32:49 by ylee              #+#    #+#             */
/*   Updated: 2022/03/10 23:51:12 by ylee             ###   ########.fr       */
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
		typedef ft::BST_iterator< Node >					iterator;
		typedef	ft::BST_iterator<const Node >				const_iterator;
		typedef	ft::reverse_iterator<iterator>			reverse_iterator;
		typedef	ft::reverse_iterator<const_iterator>	const_reverse_iterator;
		typedef	size_t	size_type;
	private:
		Node_Alloc	node_alloc;
		Node*		root;
		Node*		endN;
		Compare		value_comp;
		size_type	len ;
	public:
		binary_search_tree()
		: node_alloc(Node_Alloc()), value_comp(Compare()), len(0)
		{
			endN = node_alloc.allocate(1);
			node_alloc.construct(endN, Node(T(), endN, endN, endN));
			root = endN ;
		}
		binary_search_tree(const T& val)
		: node_alloc(Node_Alloc()), value_comp(Compare()), len(1)
		{
			endN = node_alloc.allocate(1);
			node_alloc.construct(endN, Node(T(), endN, endN, endN));
			root = node_alloc.allocate(1);
			node_alloc.construct(root, Node(val, endN, endN, endN));
		}
		
		binary_search_tree(const binary_search_tree& copy)
		: node_alloc(Node_Alloc()), value_comp(Compare())
		{
			*this = copy;
		}
		
		~binary_search_tree()
		{
			// clear();
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
		
		iterator	begin()
		{
			Node*	tmp = root;
			while (tmp->left != endN)
			{
				tmp = tmp->left;
			}
			return iterator(tmp, endN) ;
		}

		iterator	lastNode()
		{
			Node*	tmp = root;
			while (tmp->right != endN)
			{
				tmp = tmp->right;
			}
			return iterator(tmp, endN) ;
		}
		
		iterator	end()
		{
			return iterator(endN, endN) ;
		}
		
		iterator	find(const T& key)
		{
			//root 부터 시작해서 찾는거로 수정하기
			iterator	i = begin();
			while (*i != endN)
			{
				std::cout << "this Node : " << *i << "//\n";
				if (value_comp(**i, key))
					i++;
				else if (value_comp(key, **i))
					return end() ;
				else
					return i ;
			}
			return i ;
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

			while (tmp != endN)
			{
				if (value_comp(**tmp, value)) // value 가 큰 경우
				{
					prev = tmp ;
					tmp = tmp->right ;
					moveLeft = false ;
				}
				else if (value_comp(value, **tmp)) // value 가 작은 경우
				{
					prev = tmp ;
					tmp = tmp->left ;
					moveLeft = true ;
				}
				else // tmp 의 key 와 value 의 key 가 같은 경우
					return ft::pair<iterator, bool>(end(), false) ;
			}
			Node*	newNode = node_alloc.allocate(1);
			node_alloc.construct(newNode, Node(value, prev, endN, endN)) ;
			if (moveLeft == true)
				prev->left = newNode ;
			else
				prev->right = newNode ;
			if (len == 0)
				root = newNode ;
			len++;
			return ft::pair<iterator, bool>(iterator(newNode, endN), true) ;
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