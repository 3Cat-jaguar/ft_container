//__tree 975줄
template <class _Tp, class _Compare, class _Allocator>
class __tree
{
public:
    typedef _Tp                                      value_type;
    typedef _Compare                                 value_compare;
    typedef _Allocator                               allocator_type;

private:
    typedef allocator_traits<allocator_type>         __alloc_traits;
    typedef typename __make_tree_node_types<value_type,
        typename __alloc_traits::void_pointer>::type
                                                    _NodeTypes;
    typedef typename _NodeTypes::key_type           key_type;
public:
    typedef typename _NodeTypes::__node_value_type      __node_value_type;
    typedef typename _NodeTypes::__container_value_type __container_value_type;

    typedef typename __alloc_traits::pointer         pointer;
    typedef typename __alloc_traits::const_pointer   const_pointer;
    typedef typename __alloc_traits::size_type       size_type;
    typedef typename __alloc_traits::difference_type difference_type;

public:
    typedef typename _NodeTypes::__void_pointer        __void_pointer;

    typedef typename _NodeTypes::__node_type           __node;
    typedef typename _NodeTypes::__node_pointer        __node_pointer;

    typedef typename _NodeTypes::__node_base_type      __node_base;
    typedef typename _NodeTypes::__node_base_pointer   __node_base_pointer;

    typedef typename _NodeTypes::__end_node_type       __end_node_t;
    typedef typename _NodeTypes::__end_node_pointer    __end_node_ptr;

    typedef typename _NodeTypes::__parent_pointer      __parent_pointer;
    typedef typename _NodeTypes::__iter_pointer        __iter_pointer;

    typedef typename __rebind_alloc_helper<__alloc_traits, __node>::type __node_allocator;
    typedef allocator_traits<__node_allocator>         __node_traits;

private:
    // check for sane allocator pointer rebinding semantics. Rebinding the
    // allocator for a new pointer type should be exactly the same as rebinding
    // the pointer using 'pointer_traits'.
    static_assert((is_same<__node_pointer, typename __node_traits::pointer>::value),
                  "Allocator does not rebind pointers in a sane manner.");
    typedef typename __rebind_alloc_helper<__node_traits, __node_base>::type
        __node_base_allocator;
    typedef allocator_traits<__node_base_allocator> __node_base_traits;
    static_assert((is_same<__node_base_pointer, typename __node_base_traits::pointer>::value),
                 "Allocator does not rebind pointers in a sane manner.");

private:
    __iter_pointer                                     __begin_node_;
    __compressed_pair<__end_node_t, __node_allocator>  __pair1_;
    __compressed_pair<size_type, value_compare>        __pair3_;

public:
    _LIBCPP_INLINE_VISIBILITY
    __iter_pointer __end_node() _NOEXCEPT
    {
        return static_cast<__iter_pointer>(
                pointer_traits<__end_node_ptr>::pointer_to(__pair1_.first())
        );
    }
    _LIBCPP_INLINE_VISIBILITY
    __iter_pointer __end_node() const _NOEXCEPT
    {
        return static_cast<__iter_pointer>(
            pointer_traits<__end_node_ptr>::pointer_to(
                const_cast<__end_node_t&>(__pair1_.first())
            )
        );
    }
    _LIBCPP_INLINE_VISIBILITY
          __node_allocator& __node_alloc() _NOEXCEPT {return __pair1_.second();}
private:
    _LIBCPP_INLINE_VISIBILITY
    const __node_allocator& __node_alloc() const _NOEXCEPT
        {return __pair1_.second();}
    _LIBCPP_INLINE_VISIBILITY
          __iter_pointer& __begin_node() _NOEXCEPT {return __begin_node_;}
    _LIBCPP_INLINE_VISIBILITY
    const __iter_pointer& __begin_node() const _NOEXCEPT {return __begin_node_;}
public:
    _LIBCPP_INLINE_VISIBILITY
    allocator_type __alloc() const _NOEXCEPT
        {return allocator_type(__node_alloc());}
private:
    _LIBCPP_INLINE_VISIBILITY
          size_type& size() _NOEXCEPT {return __pair3_.first();}
public:
    _LIBCPP_INLINE_VISIBILITY
    const size_type& size() const _NOEXCEPT {return __pair3_.first();}
    _LIBCPP_INLINE_VISIBILITY
          value_compare& value_comp() _NOEXCEPT {return __pair3_.second();}
    _LIBCPP_INLINE_VISIBILITY
    const value_compare& value_comp() const _NOEXCEPT
        {return __pair3_.second();}
public:

    _LIBCPP_INLINE_VISIBILITY
    __node_pointer __root() const _NOEXCEPT
        {return static_cast<__node_pointer>(__end_node()->__left_);}

    __node_base_pointer* __root_ptr() const _NOEXCEPT {
        return _VSTD::addressof(__end_node()->__left_);
    }

    typedef __tree_iterator<value_type, __node_pointer, difference_type>             iterator;
    typedef __tree_const_iterator<value_type, __node_pointer, difference_type> const_iterator;

    explicit __tree(const value_compare& __comp)
        _NOEXCEPT_(
            is_nothrow_default_constructible<__node_allocator>::value &&
            is_nothrow_copy_constructible<value_compare>::value);
    explicit __tree(const allocator_type& __a);
    __tree(const value_compare& __comp, const allocator_type& __a);
    __tree(const __tree& __t);
    __tree& operator=(const __tree& __t);
    template <class _ForwardIterator>
        void __assign_unique(_ForwardIterator __first, _ForwardIterator __last);
    template <class _InputIterator>
        void __assign_multi(_InputIterator __first, _InputIterator __last);
    __tree(__tree&& __t)
        _NOEXCEPT_(
            is_nothrow_move_constructible<__node_allocator>::value &&
            is_nothrow_move_constructible<value_compare>::value);
    __tree(__tree&& __t, const allocator_type& __a);
    __tree& operator=(__tree&& __t)
        _NOEXCEPT_(
            __node_traits::propagate_on_container_move_assignment::value &&
            is_nothrow_move_assignable<value_compare>::value &&
            is_nothrow_move_assignable<__node_allocator>::value);
    ~__tree();

    _LIBCPP_INLINE_VISIBILITY
          iterator begin()  _NOEXCEPT {return       iterator(__begin_node());}
    _LIBCPP_INLINE_VISIBILITY
    const_iterator begin() const _NOEXCEPT {return const_iterator(__begin_node());}
    _LIBCPP_INLINE_VISIBILITY
          iterator end() _NOEXCEPT {return       iterator(__end_node());}
    _LIBCPP_INLINE_VISIBILITY
    const_iterator end() const _NOEXCEPT {return const_iterator(__end_node());}

    _LIBCPP_INLINE_VISIBILITY
    size_type max_size() const _NOEXCEPT
        {return _VSTD::min<size_type>(
                __node_traits::max_size(__node_alloc()),
                numeric_limits<difference_type >::max());}

    void clear() _NOEXCEPT;

    void swap(__tree& __t)
#if _LIBCPP_STD_VER <= 11
        _NOEXCEPT_(
            __is_nothrow_swappable<value_compare>::value
            && (!__node_traits::propagate_on_container_swap::value ||
                 __is_nothrow_swappable<__node_allocator>::value)
            );
#else
        _NOEXCEPT_(__is_nothrow_swappable<value_compare>::value);
#endif

    template <class _Key, class ..._Args>
    pair<iterator, bool>
    __emplace_unique_key_args(_Key const&, _Args&&... __args);
    template <class _Key, class ..._Args>
    pair<iterator, bool>
    __emplace_hint_unique_key_args(const_iterator, _Key const&, _Args&&...);

    template <class... _Args>
    pair<iterator, bool> __emplace_unique_impl(_Args&&... __args);

    template <class... _Args>
    iterator __emplace_hint_unique_impl(const_iterator __p, _Args&&... __args);

    template <class... _Args>
    iterator __emplace_multi(_Args&&... __args);

    template <class... _Args>
    iterator __emplace_hint_multi(const_iterator __p, _Args&&... __args);

    template <class _Pp>
    _LIBCPP_INLINE_VISIBILITY
    pair<iterator, bool> __emplace_unique(_Pp&& __x) {
        return __emplace_unique_extract_key(_VSTD::forward<_Pp>(__x),
                                            __can_extract_key<_Pp, key_type>());
    }

    template <class _First, class _Second>
    _LIBCPP_INLINE_VISIBILITY
    typename enable_if<
        __can_extract_map_key<_First, key_type, __container_value_type>::value,
        pair<iterator, bool>
    >::type __emplace_unique(_First&& __f, _Second&& __s) {
        return __emplace_unique_key_args(__f, _VSTD::forward<_First>(__f),
                                              _VSTD::forward<_Second>(__s));
    }

    template <class... _Args>
    _LIBCPP_INLINE_VISIBILITY
    pair<iterator, bool> __emplace_unique(_Args&&... __args) {
        return __emplace_unique_impl(_VSTD::forward<_Args>(__args)...);
    }

    template <class _Pp>
    _LIBCPP_INLINE_VISIBILITY
    pair<iterator, bool>
    __emplace_unique_extract_key(_Pp&& __x, __extract_key_fail_tag) {
      return __emplace_unique_impl(_VSTD::forward<_Pp>(__x));
    }

    template <class _Pp>
    _LIBCPP_INLINE_VISIBILITY
    pair<iterator, bool>
    __emplace_unique_extract_key(_Pp&& __x, __extract_key_self_tag) {
      return __emplace_unique_key_args(__x, _VSTD::forward<_Pp>(__x));
    }

    template <class _Pp>
    _LIBCPP_INLINE_VISIBILITY
    pair<iterator, bool>
    __emplace_unique_extract_key(_Pp&& __x, __extract_key_first_tag) {
      return __emplace_unique_key_args(__x.first, _VSTD::forward<_Pp>(__x));
    }

    template <class _Pp>
    _LIBCPP_INLINE_VISIBILITY
    iterator __emplace_hint_unique(const_iterator __p, _Pp&& __x) {
        return __emplace_hint_unique_extract_key(__p, _VSTD::forward<_Pp>(__x),
                                            __can_extract_key<_Pp, key_type>());
    }

    template <class _First, class _Second>
    _LIBCPP_INLINE_VISIBILITY
    typename enable_if<
        __can_extract_map_key<_First, key_type, __container_value_type>::value,
        iterator
    >::type __emplace_hint_unique(const_iterator __p, _First&& __f, _Second&& __s) {
        return __emplace_hint_unique_key_args(__p, __f,
                                              _VSTD::forward<_First>(__f),
                                              _VSTD::forward<_Second>(__s)).first;
    }

    template <class... _Args>
    _LIBCPP_INLINE_VISIBILITY
    iterator __emplace_hint_unique(const_iterator __p, _Args&&... __args) {
        return __emplace_hint_unique_impl(__p, _VSTD::forward<_Args>(__args)...);
    }

    template <class _Pp>
    _LIBCPP_INLINE_VISIBILITY
    iterator
    __emplace_hint_unique_extract_key(const_iterator __p, _Pp&& __x, __extract_key_fail_tag) {
      return __emplace_hint_unique_impl(__p, _VSTD::forward<_Pp>(__x));
    }

    template <class _Pp>
    _LIBCPP_INLINE_VISIBILITY
    iterator
    __emplace_hint_unique_extract_key(const_iterator __p, _Pp&& __x, __extract_key_self_tag) {
      return __emplace_hint_unique_key_args(__p, __x, _VSTD::forward<_Pp>(__x)).first;
    }

    template <class _Pp>
    _LIBCPP_INLINE_VISIBILITY
    iterator
    __emplace_hint_unique_extract_key(const_iterator __p, _Pp&& __x, __extract_key_first_tag) {
      return __emplace_hint_unique_key_args(__p, __x.first, _VSTD::forward<_Pp>(__x)).first;
    }

    _LIBCPP_INLINE_VISIBILITY
    pair<iterator, bool> __insert_unique(const __container_value_type& __v) {
        return __emplace_unique_key_args(_NodeTypes::__get_key(__v), __v);
    }

    _LIBCPP_INLINE_VISIBILITY
    iterator __insert_unique(const_iterator __p, const __container_value_type& __v) {
        return __emplace_hint_unique_key_args(__p, _NodeTypes::__get_key(__v), __v).first;
    }

    _LIBCPP_INLINE_VISIBILITY
    pair<iterator, bool> __insert_unique(__container_value_type&& __v) {
        return __emplace_unique_key_args(_NodeTypes::__get_key(__v), _VSTD::move(__v));
    }

    _LIBCPP_INLINE_VISIBILITY
    iterator __insert_unique(const_iterator __p, __container_value_type&& __v) {
        return __emplace_hint_unique_key_args(__p, _NodeTypes::__get_key(__v), _VSTD::move(__v)).first;
    }

    template <class _Vp, class = typename enable_if<
            !is_same<typename __unconstref<_Vp>::type,
                     __container_value_type
            >::value
        >::type>
    _LIBCPP_INLINE_VISIBILITY
    pair<iterator, bool> __insert_unique(_Vp&& __v) {
        return __emplace_unique(_VSTD::forward<_Vp>(__v));
    }

    template <class _Vp, class = typename enable_if<
            !is_same<typename __unconstref<_Vp>::type,
                     __container_value_type
            >::value
        >::type>
    _LIBCPP_INLINE_VISIBILITY
    iterator __insert_unique(const_iterator __p, _Vp&& __v) {
        return __emplace_hint_unique(__p, _VSTD::forward<_Vp>(__v));
    }

    _LIBCPP_INLINE_VISIBILITY
    iterator __insert_multi(__container_value_type&& __v) {
        return __emplace_multi(_VSTD::move(__v));
    }

    _LIBCPP_INLINE_VISIBILITY
    iterator __insert_multi(const_iterator __p, __container_value_type&& __v) {
        return __emplace_hint_multi(__p, _VSTD::move(__v));
    }

    template <class _Vp>
    _LIBCPP_INLINE_VISIBILITY
    iterator __insert_multi(_Vp&& __v) {
        return __emplace_multi(_VSTD::forward<_Vp>(__v));
    }

    template <class _Vp>
    _LIBCPP_INLINE_VISIBILITY
    iterator __insert_multi(const_iterator __p, _Vp&& __v) {
        return __emplace_hint_multi(__p, _VSTD::forward<_Vp>(__v));
    }

    _LIBCPP_INLINE_VISIBILITY
    pair<iterator, bool> __node_assign_unique(const __container_value_type& __v, __node_pointer __dest);

    _LIBCPP_INLINE_VISIBILITY
    iterator __node_insert_multi(__node_pointer __nd);
    _LIBCPP_INLINE_VISIBILITY
    iterator __node_insert_multi(const_iterator __p, __node_pointer __nd);


    _LIBCPP_INLINE_VISIBILITY iterator
    __remove_node_pointer(__node_pointer) _NOEXCEPT;

#if _LIBCPP_STD_VER > 14
    template <class _NodeHandle, class _InsertReturnType>
    _LIBCPP_INLINE_VISIBILITY
    _InsertReturnType __node_handle_insert_unique(_NodeHandle&&);
    template <class _NodeHandle>
    _LIBCPP_INLINE_VISIBILITY
    iterator __node_handle_insert_unique(const_iterator, _NodeHandle&&);
    template <class _Tree>
    _LIBCPP_INLINE_VISIBILITY
    void __node_handle_merge_unique(_Tree& __source);

    template <class _NodeHandle>
    _LIBCPP_INLINE_VISIBILITY
    iterator __node_handle_insert_multi(_NodeHandle&&);
    template <class _NodeHandle>
    _LIBCPP_INLINE_VISIBILITY
    iterator __node_handle_insert_multi(const_iterator, _NodeHandle&&);
    template <class _Tree>
    _LIBCPP_INLINE_VISIBILITY
    void __node_handle_merge_multi(_Tree& __source);


    template <class _NodeHandle>
    _LIBCPP_INLINE_VISIBILITY
    _NodeHandle __node_handle_extract(key_type const&);
    template <class _NodeHandle>
    _LIBCPP_INLINE_VISIBILITY
    _NodeHandle __node_handle_extract(const_iterator);
#endif

    iterator erase(const_iterator __p);
    iterator erase(const_iterator __f, const_iterator __l);
    template <class _Key>
        size_type __erase_unique(const _Key& __k);
    template <class _Key>
        size_type __erase_multi(const _Key& __k);

    void __insert_node_at(__parent_pointer     __parent,
                          __node_base_pointer& __child,
                          __node_base_pointer __new_node) _NOEXCEPT;

    template <class _Key>
        iterator find(const _Key& __v);
    template <class _Key>
        const_iterator find(const _Key& __v) const;

    template <class _Key>
        size_type __count_unique(const _Key& __k) const;
    template <class _Key>
        size_type __count_multi(const _Key& __k) const;

    template <class _Key>
        _LIBCPP_INLINE_VISIBILITY
        iterator lower_bound(const _Key& __v)
            {return __lower_bound(__v, __root(), __end_node());}
    template <class _Key>
        iterator __lower_bound(const _Key& __v,
                               __node_pointer __root,
                               __iter_pointer __result);
    template <class _Key>
        _LIBCPP_INLINE_VISIBILITY
        const_iterator lower_bound(const _Key& __v) const
            {return __lower_bound(__v, __root(), __end_node());}
    template <class _Key>
        const_iterator __lower_bound(const _Key& __v,
                                     __node_pointer __root,
                                     __iter_pointer __result) const;
    template <class _Key>
        _LIBCPP_INLINE_VISIBILITY
        iterator upper_bound(const _Key& __v)
            {return __upper_bound(__v, __root(), __end_node());}
    template <class _Key>
        iterator __upper_bound(const _Key& __v,
                               __node_pointer __root,
                               __iter_pointer __result);
    template <class _Key>
        _LIBCPP_INLINE_VISIBILITY
        const_iterator upper_bound(const _Key& __v) const
            {return __upper_bound(__v, __root(), __end_node());}
    template <class _Key>
        const_iterator __upper_bound(const _Key& __v,
                                     __node_pointer __root,
                                     __iter_pointer __result) const;
    template <class _Key>
        pair<iterator, iterator>
        __equal_range_unique(const _Key& __k);
    template <class _Key>
        pair<const_iterator, const_iterator>
        __equal_range_unique(const _Key& __k) const;

    template <class _Key>
        pair<iterator, iterator>
        __equal_range_multi(const _Key& __k);
    template <class _Key>
        pair<const_iterator, const_iterator>
        __equal_range_multi(const _Key& __k) const;

    typedef __tree_node_destructor<__node_allocator> _Dp;
    typedef unique_ptr<__node, _Dp> __node_holder;

    __node_holder remove(const_iterator __p) _NOEXCEPT;
private:
    __node_base_pointer&
        __find_leaf_low(__parent_pointer& __parent, const key_type& __v);
    __node_base_pointer&
        __find_leaf_high(__parent_pointer& __parent, const key_type& __v);
    __node_base_pointer&
        __find_leaf(const_iterator __hint,
                    __parent_pointer& __parent, const key_type& __v);
    // FIXME: Make this function const qualified. Unfortunately doing so
    // breaks existing code which uses non-const callable comparators.
    template <class _Key>
    __node_base_pointer&
        __find_equal(__parent_pointer& __parent, const _Key& __v);
    template <class _Key>
    _LIBCPP_INLINE_VISIBILITY __node_base_pointer&
    __find_equal(__parent_pointer& __parent, const _Key& __v) const {
      return const_cast<__tree*>(this)->__find_equal(__parent, __v);
    }
    template <class _Key>
    __node_base_pointer&
        __find_equal(const_iterator __hint, __parent_pointer& __parent,
                     __node_base_pointer& __dummy,
                     const _Key& __v);

    template <class ..._Args>
    __node_holder __construct_node(_Args&& ...__args);

    void destroy(__node_pointer __nd) _NOEXCEPT;

    _LIBCPP_INLINE_VISIBILITY
    void __copy_assign_alloc(const __tree& __t)
        {__copy_assign_alloc(__t, integral_constant<bool,
             __node_traits::propagate_on_container_copy_assignment::value>());}

    _LIBCPP_INLINE_VISIBILITY
    void __copy_assign_alloc(const __tree& __t, true_type)
        {
        if (__node_alloc() != __t.__node_alloc())
            clear();
        __node_alloc() = __t.__node_alloc();
        }
    _LIBCPP_INLINE_VISIBILITY
    void __copy_assign_alloc(const __tree&, false_type) {}

    void __move_assign(__tree& __t, false_type);
    void __move_assign(__tree& __t, true_type)
        _NOEXCEPT_(is_nothrow_move_assignable<value_compare>::value &&
                   is_nothrow_move_assignable<__node_allocator>::value);

    _LIBCPP_INLINE_VISIBILITY
    void __move_assign_alloc(__tree& __t)
        _NOEXCEPT_(
            !__node_traits::propagate_on_container_move_assignment::value ||
            is_nothrow_move_assignable<__node_allocator>::value)
        {__move_assign_alloc(__t, integral_constant<bool,
             __node_traits::propagate_on_container_move_assignment::value>());}

    _LIBCPP_INLINE_VISIBILITY
    void __move_assign_alloc(__tree& __t, true_type)
        _NOEXCEPT_(is_nothrow_move_assignable<__node_allocator>::value)
        {__node_alloc() = _VSTD::move(__t.__node_alloc());}
    _LIBCPP_INLINE_VISIBILITY
    void __move_assign_alloc(__tree&, false_type) _NOEXCEPT {}

    struct _DetachedTreeCache {
      _LIBCPP_INLINE_VISIBILITY
      explicit _DetachedTreeCache(__tree *__t) _NOEXCEPT : __t_(__t),
        __cache_root_(__detach_from_tree(__t)) {
          __advance();
        }

      _LIBCPP_INLINE_VISIBILITY
      __node_pointer __get() const _NOEXCEPT {
        return __cache_elem_;
      }

      _LIBCPP_INLINE_VISIBILITY
      void __advance() _NOEXCEPT {
        __cache_elem_ = __cache_root_;
        if (__cache_root_) {
          __cache_root_ = __detach_next(__cache_root_);
        }
      }

      _LIBCPP_INLINE_VISIBILITY
      ~_DetachedTreeCache() {
        __t_->destroy(__cache_elem_);
        if (__cache_root_) {
          while (__cache_root_->__parent_ != nullptr)
            __cache_root_ = static_cast<__node_pointer>(__cache_root_->__parent_);
          __t_->destroy(__cache_root_);
        }
      }

       _DetachedTreeCache(_DetachedTreeCache const&) = delete;
       _DetachedTreeCache& operator=(_DetachedTreeCache const&) = delete;

    private:
      _LIBCPP_INLINE_VISIBILITY
      static __node_pointer __detach_from_tree(__tree *__t) _NOEXCEPT;
      _LIBCPP_INLINE_VISIBILITY
      static __node_pointer __detach_next(__node_pointer) _NOEXCEPT;

      __tree *__t_;
      __node_pointer __cache_root_;
      __node_pointer __cache_elem_;
    };


    template <class, class, class, class> friend class _LIBCPP_TEMPLATE_VIS map;
    template <class, class, class, class> friend class _LIBCPP_TEMPLATE_VIS multimap;
};
