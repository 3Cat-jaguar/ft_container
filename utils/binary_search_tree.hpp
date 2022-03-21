/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_search_tree.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylee <ylee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 15:32:49 by ylee              #+#    #+#             */
/*   Updated: 2022/03/22 03:02:30 by ylee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINARY_TREE_HPP
# define BINARY_TREE_HPP

# include "./less.hpp"
# include "./BST_iterator.hpp"
# include "./reverse_iterator.hpp"
# include "./pair.hpp"
# include "./enable_if.hpp"
# include "./is_integral.hpp"
# include "./equal.hpp"
# include "./lexicographical_compare.hpp"
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
			endN->height = -1 ;
			root = endN ;
		}
		binary_search_tree(const T& val, Compare comp = Compare(), Node_Alloc alloc = Node_Alloc())
		: node_alloc(alloc), key_comp(comp), len(1)
		{
			endN = node_alloc.allocate(1);
			node_alloc.construct(endN, Node(T(), endN, endN, endN));
			endN->height = -1 ;
			root = node_alloc.allocate(1);
			node_alloc.construct(root, Node(val, endN, endN, endN));
		}
		
		binary_search_tree(const binary_search_tree& copy)
		: node_alloc(copy.node_alloc), key_comp(copy.key_comp)
		{
			endN = node_alloc.allocate(1);
			node_alloc.construct(endN, Node(T(), endN, endN, endN));
			endN->height = -1 ;
			root = endN ;
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
			// std::cout << "start BST copy operator\n";
			if (*this == copy)
				return *this ;
			clear();
			insert(copy.begin(), copy.end());
			return *this ;
		}

		void	swap(binary_search_tree& other)
		{
			Node*	tmp_root = other.root;
			Node*	tmp_endN = other.endN;
			size_type	tmp_len = other.len;

			other.root = this->root ;
			other.endN = this->endN ;
			other.len = this->len ;
			this->root = tmp_root ;
			this->endN = tmp_endN ;
			this->len = tmp_len ;
		}

		Node*		beginNode() const
		{
			Node*	tmp = root;
			while (tmp->left != endN)
			{
				// std::cout << "this node : " << *tmp << std::endl;
				tmp = tmp->left;
			}
			return tmp ;
		}
		
		Node*	lastNode() const
		{
			Node*	tmp = root;
			while (tmp->right != endN)
			{
				tmp = tmp->right;
			}
			return tmp ;
		}

		Node*	endNode() const
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
		
		iterator	find(const T& key) const
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

		iterator	find(const Node& keyN) const
		{
			return	find(*keyN) ;
		}

		size_type	count(const T& key) const
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
					return 1 ;
			}
			return 0 ;
		}
		
		ft::pair<iterator, bool>	insert(const T& value)
		{
			Node*	tmp = root ;
			Node*	prev = tmp ;
			bool	moveLeft = true ;
			bool	biggest = true ;

			// std::cout << "start insert value : " << value.first << "\n";
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
					return ft::pair<iterator, bool>(iterator(tmp, endN), false) ;
			}
			// std::cout << "find position\n";
			Node*	newNode = node_alloc.allocate(1);
			node_alloc.construct(newNode, Node(value, prev, endN, endN)) ;
			if (prev != endN)
			{
				if (moveLeft == true)
					prev->left = newNode ;
				else
					prev->right = newNode ;
			}
			if (biggest)
				endN->parent = newNode ;
			// std::cout << "1) endN information : "
			// << endN->value << " , "
			// << endN->parent->value << "\n";
			if (len == 0)
				root = newNode ;
			len++;
			// std::cout << ">>insert " << value << " result <<\n" ;
			//rearrange
			insertBalancing(newNode);
			
			// if (biggest)
			// 	endN->parent = newNode ;
				
			// std::cout << "2) endN information : "
			// << endN->value << " , "
			// << endN->parent->value << "\n";
			// //insert check
			// iterator	i = begin();
			// iterator	f = end();
			// while (i!=f)
			// {
			// 	std::cout << *i << std::endl;
			// 	i++;
			// }
			// std::cout << *i << "\t>>end\n\n";
			
			return ft::pair<iterator, bool>(iterator(newNode, endN), true) ;
		}

		iterator insert( iterator hint, const T& value )
		{
			if (len == 0)
			{
				Node*	newNode = node_alloc.allocate(1);
				node_alloc.construct(newNode, Node(value, endN, endN, endN)) ;
				endN->parent = newNode ;
				root = newNode;
				len++;
				return iterator(newNode, endN) ;
			}
			if (hint.base() == endN)
				hint--;
			Node*	newNode;
			if(key_comp(hint->first, value.first))
			{
				// std::cout << "here! 1\n";
				while (hint.base() != endN)
				{
					
					if (key_comp(hint->first, value.first))
						hint++ ;
					else if (hint->first == value.first)
						return hint ;
					else
						break ;
				}
				Node*	hintN = hint.base();
				newNode = node_alloc.allocate(1);
				node_alloc.construct(newNode, Node(value, endN, endN, endN)) ;
				if (hintN == endN)
				{
					// std::cout << "endN : \n";
					// std::cout << *hintN << " , "
					// << *(hintN->parent) << " , "
					// << *(hintN->left) << " , "
					// << *(hintN->right) << "\n";
					hintN->parent->right = newNode;
					newNode->parent = hintN->parent ;
					endN->parent = newNode;
				}
				else if (hintN->left == endN)
				{
					hintN->left = newNode;
					newNode->parent = hintN;
				}
				else
				{
					--hint;
					hintN = hint.base();
					hintN->right = newNode;
					newNode->parent = hintN;
				}
				// std::cout << *newNode << " , "
				// << *(newNode->parent) << " , "
				// << *(newNode->left) << " , "
				// << *(newNode->right) << "\n";
			}
			else if (key_comp(value.first, hint->first))
			{
				// std::cout << "here! 2\n";
				iterator	prev = hint;
				while (hint.base() != endN)
				{
					prev = hint;
					if (key_comp(value.first, hint->first))
						hint--;
					else if (hint->first == value.first)
						return hint ;
					else
						break ;
				}
				Node*	hintN = hint.base();
				newNode = node_alloc.allocate(1);
				node_alloc.construct(newNode, Node(value, endN, endN, endN)) ;
				if (hintN == endN)
				{
					Node*	prevN = prev.base();
					prevN->left = newNode;
					newNode->parent = prevN ;
				}
				else if (hintN->right == endN)
				{
					hintN->right = newNode;
					newNode->parent = hintN;
				}
				else
				{
					Node*	prevN = prev.base();
					prevN->left = newNode;
					newNode->parent = hintN;
				}
			}
			else
				return hint ;
			// std::cout << "here! 3\n";
			// std::cout << *newNode << " , "
			// 	<< *(newNode->parent) << " , "
			// 	<< *(newNode->left) << " , "
			// 	<< *(newNode->right) << "\n";
			len++;
			insertBalancing(newNode);
			// std::cout << "here! 4\n";
			return iterator(newNode, endN);
		}

		template< class InputIt >
		void insert( InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = nullptr )
		{
			// std::cout << "iterator start\n";
			for(; first != last; first++)
			{
				insert(*first);	
			}
			// std::cout << "iterator end\n";
			// tree.insert(first, last) ;
		}

		size_type	size() const
		{
			return	len ;
		}

		size_type	max_size() const
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
			// std::cout << "erase node : " << *pos << std::endl;
			Node*	eraseN = pos.base();
			Node*	parentN = eraseN->parent ;
			Node*	replaceN = endN ;
			bool	leftNode = (parentN->left == eraseN) ;
			// 지울 노드가 parent 의 left 였다면 leftNode == true, right 였다면 false
			if (eraseN->left == endN && eraseN->right == endN) // leaf 인 경우
			{
				// std::cout << ">>no child node erase<<\n";
				// std::cout << "[before erase]\n";
				// std::cout << "parentN : \n";
				// std::cout << *parentN;
				// std::cout << "eraseN : \n";
				// std::cout << *eraseN;
				
				if (leftNode)
					parentN->left = endN ;
				else
					parentN->right = endN ;
				if (eraseN == root)
					root = endN ;
				
				// std::cout << "[replace to erase]\n";
				// std::cout << "parentN : \n";
				// std::cout << *parentN;
				// std::cout << "eraseN : \n";
				// std::cout << *eraseN;
			}
			else if (eraseN->left != endN && eraseN->right != endN) // 자식 노드가 2개 있는 경우
			{
				replaceN = eraseN->left;
				while (replaceN->right != endN)
					replaceN = replaceN->right ;
				// std::cout << ">>two child node erase<<\n";
				// std::cout << "[before erase]\n";
				// std::cout << "parentN : \n";
				// std::cout << *parentN;
				// std::cout << "eraseN : \n";
				// std::cout << *eraseN;
				// std::cout << "replaceN : \n";
				// std::cout << *replaceN;
				// left 노드 중 가장 큰 노드의 값으로 대체한뒤 가장 큰 left 노드를 제거한다.
				if (replaceN->parent == eraseN)
				{
					eraseN->left = eraseN ;
					replaceN->parent = replaceN ;
				}
				Node	tmp(*replaceN);
				replaceN->copyExceptValue(*eraseN);
				replaceN->left->parent = replaceN;
				replaceN->right->parent = replaceN;
				eraseN->copyExceptValue(tmp) ;
				if (eraseN == root)
					root = replaceN ;
				else
				{
					if (leftNode)
						parentN->left = replaceN ;
					else
						parentN->right = replaceN ;	
				}
				// std::cout << "[replace to erase]\n";
				// std::cout << "parentN : \n";
				// std::cout << *parentN;
				// std::cout << "eraseN : \n";
				// std::cout << *eraseN;
				// std::cout << "replaceN : \n";
				// std::cout << *replaceN;
				erase(iterator(eraseN, endN));
				return ;
			}
			else // 자식 노드가 1개인 경우
			{
				replaceN = (eraseN->left == endN) ? eraseN->right : eraseN->left ;
				// std::cout << ">>one child node erase<<\n";
				// std::cout << "[before erase]\n";
				// std::cout << "parentN : \n";
				// std::cout << *parentN;
				// std::cout << "eraseN : \n";
				// std::cout << *eraseN;
				// std::cout << "replaceN : \n";
				// std::cout << *replaceN;
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

				// std::cout << "[replace to erase]\n";
				// std::cout << "parentN : \n";
				// std::cout << *parentN;
				// std::cout << "eraseN : \n";
				// std::cout << *eraseN;
				// std::cout << "replaceN : \n";
				// std::cout << *replaceN;
			}
			node_alloc.destroy(eraseN);
			node_alloc.deallocate(eraseN, 1);
			len--;
			endN->parent = lastNode();
			//정렬
			// while (replaceN != parentN)
			// {
			// 	checkHeight(replaceN);
			// 	replaceN = replaceN->parent ;
			// }
			deleteBalancing(parentN);
			// std::cout << "end delete complete even balancing\n";
		}
		
		void erase( iterator first, iterator last )
		{
			iterator	tmp = first;
			iterator	next = tmp ;
			while (next != end() && next != last)
			{
				tmp = next++;
				// std::cout << "erase iterator\ntmp : " << *tmp << " , next : " << *next << std::endl;
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

		Node*	rightRotation(Node* cur)
		{
			Node*	replaceN = cur->left ;
			
			// std::cout << ">>right rotation<<\n";
			// std::cout << "[before rotation]\n";
			// std::cout << "cur : \n";
			// std::cout << *cur;
			// std::cout << "replaceN : \n";
			// std::cout << *replaceN;
			
			
			replaceN->parent = cur->parent;
			cur->left = replaceN->right ;
			cur->parent = replaceN ;
			replaceN->right = cur;
			if (cur->left != endN)
				cur->left->parent = cur;

			checkHeight(cur);
			checkHeight(replaceN);
			

			// std::cout << "[after rotation]\n";
			// std::cout << "cur : \n";
			// std::cout << *cur;
			// std::cout << "replaceN : \n";
			// std::cout << *replaceN;
			
			return replaceN ;
		}
		
		Node*	leftRotation(Node* cur)
		{
			Node*	replaceN = cur->right ;

			// std::cout << "-------\n";
			// std::cout << ">>left rotation<<\n";
			// std::cout << "[before rotation]\n";
			// std::cout << "cur : \n";
			// std::cout << *cur;
			// std::cout << "replaceN : \n";
			// std::cout << *replaceN;
			// std::cout << "-------\n\n";
			
			replaceN->parent = cur->parent;
			cur->right = replaceN->left ;
			cur->parent = replaceN ;
			replaceN->left = cur;
			if (cur->right != endN)
				cur->right->parent = cur ;

			checkHeight(cur);
			checkHeight(replaceN);
			
			// std::cout << "[after rotation]\n";
			// std::cout << "cur : \n";
			// std::cout << *cur;
			// std::cout << "replaceN : \n";
			// std::cout << *replaceN;
			// std::cout << "-------\n\n";
			
			return replaceN ;
		}

		void	checkHeight(Node* cur)
		{
			if (cur == endN)
				return ;
			if (cur->left->height < cur->right->height)
				cur->height = cur->right->height + 1 ;
			else
				cur->height = cur->left->height + 1 ;
		}

		int		checkBalanced(Node* cur)
		{
			return	(cur->left->height - cur->right->height) ;
		}
		
		
		void	insertBalancing(Node* cur)
		{
			if (cur == root)
				return ;
			Node*	parentN = cur->parent;
			// std::cout << "here! 1\n";
			checkHeight(parentN);
			if (parentN == root)
				return ;
			// std::cout << "here! 2\n";
			Node*	gpN = parentN->parent;
			int	isBalanced = checkBalanced(gpN);
			// std::cout << "here! 3\n";
			if (isBalanced > 1 || isBalanced < -1) // 밸런스가 깨진경우 rotation 진행
			{
				Node*	final = gpN->parent;
				if (gpN == root)
					root = rearrange(gpN, parentN, cur);
				else if (gpN->parent->left == gpN)
					final->left = rearrange(gpN, parentN, cur);
				else if (gpN->parent->right == gpN)
					final->right = rearrange(gpN, parentN, cur);
			}
			// 밸런스 체크 완료
			// root 까지 계속 이어서 체크
			insertBalancing(parentN);
			return ;
		}

		Node*	rearrange(Node* gpN, Node* pN, Node* N)
		{
			if (gpN->left == pN && pN->left == N) // LL case -> rightRotation
			{
				return	rightRotation(gpN);
			}
			else if (gpN->left == pN && pN->right == N) // LR case -> left(pN) and right(gpN)
			{
				gpN->left = leftRotation(pN);
				return	rightRotation(gpN);
			}
			else if (gpN->right == pN && pN->right == N) // RR case -> leftRotation
			{
				return	leftRotation(gpN);
			}
			else // RL case ->right(pN) and left(gpN)
			{
				gpN->right = rightRotation(pN);
				return	leftRotation(gpN);
			}
		}

		
		void	deleteBalancing(Node* cur)
		{
			if (cur == endN)
				return ;
			checkHeight(cur);
			// std::cout << "delete balancing target node : " << *cur << std::endl;
			Node*	parentN = cur->parent;
			int	isBalanced = checkBalanced(cur);
			if (isBalanced > 1 || isBalanced < -1) // 밸런스가 깨진경우 rotation 진행
			{
				Node*	cN = (cur->left->height < cur->right->height) ? cur->right : cur->left;
				Node*	gcN = (cN->left->height < cN->right->height) ? cN->right : cN->left;
				if (cur == root)
					root = rearrange(cur, cN, gcN);
				else if (parentN->left == cur)
					parentN->left = rearrange(cur, cN, gcN);
				else if (parentN->right == cur)
					parentN->right = rearrange(cur, cN, gcN);
			}
			
			// 밸런스 체크 완료
			// root 까지 계속 이어서 체크
			deleteBalancing(parentN);
			return ;
		}

		// >>> 위는 작업 완료. 아래는 작업 중. <<<
		ft::pair<iterator,iterator> equal_range( const T& key )
		{
			Node*	cur = root ;
			Node*	prev = cur;
			bool	biggest = true ;
			bool	smallest = true ;
			while (cur != endN)
			{
				// std::cout << "this Node : " << cur->value << "//\n";
				if (key_comp((cur->value).first, key.first))
				{
					smallest = false ;
					prev = cur;
					cur = cur->right ;
				}
				else if (key_comp(key.first, (cur->value).first))
				{
					biggest = false ;
					prev = cur;
					cur = cur->left ;
				}
				else
				{
					iterator second = iterator(cur, endN);
					iterator first = second++;
					return ft::pair<iterator, iterator>(first, second) ;
				}
			}
			if (smallest)
			{
				return ft::pair<iterator, iterator>(begin(), begin()) ;
			}
			if (biggest)
			{
				return ft::pair<iterator, iterator>(end(), end()) ;
			}
			iterator	prevIter(prev, endN);
			if (key_comp((prev->value).first, key.first))
				prevIter++;
			return ft::pair<iterator, iterator>(prevIter, prevIter) ;
		}

		ft::pair<const_iterator,const_iterator> equal_range( const T& key ) const
		{
			Node*	cur = root ;
			Node*	prev = cur;
			bool	biggest = true ;
			bool	smallest = true ;
			while (cur != endN)
			{
				// std::cout << "this Node : " << cur->value << "//\n";
				if (key_comp((cur->value).first, key.first))
				{
					smallest = false ;
					prev = cur;
					cur = cur->right ;
				}
				else if (key_comp(key.first, (cur->value).first))
				{
					biggest = false ;
					prev = cur;
					cur = cur->left ;
				}
				else
				{
					const_iterator second = const_iterator(cur, endN);
					const_iterator first = second++;
					return ft::pair<const_iterator, const_iterator>(first, second) ;
				}
			}
			if (smallest)
			{
				return ft::pair<const_iterator, const_iterator>(begin(), begin()) ;
			}
			if (biggest)
			{
				return ft::pair<const_iterator, const_iterator>(end(), end()) ;
			}
			const_iterator	prevIter(prev, endN);
			if (key_comp((prev->value).first, key.first))
				prevIter++;
			return ft::pair<const_iterator, const_iterator>(prevIter, prevIter) ;
		}
		
		iterator lower_bound( const T& key )
		{
			Node*	cur = root ;
			Node*	prev = cur;
			bool	biggest = true ;
			bool	smallest = true ;
			while (cur != endN)
			{
				// std::cout << "this Node : " << cur->value << "//\n";
				if (key_comp((cur->value).first, key.first))
				{
					smallest = false ;
					prev = cur;
					cur = cur->right ;
				}
				else if (key_comp(key.first, (cur->value).first))
				{
					biggest = false ;
					prev = cur;
					cur = cur->left ;
				}
				else
				{
					return	iterator(cur, endN) ;
				}
			}
			if (smallest)
			{
				return begin() ;
			}
			if (biggest)
			{
				return end() ;
			}
			iterator	prevIter(prev, endN);
			if (key_comp((prev->value).first, key.first))
				prevIter++;
			return prevIter ;
		}

		const_iterator lower_bound( const T& key ) const
		{
			Node*	cur = root ;
			Node*	prev = cur;
			bool	biggest = true ;
			bool	smallest = true ;
			while (cur != endN)
			{
				// std::cout << "this Node : " << cur->value << "//\n";
				if (key_comp((cur->value).first, key.first))
				{
					smallest = false ;
					prev = cur;
					cur = cur->right ;
				}
				else if (key_comp(key.first, (cur->value).first))
				{
					biggest = false ;
					prev = cur;
					cur = cur->left ;
				}
				else
				{
					return	const_iterator(cur, endN) ;
				}
			}
			if (smallest)
			{
				return begin() ;
			}
			if (biggest)
			{
				return end() ;
			}
			const_iterator	prevIter(prev, endN);
			if (key_comp((prev->value).first, key.first))
				prevIter++;
			return prevIter ;
		}
		
		iterator upper_bound( const T& key )
		{
			Node*	cur = root ;
			Node*	prev = cur;
			bool	biggest = true ;
			bool	smallest = true ;
			while (cur != endN)
			{
				// std::cout << "this Node : " << cur->value << "//\n";
				if (key_comp((cur->value).first, key.first))
				{
					smallest = false ;
					prev = cur;
					cur = cur->right ;
				}
				else if (key_comp(key.first, (cur->value).first))
				{
					biggest = false ;
					prev = cur;
					cur = cur->left ;
				}
				else
				{
					iterator	find(cur, endN);
					find++;
					return	find ;
				}
			}
			if (smallest)
			{
				return begin() ;
			}
			if (biggest)
			{
				return end() ;
			}
			iterator	prevIter(prev, endN);
			if (key_comp((prev->value).first, key.first))
				prevIter++;
			return prevIter ;
		}

		const_iterator upper_bound( const T& key ) const
		{
			Node*	cur = root ;
			Node*	prev = cur;
			bool	biggest = true ;
			bool	smallest = true ;
			while (cur != endN)
			{
				// std::cout << "this Node : " << cur->value << "//\n";
				if (key_comp((cur->value).first, key.first))
				{
					smallest = false ;
					prev = cur;
					cur = cur->right ;
				}
				else if (key_comp(key.first, (cur->value).first))
				{
					biggest = false ;
					prev = cur;
					cur = cur->left ;
				}
				else
				{
					const_iterator	find(cur, endN);
					find++;
					return	find ;
				}
			}
			if (smallest)
			{
				return begin() ;
			}
			if (biggest)
			{
				return end() ;
			}
			const_iterator	prevIter(prev, endN);
			if (key_comp((prev->value).first, key.first))
				prevIter++;
			return prevIter ;
		}
		
	};


	template< class T, class Compare, class cT, class cCompare >
	bool operator==( const binary_search_tree<T, Compare>& lhs, const binary_search_tree<cT, cCompare>& rhs )
	{
		if (lhs.size() != rhs.size())
			return false ;
		return	ft::equal(lhs.begin(), lhs.end(), rhs.begin()) ;
	}
	
	template< class T, class Compare, class cT, class cCompare >
	bool operator!=( const binary_search_tree<T, Compare>& lhs, const binary_search_tree<cT, cCompare>& rhs )
	{
		return !(lhs == rhs) ;
	}
	
	template< class T, class Compare, class cT, class cCompare >
	bool operator< ( const binary_search_tree<T, Compare>& lhs, const binary_search_tree<cT, cCompare>& rhs )
	{
		return	ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()) ;
	}
	
	template< class T, class Compare, class cT, class cCompare >
	bool operator<=( const binary_search_tree<T, Compare>& lhs, const binary_search_tree<cT, cCompare>& rhs )
	{
		return	!(rhs < lhs);
	}
	
	template< class T, class Compare, class cT, class cCompare >
	bool operator> ( const binary_search_tree<T, Compare>& lhs, const binary_search_tree<cT, cCompare>& rhs )
	{
		return	(rhs < lhs) ;
	}
	
	template< class T, class Compare, class cT, class cCompare >
	bool operator>=( const binary_search_tree<T, Compare>& lhs, const binary_search_tree<cT, cCompare>& rhs )
	{
		return	!( lhs < rhs ) ;
	}
	
	template<typename T, typename Compare>
	std::ostream&	operator<<(std::ostream& out, const binary_search_tree<T, Compare>& tree)
	{
		typedef	typename ft::binary_search_tree<T, Compare>::iterator	iterator;
		
		out << "this tree information\n";
		iterator	i = tree.begin();
		iterator	f = tree.end();
		while (i != f)
		{
			out << *i << std::endl;
			out << "-----\n";
			i++;
		}
		out << *i << std::endl;
		out << ">>> end <<<\n";
		return out ;
	}
	
}

#endif
