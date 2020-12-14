#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <algorithm>
#include <vector>
#include <string>
#include <list>

// complete guide L3208
// the default assignment op requires that both sides of the assignment
// op have the same type, which is not the case if stack have different
// element types
// by defining an assignment op as a template, you can enable conversion
template< typename Container >
class Stack
{
private:
    Container elements{};

public:
    Stack( std::initializer_list< typename Container::value_type > il )
      : elements( il )
    {
    }

    template< typename B >
    Stack& operator=( const Stack< B >& other )
    {
        this->elements.resize( other.elements.size() );
        std::copy( other.elements.begin(), other.elements.end(), this->elements.begin() );
        return *this;
    }

    // complete guide L3279
    // in order to access "other" container's private data member, I have to
    // use friend access
    // because the name of the template parameter is not used, I can omit it
    template< typename >
    friend class Stack;

    [[nodiscard]] const Container& preview() const
    {
        return elements;
    }
};

TEST_CASE( "test assign stack of different implementation type" )
{
    Stack< std::list< int > > st1{ 1, 2, 3 };
    Stack< std::vector< float > > st2{ 4, 5, 6 };
    // won't compile without the template assignment op
    st1 = st2;
    CHECK_EQ( std::list< int >{ 4, 5, 6 }, st1.preview() );
}
