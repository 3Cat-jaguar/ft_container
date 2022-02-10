#ifndef TEST_VECTOR_HPP
# define TEST_VECTOR_HPP

# include <memory>
# include <vector>
# include "./utils/random_access_iterator.hpp"
# include "./utils/reverse_iterator.hpp"

namespace ft
{
    template<typename T>
    struct   test_vector : public std::vector<T>
    {
        typedef	ft::random_access_iterator<T>			iterator;
        typedef	ft::random_access_iterator<const T>		const_iterator;
        typedef	ft::reverse_iterator<iterator>			reverse_iterator;
        typedef	ft::reverse_iterator<const_iterator>	const_reverse_iterator;
    
        iterator    begin()
        {
            return iterator(&(*this)[0]);
        }

        const_iterator  begin() const _NOEXCEPT
        {
            return iterator(&(*this)[0]);
        }

        iterator    end() _NOEXCEPT
        {
            return iterator(&(*this)[this->size()]);
        }

        const_iterator  end() const _NOEXCEPT
        {
            return iterator(&(*this)[this->size()]);
        }

    };

} // namespace ft


#endif