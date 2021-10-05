#ifndef VECTOR_HPP
# define VECTOR_HPP
# include <memory>
# include "iterator.hpp"

namespace ft
{
	template<
		class T, //T must meet the requirements of CopyAssignable and CopyConstructible.
		class Allocator = std::allocator<T>
	> class vector
	{
	public:
		typedef T value_type;
		typedef Allocator allocator_type;
		typedef std::size_t size_type;
		typedef std::ptrdiff_t difference_type;
		typedef value_type& reference;
		typedef const value_type& const_reference;
		typedef typename Allocator::pointer pointer;
		typedef typename Allocator::const_pointer const_pointer;
		typedef random_access_iterator<random_access_iterator_tag, T> iterator;
		typedef const random_access_iterator<random_access_iterator_tag, T>  const_iterator;
		typedef reverse_iterator<iterator> reverse_iterator;
		typedef const vector::reverse_iterator const_reverse_iterator;
		//1) std::vector is a sequence container that encapsulates dynamic size arrays.
	private:
		size_t			_capacity;
		const Allocator	_alloc;
		T*				_arr;
	public:
		vector(): _capacity(0), _alloc(0), _arr(nullptr){}
		explicit vector(const Allocator& alloc): _capacity(0), _alloc(alloc), _arr(nullptr){}
		explicit vector( size_type count,
			const T& value = T(),
			const Allocator& alloc = Allocator())
		: _capacity(count), _alloc(alloc)
		{
			_arr = _alloc.allocate(_capacity);
			for (int i = 0; i < count; i++)
				
		}
		template< class InputIt >
vector( InputIt first, InputIt last,
        const Allocator& alloc = Allocator() );
		vector( const vector& other );
constexpr vector( const vector& other );
	};

}

#endif