/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylee <ylee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 12:44:11 by ylee              #+#    #+#             */
/*   Updated: 2022/02/20 17:51:44 by ylee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"

namespace	ft
{
    template < typename T, typename Container = ft::vector<T> >
    class   stack
    {
    public:
        typedef Container                   container_type;
        typedef typename Container::value_type       value_type;
        typedef typename Container::size_type        size_type;
        typedef typename Container::reference        reference;
        typedef typename Container::const_reference  const_reference;
        
    protected:
        container_type  c;
    public:
        explicit stack( const Container& cont = Container() ):c(cont)
        {}
        stack( const stack& other )
        {
            *this = other ;
        }
        stack& operator=( const stack& other )
        {
            this->c = other.c ;
            return *this ;
        }
        ~stack()
        {}
        reference   top()
        {
            return  c.back();
        }
        const_reference top() const
        {
            return  c.back();
        }
        bool    empty() const
        {
            return  this->c.empty();
        }
        size_type   size() const
        {
            return  (this->c.size()) ;
        }
        void    push( const value_type& value )
        {
            c.push_back(value);
        }
        void    pop()
        {
            c.pop_back();
        }
        
        template< class U, class Cont >
        friend bool operator==( const ft::stack<U,Cont>& lhs, const ft::stack<T,Container>& rhs );

        template< class U, class Cont >
        friend bool operator!=( const ft::stack<U,Cont>& lhs, const ft::stack<T,Container>& rhs );
    
        template< class U, class Cont >
        friend bool operator< ( const ft::stack<U,Cont>& lhs, const ft::stack<T,Container>& rhs );
    
        template< class U, class Cont >
        friend bool operator<=( const ft::stack<U,Cont>& lhs, const ft::stack<T,Container>& rhs );
    
        template< class U, class Cont >
        friend bool operator> ( const ft::stack<U,Cont>& lhs, const ft::stack<T,Container>& rhs );
    
        template< class U, class Cont >
        friend bool operator>=( const ft::stack<U,Cont>& lhs, const ft::stack<T,Container>& rhs );

    };

    template< class T, class Container >
    bool operator==( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs )
    {        
        return  lhs.c == rhs.c ;
    }

    template< class T, class Container >
    bool operator!=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs )
    {
        return  lhs.c != rhs.c ;
    }
    
    template< class T, class Container >
    bool operator<( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs )
    {
        return  lhs.c < rhs.c ;
    }
    
    template< class T, class Container >
    bool operator<=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs )
    {
        return  lhs.c <= rhs.c ;
    }
    
    template< class T, class Container >
    bool operator>( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs )
    {
        return  lhs.c > rhs.c ;
    }
    
    template< class T, class Container >
    bool operator>=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs )
    {
        return  lhs.c >= rhs.c ;
    }
    
}

#endif
