/*

    map synopsis

namespace std
{

template <class Key, class T, class Compare = less<Key>,
          class Allocator = allocator<pair<const Key, T>>>
class map
{
public:
    // types:
    typedef Key                                      key_type;
    typedef T                                        mapped_type;
    typedef pair<const key_type, mapped_type>        value_type;
    typedef Compare                                  key_compare;
    typedef Allocator                                allocator_type;
    typedef typename allocator_type::reference       reference;
    typedef typename allocator_type::const_reference const_reference;
    typedef typename allocator_type::pointer         pointer;
    typedef typename allocator_type::const_pointer   const_pointer;
    typedef typename allocator_type::size_type       size_type;
    typedef typename allocator_type::difference_type difference_type;

    typedef implementation-defined                   iterator;
    typedef implementation-defined                   const_iterator;
    typedef std::reverse_iterator<iterator>          reverse_iterator;
    typedef std::reverse_iterator<const_iterator>    const_reverse_iterator;
    typedef unspecified                              node_type;              // C++17
    typedef INSERT_RETURN_TYPE<iterator, node_type>  insert_return_type;     // C++17

    class value_compare
        : public binary_function<value_type, value_type, bool>
    {
        friend class map;
    protected:
        key_compare comp;

        value_compare(key_compare c);
    public:
        bool operator()(const value_type& x, const value_type& y) const;
    };

    // construct/copy/destroy:
    
    // iterators:
    
    // capacity:
    
    // modifiers:
    
    // observers:

    // map operations:
};

//map non-member functions

// specialized algorithms:

}  // std

*/

#include <__config>
#include <__tree>
#include <__node_handle>
#include <iterator>
#include <memory>
#include <utility>
#include <functional>
#include <initializer_list>
#include <type_traits>
#include <version>

#if !defined(_LIBCPP_HAS_NO_PRAGMA_SYSTEM_HEADER)
#pragma GCC system_header
#endif

_LIBCPP_BEGIN_NAMESPACE_STD

template <class _Key, class _CP, class _Compare,
          bool = is_empty<_Compare>::value && !__libcpp_is_final<_Compare>::value>
class __map_value_compare
    : private _Compare
{
public:
    _LIBCPP_INLINE_VISIBILITY
    __map_value_compare()
        _NOEXCEPT_(is_nothrow_default_constructible<_Compare>::value)
        : _Compare() {}
    _LIBCPP_INLINE_VISIBILITY
    __map_value_compare(_Compare c)
        _NOEXCEPT_(is_nothrow_copy_constructible<_Compare>::value)
        : _Compare(c) {}
    _LIBCPP_INLINE_VISIBILITY
    const _Compare& key_comp() const _NOEXCEPT {return *this;}
    _LIBCPP_INLINE_VISIBILITY
    bool operator()(const _CP& __x, const _CP& __y) const
        {return static_cast<const _Compare&>(*this)(__x.__get_value().first, __y.__get_value().first);}
    _LIBCPP_INLINE_VISIBILITY
    bool operator()(const _CP& __x, const _Key& __y) const
        {return static_cast<const _Compare&>(*this)(__x.__get_value().first, __y);}
    _LIBCPP_INLINE_VISIBILITY
    bool operator()(const _Key& __x, const _CP& __y) const
        {return static_cast<const _Compare&>(*this)(__x, __y.__get_value().first);}
    void swap(__map_value_compare&__y)
        _NOEXCEPT_(__is_nothrow_swappable<_Compare>::value)
    {
      using _VSTD::swap;
      swap(static_cast<_Compare&>(*this), static_cast<_Compare&>(__y));
    }

#if _LIBCPP_STD_VER > 11
    template <typename _K2>
    _LIBCPP_INLINE_VISIBILITY
    typename enable_if<__is_transparent<_Compare, _K2>::value, bool>::type
    operator () ( const _K2& __x, const _CP& __y ) const
        {return static_cast<const _Compare&>(*this) (__x, __y.__get_value().first);}

    template <typename _K2>
    _LIBCPP_INLINE_VISIBILITY
    typename enable_if<__is_transparent<_Compare, _K2>::value, bool>::type
    operator () (const _CP& __x, const _K2& __y) const
        {return static_cast<const _Compare&>(*this) (__x.__get_value().first, __y);}
#endif
};

template <class _Key, class _CP, class _Compare>
class __map_value_compare<_Key, _CP, _Compare, false>
{
    _Compare comp;

public:
    _LIBCPP_INLINE_VISIBILITY
    __map_value_compare()
        _NOEXCEPT_(is_nothrow_default_constructible<_Compare>::value)
        : comp() {}
    _LIBCPP_INLINE_VISIBILITY
    __map_value_compare(_Compare c)
        _NOEXCEPT_(is_nothrow_copy_constructible<_Compare>::value)
        : comp(c) {}
    _LIBCPP_INLINE_VISIBILITY
    const _Compare& key_comp() const _NOEXCEPT {return comp;}

    _LIBCPP_INLINE_VISIBILITY
    bool operator()(const _CP& __x, const _CP& __y) const
        {return comp(__x.__get_value().first, __y.__get_value().first);}
    _LIBCPP_INLINE_VISIBILITY
    bool operator()(const _CP& __x, const _Key& __y) const
        {return comp(__x.__get_value().first, __y);}
    _LIBCPP_INLINE_VISIBILITY
    bool operator()(const _Key& __x, const _CP& __y) const
        {return comp(__x, __y.__get_value().first);}
    void swap(__map_value_compare&__y)
        _NOEXCEPT_(__is_nothrow_swappable<_Compare>::value)
    {
        using _VSTD::swap;
        swap(comp, __y.comp);
    }

#if _LIBCPP_STD_VER > 11
    template <typename _K2>
    _LIBCPP_INLINE_VISIBILITY
    typename enable_if<__is_transparent<_Compare, _K2>::value, bool>::type
    operator () ( const _K2& __x, const _CP& __y ) const
        {return comp (__x, __y.__get_value().first);}

    template <typename _K2>
    _LIBCPP_INLINE_VISIBILITY
    typename enable_if<__is_transparent<_Compare, _K2>::value, bool>::type
    operator () (const _CP& __x, const _K2& __y) const
        {return comp (__x.__get_value().first, __y);}
#endif
};



template <class _Allocator>
class __map_node_destructor
{
    typedef _Allocator                          allocator_type;
    typedef allocator_traits<allocator_type>    __alloc_traits;

public:
    typedef typename __alloc_traits::pointer    pointer;

private:
    allocator_type& __na_;

    __map_node_destructor& operator=(const __map_node_destructor&);

public:
    bool __first_constructed;
    bool __second_constructed;

    _LIBCPP_INLINE_VISIBILITY
    explicit __map_node_destructor(allocator_type& __na) _NOEXCEPT
        : __na_(__na),
          __first_constructed(false),
          __second_constructed(false)
        {}

#ifndef _LIBCPP_CXX03_LANG
    _LIBCPP_INLINE_VISIBILITY
    __map_node_destructor(__tree_node_destructor<allocator_type>&& __x) _NOEXCEPT
        : __na_(__x.__na_),
          __first_constructed(__x.__value_constructed),
          __second_constructed(__x.__value_constructed)
        {
            __x.__value_constructed = false;
        }
#endif  // _LIBCPP_CXX03_LANG

    _LIBCPP_INLINE_VISIBILITY
    void operator()(pointer __p) _NOEXCEPT
    {
        if (__second_constructed)
            __alloc_traits::destroy(__na_, _VSTD::addressof(__p->__value_.__get_value().second));
        if (__first_constructed)
            __alloc_traits::destroy(__na_, _VSTD::addressof(__p->__value_.__get_value().first));
        if (__p)
            __alloc_traits::deallocate(__na_, __p, 1);
    }
};

template <class _Key, class _Tp, class _Compare, class _Allocator>
    class map;

template <class _TreeIterator> class __map_const_iterator;


template <class _Tp>
struct __extract_key_value_types;

template <class _Key, class _Tp>
struct __extract_key_value_types<__value_type<_Key, _Tp> >
{
  typedef _Key const __key_type;
  typedef _Tp        __mapped_type;
};

template <class _TreeIterator>
class _LIBCPP_TEMPLATE_VIS __map_iterator
{
    typedef typename _TreeIterator::_NodeTypes                   _NodeTypes;
    typedef typename _TreeIterator::__pointer_traits             __pointer_traits;

    _TreeIterator __i_;

public:
    typedef bidirectional_iterator_tag                           iterator_category;
    typedef typename _NodeTypes::__map_value_type                value_type;
    typedef typename _TreeIterator::difference_type              difference_type;
    typedef value_type&                                          reference;
    typedef typename _NodeTypes::__map_value_type_pointer        pointer;

    _LIBCPP_INLINE_VISIBILITY
    __map_iterator() _NOEXCEPT {}

    _LIBCPP_INLINE_VISIBILITY
    __map_iterator(_TreeIterator __i) _NOEXCEPT : __i_(__i) {}

    _LIBCPP_INLINE_VISIBILITY
    reference operator*() const {return __i_->__get_value();}
    _LIBCPP_INLINE_VISIBILITY
    pointer operator->() const {return pointer_traits<pointer>::pointer_to(__i_->__get_value());}

    _LIBCPP_INLINE_VISIBILITY
    __map_iterator& operator++() {++__i_; return *this;}
    _LIBCPP_INLINE_VISIBILITY
    __map_iterator operator++(int)
    {
        __map_iterator __t(*this);
        ++(*this);
        return __t;
    }

    _LIBCPP_INLINE_VISIBILITY
    __map_iterator& operator--() {--__i_; return *this;}
    _LIBCPP_INLINE_VISIBILITY
    __map_iterator operator--(int)
    {
        __map_iterator __t(*this);
        --(*this);
        return __t;
    }

    friend _LIBCPP_INLINE_VISIBILITY
    bool operator==(const __map_iterator& __x, const __map_iterator& __y)
        {return __x.__i_ == __y.__i_;}
    friend
    _LIBCPP_INLINE_VISIBILITY
    bool operator!=(const __map_iterator& __x, const __map_iterator& __y)
        {return __x.__i_ != __y.__i_;}

    template <class, class, class, class> friend class _LIBCPP_TEMPLATE_VIS map;
    template <class, class, class, class> friend class _LIBCPP_TEMPLATE_VIS multimap;
    template <class> friend class _LIBCPP_TEMPLATE_VIS __map_const_iterator;
};

template <class _TreeIterator>
class _LIBCPP_TEMPLATE_VIS __map_const_iterator
{
    typedef typename _TreeIterator::_NodeTypes                   _NodeTypes;
    typedef typename _TreeIterator::__pointer_traits             __pointer_traits;

    _TreeIterator __i_;

public:
    typedef bidirectional_iterator_tag                           iterator_category;
    typedef typename _NodeTypes::__map_value_type                value_type;
    typedef typename _TreeIterator::difference_type              difference_type;
    typedef const value_type&                                    reference;
    typedef typename _NodeTypes::__const_map_value_type_pointer  pointer;

    _LIBCPP_INLINE_VISIBILITY
    __map_const_iterator() _NOEXCEPT {}

    _LIBCPP_INLINE_VISIBILITY
    __map_const_iterator(_TreeIterator __i) _NOEXCEPT : __i_(__i) {}
    _LIBCPP_INLINE_VISIBILITY
    __map_const_iterator(__map_iterator<
        typename _TreeIterator::__non_const_iterator> __i) _NOEXCEPT
        : __i_(__i.__i_) {}

    _LIBCPP_INLINE_VISIBILITY
    reference operator*() const {return __i_->__get_value();}
    _LIBCPP_INLINE_VISIBILITY
    pointer operator->() const {return pointer_traits<pointer>::pointer_to(__i_->__get_value());}

    _LIBCPP_INLINE_VISIBILITY
    __map_const_iterator& operator++() {++__i_; return *this;}
    _LIBCPP_INLINE_VISIBILITY
    __map_const_iterator operator++(int)
    {
        __map_const_iterator __t(*this);
        ++(*this);
        return __t;
    }

    _LIBCPP_INLINE_VISIBILITY
    __map_const_iterator& operator--() {--__i_; return *this;}
    _LIBCPP_INLINE_VISIBILITY
    __map_const_iterator operator--(int)
    {
        __map_const_iterator __t(*this);
        --(*this);
        return __t;
    }

    friend _LIBCPP_INLINE_VISIBILITY
    bool operator==(const __map_const_iterator& __x, const __map_const_iterator& __y)
        {return __x.__i_ == __y.__i_;}
    friend _LIBCPP_INLINE_VISIBILITY
    bool operator!=(const __map_const_iterator& __x, const __map_const_iterator& __y)
        {return __x.__i_ != __y.__i_;}

    template <class, class, class, class> friend class _LIBCPP_TEMPLATE_VIS map;
    template <class, class, class, class> friend class _LIBCPP_TEMPLATE_VIS multimap;
    template <class, class, class> friend class _LIBCPP_TEMPLATE_VIS __tree_const_iterator;
};

template <class _Key, class _Tp, class _Compare = less<_Key>,
          class _Allocator = allocator<pair<const _Key, _Tp> > >
class _LIBCPP_TEMPLATE_VIS map
{
public:
    // types:
    typedef _Key                                     key_type;
    typedef _Tp                                      mapped_type;
    typedef pair<const key_type, mapped_type>        value_type;
    typedef typename __identity<_Compare>::type      key_compare;
    typedef typename __identity<_Allocator>::type    allocator_type;
    typedef value_type&                              reference;
    typedef const value_type&                        const_reference;

    static_assert((is_same<typename allocator_type::value_type, value_type>::value),
                  "Allocator::value_type must be same type as value_type");

        class _LIBCPP_TEMPLATE_VIS value_compare
            : public binary_function<value_type, value_type, bool>
        {
            friend class map;
        protected:
            key_compare comp;

            _LIBCPP_INLINE_VISIBILITY value_compare(key_compare c) : comp(c) {}
        public:
            _LIBCPP_INLINE_VISIBILITY
            bool operator()(const value_type& __x, const value_type& __y) const
                {return comp(__x.first, __y.first);}
        };

private:

    typedef _VSTD::__value_type<key_type, mapped_type>             __value_type;
    typedef __map_value_compare<key_type, __value_type, key_compare> __vc;
    typedef typename __rebind_alloc_helper<allocator_traits<allocator_type>,
                                                 __value_type>::type __allocator_type;
    typedef __tree<__value_type, __vc, __allocator_type>   __base;
    typedef typename __base::__node_traits                 __node_traits;
    typedef allocator_traits<allocator_type>               __alloc_traits;

    __base __tree_;

public:
    typedef typename __alloc_traits::pointer               pointer;
    typedef typename __alloc_traits::const_pointer         const_pointer;
    typedef typename __alloc_traits::size_type             size_type;
    typedef typename __alloc_traits::difference_type       difference_type;
    typedef __map_iterator<typename __base::iterator>             iterator;
    typedef __map_const_iterator<typename __base::const_iterator> const_iterator;
    typedef _VSTD::reverse_iterator<iterator>               reverse_iterator;
    typedef _VSTD::reverse_iterator<const_iterator>         const_reverse_iterator;

private:
    typedef typename __base::__node                    __node;
    typedef typename __base::__node_allocator          __node_allocator;
    typedef typename __base::__node_pointer            __node_pointer;
    typedef typename __base::__node_base_pointer       __node_base_pointer;
    typedef typename __base::__parent_pointer          __parent_pointer;

    typedef __map_node_destructor<__node_allocator> _Dp;
    typedef unique_ptr<__node, _Dp> __node_holder;

};



template <class _Key, class _Tp, class _Compare, class _Allocator>
inline _LIBCPP_INLINE_VISIBILITY
bool
operator==(const map<_Key, _Tp, _Compare, _Allocator>& __x,
           const map<_Key, _Tp, _Compare, _Allocator>& __y)
{
    return __x.size() == __y.size() && _VSTD::equal(__x.begin(), __x.end(), __y.begin());
}

template <class _Key, class _Tp, class _Compare, class _Allocator>
inline _LIBCPP_INLINE_VISIBILITY
bool
operator< (const map<_Key, _Tp, _Compare, _Allocator>& __x,
           const map<_Key, _Tp, _Compare, _Allocator>& __y)
{
    return _VSTD::lexicographical_compare(__x.begin(), __x.end(), __y.begin(), __y.end());
}

