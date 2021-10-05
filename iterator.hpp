#ifndef ITERATOR_HPP
# define ITERATOR_HPP
# include <memory>

namespace ft
{
	/*
	*	Iterator categories.
	*	typedef of the original empty structs, if reimplemented stl algorithms wouldnt work.
	*/
	typedef std::input_iterator_tag input_iterator_tag;
	typedef std::output_iterator_tag output_iterator_tag;
	typedef std::forward_iterator_tag forward_iterator_tag;
	typedef std::bidirectional_iterator_tag bidirectional_iterator_tag;
	typedef std::random_access_iterator_tag random_access_iterator_tag;

	/*
	*	Iterator_traits
	*/
	template <class Iterator>
	struct iterator_traits {
		typedef typename Iterator::iterator_category iterator_category;
		typedef typename Iterator::value_type        value_type;
		typedef typename Iterator::difference_type   difference_type;
		typedef typename Iterator::pointer           pointer;
		typedef typename Iterator::reference         reference;
	};

	template <class T>
	struct iterator_traits<T*> {
		typedef random_access_iterator_tag iterator_category;
		typedef T                          value_type;
		typedef ptrdiff_t                  difference_type;
		typedef T*                         pointer;
		typedef T&                         reference;
  	};

	/*
	*	Iterator class member types.
	*/
	template<class _Category, class _Tp, class _Distance = ptrdiff_t,
	class _Pointer = _Tp*, class _Reference = _Tp&>
	struct iterator
	{
		typedef _Tp        value_type;
		typedef _Distance  difference_type;
		typedef _Pointer   pointer;
		typedef _Reference reference;
		typedef _Category  iterator_category;
	};

	/*
	*	Insert iterator.
	*/
	template <class Container>
	class insert_iterator :
	public std::iterator<output_iterator_tag,void,void,void,void>
	{
	protected:
		Container* container;
		typename Container::iterator iter;

	public:
		typedef Container container_type;
		explicit insert_iterator (Container& x, typename Container::iterator i): container(&x), iter(i) {}
		insert_iterator<Container>& operator= (typename Container::const_reference value) { iter=container->insert(iter,value); ++iter; return *this; }
		insert_iterator<Container>& operator* () { return *this; }
		insert_iterator<Container>& operator++ () { return *this; }
		insert_iterator<Container>& operator++ (int) { return *this; }
	};

	/*
	*	Back insert iterator.
	*/
	template <class Container>
	class back_insert_iterator :
	public std::iterator<output_iterator_tag,void,void,void,void>
	{
	protected:
		Container* container;

	public:
		typedef Container container_type;
	explicit back_insert_iterator (Container& x) : container(&x) {}
		back_insert_iterator<Container>& operator= (typename Container::const_reference value) { container->push_back(value); return *this; }
		back_insert_iterator<Container>& operator* () { return *this; }
		back_insert_iterator<Container>& operator++ () { return *this; }
		back_insert_iterator<Container> operator++ (int) { return *this; }
	};

	/*
	*	Front insert iterator.
	*/
	template <class Container>
	class front_insert_iterator :
	public iterator<output_iterator_tag,void,void,void,void>
	{
	protected:
		Container* container;

	public:
		typedef Container container_type;
		explicit front_insert_iterator (Container& x) : container(&x) {}
		front_insert_iterator<Container>& operator= (typename Container::const_reference value) { container->push_front(value); return *this; }
		front_insert_iterator<Container>& operator* () { return *this; }
		front_insert_iterator<Container>& operator++ () { return *this; }
		front_insert_iterator<Container> operator++ (int) { return *this; }
	};

	/*
	*	Random access iterator.
	*/
	template<
    class Category,
    class T,
    class Distance = std::ptrdiff_t,
    class Pointer = T*,
    class Reference = T&
	> class random_access_iterator: random_access_iterator_tag
	{
	public:
		typedef T value_type;
		typedef value_type* pointer;
		typedef value_type const * const_pointer;
		typedef value_type& reference;
		typedef value_type const & const_reference;
		typedef std::ptrdiff_t difference_type;
	protected:
		pointer ptr;
		difference_type diff;
	public:
		random_access_iterator(): ptr(nullptr), diff(sizeof(value_type)) {}
		random_access_iterator(pointer p): ptr(p), diff(sizeof(value_type)) {}
		random_access_iterator(const random_access_iterator& it): ptr(it.p), diff(sizeof(value_type)) {}
		virtual ~random_access_iterator() {}


		bool operator==(random_access_iterator const &other) const {
			return (this->ptr == other.ptr);
		}
		
		bool operator!=(random_access_iterator const &other) const
		{
			return (this->ptr != other.ptr);
		}

		reference operator*()
		{
			return (*this->ptr);
		}
		
		const_reference operator*() const
		{
			return (*this->ptr);
		}

		reference operator[](int n)
		{
			return (this->ptr[n]);
		}

		const_reference operator[](int n) const
		{
			return (this->ptr[n]);
		}

		pointer operator->()
		{
			return (this->ptr);
		}
		
		const_pointer operator->() const
		{
			return (this->ptr);
		}

		random_access_iterator operator++(int) {
			random_access_iterator aux(*this);
			this->ptr++;
			return (aux);
		}

		random_access_iterator& operator++() {
			this->ptr++;
			return (*this);
		}

		random_access_iterator operator--(int) {
			random_access_iterator aux(*this);
			this->ptr--;
			return (aux);
		}

		random_access_iterator& operator--() {
			this->ptr--;
			return (*this);
		}

		random_access_iterator& operator+=(int n)
		{
			this->ptr += n * this->diff;
			return (*this);
		}

		random_access_iterator operator+(int n) const
		{
			random_access_iterator ret(*this);
			return (ret += n);
		}

		random_access_iterator& operator-=(int n)
		{
			this->ptr -= n * this->diff;
			return (*this);
		}

		random_access_iterator operator-(int n) const
		{
			random_access_iterator ret(*this);
			return (ret -= n);
		}

		bool operator>(random_access_iterator const &other) const
		{
			return (this->ptr > other.ptr);
		}

		bool operator<(random_access_iterator const &other) const
		{
			return (this->ptr < other.ptr);
		}

		bool operator>=(random_access_iterator const &other) const
		{
			return (this->ptr >= other.ptr);
		}

		bool operator<=(random_access_iterator const &other) const
		{
			return (this->ptr <= other.ptr);
		}

		template <class InputIterator, class Dist>
		void advance (InputIterator& it, Dist n)
		{
			*this = *this + n;
		}

		template<class InputIterator>
  		typename iterator_traits<InputIterator>::difference_type
    	distance (InputIterator first, InputIterator last)
		{
			return (last - first);
		}

		template <class Container>
		back_insert_iterator<Container> back_inserter (Container& x)
		{
			return (back_insert_iterator<Container>(x));
		}

		template <class Container>
		front_insert_iterator<Container> front_inserter (Container& x)
		{
			return (front_insert_iterator<Container>(x));
		}

		template <class Container, class Iterator>
		insert_iterator<Container> inserter (Container& x, Iterator it)
		{
			return (insert_iterator<Container>(x, it));
		}
	};

	/*
	*	Reverse iterator adaptor.
	*/
	template<typename Itr>
	class reverse_iterator
	{
		Itr itr;
	public:
		explicit reverse_iterator(Itr itr): itr(itr) {}
		const typename iterator_traits<Itr>::reference operator*()
		{
			return *std::prev(itr); // <== returns the content of prev
		}

		Itr& operator++()
		{
			--itr;
			return *this;
		}

		friend bool operator!=(reverse_iterator<Itr> a, reverse_iterator<Itr> b)
		{
			return a.itr != b.itr;
		}
	};

}

#endif