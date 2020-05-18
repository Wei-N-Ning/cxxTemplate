//
// Created by weining on 18/5/20.
//

//

// see the implementation (gcc) of std::iterator_traits<>

//   template<typename _Iterator>
//    struct __iterator_traits<_Iterator,
//			     __void_t<typename _Iterator::iterator_category,
//				      typename _Iterator::value_type,
//				      typename _Iterator::difference_type,
//				      typename _Iterator::pointer,
//				      typename _Iterator::reference>>
//    {
//      typedef typename _Iterator::iterator_category iterator_category;
//      typedef typename _Iterator::value_type        value_type;
//      typedef typename _Iterator::difference_type   difference_type;
//      typedef typename _Iterator::pointer           pointer;
//      typedef typename _Iterator::reference         reference;
//    };

// __void_t< ... > will trigger SFINAE if any of these requirement member type
// does not exist in the given T
